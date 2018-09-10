#include "stdafx.h"
#include "LinearModel.h"
#include "DerivEnum.h"
#include "integr.h"
#include "float.h"
#include "cosMatrix.h"

	calcLib::LinearModel::LinearModel(size_t counts, float dt, int numNodes, int numElements, float ro, float Elast, float lenght, float b, float h)
	{
		_elastic = Elast;
		_L = lenght;
		_b = b;
		_h = h;
		_A = _b * _h;
		_ro = ro;
		_m = ro * _A * _L;
		_counts = counts;
		_dt = dt;
		initTime(_counts, _dt, time);
		initarrays(numNodes, numElements, _counts, 3, N, E);
	}
	void calcLib::LinearModel::calcOneStep(int now, int prev)
	{
		_A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < E->Length; i++)
		{
			float l = preob::getL
			(
				N[E[i]->n1]->deriv[prev][(int)DerivEnum::coord][x],
				N[E[i]->n2]->deriv[prev][(int)DerivEnum::coord][x],
				N[E[i]->n1]->deriv[prev][(int)DerivEnum::coord][y],
				N[E[i]->n2]->deriv[prev][(int)DerivEnum::coord][y]
			);
			if (l == 0 || l >= FLT_MAX)
			{
				 throw gcnew NotFiniteNumberException();
			}
			/*transform displ from glob to loc*/
			cosMatrix::getAngles(N[E[i]->n1]->deriv[prev][(int)DerivEnum::coord], N[E[i]->n2]->deriv[prev][(int)DerivEnum::coord], l, E[i]->angles);

			array<float>^ p1 = gcnew array<float>(3);
			array<float>^ p2 = gcnew array<float>(3);
			preob::to_loc(N[E[i]->n1]->deriv[prev][(int)DerivEnum::u], N[E[i]->n1]->deriv[0][(int)DerivEnum::u], E[i]->angles, p1);
			preob::to_loc(N[E[i]->n2]->deriv[prev][(int)DerivEnum::u], N[E[i]->n1]->deriv[0][(int)DerivEnum::u], E[i]->angles, p2);

			/*if (i-1 == E->Length)
			{
				p2[0] = 0;
			}*/
			E[i]->force[now][x] = ((_elastic * _A / l) * (p2[x] - p1[x]));

			array<float>^ gF = gcnew array<float>(3);
			preob::to_glob(E[i]->force[now], E[i]->force[0], E[i]->angles, gF);
			N[E[i]->n2]->deriv[now][(int)DerivEnum::force][0] += gF[0];
			N[E[i]->n1]->deriv[now][(int)DerivEnum::force][0] += 0 - gF[0];

			integr::euler(N[E[i]->n1]->deriv, prev, now, _m, l, _dt);
			integr::euler(N[E[i]->n2]->deriv, prev, now, _m, l, _dt);

		}
	}
	void calcLib::LinearModel::calcMove()
	{
		for (int i = 2; i < time->Length; i++)
		{
			calcOneStep(i, i - 1);
		}
	}
	void calcLib::LinearModel::initTime(size_t counts, float deltaT, array<float>^% time)
	{
		time = gcnew array<float>(counts);
		for (size_t i = 1; i < counts; i++)
		{
			time[i] = time[i - 1] + deltaT;
		}
	}
	void calcLib::LinearModel::initarrays(int numNodes, int numElements, size_t counts, int demensia, array<Node^>^% N, array<Element^>^% E)
	{
		N = gcnew array<Node^>(numNodes);
		E = gcnew array<Element^>(numElements);
		for (int i = 0; i < N->Length; i++)
		{
			N[i] = gcnew Node(nodeFreedoms::O_x, counts);
		}
		for (int i = 0; i < E->Length; i++)
		{
			E[i] = gcnew Element(i, i + 1, counts);
		}
	}
	void calcLib::LinearModel::initCoords(float elemL, size_t counts, array<Node^>^% N, array<Element^>^% E)
	{
		for (int n = 1; n < N->Length; n++)
		{
			for (size_t i = 0; i < counts; i++)
			{
				N[n]->deriv[i][(int)DerivEnum::coord][x] = N[n - 1]->deriv[i][(int)DerivEnum::coord][x] + elemL;
				//N[n]->deriv[(int)DerivEnum::coord][y][i] = N[n - 1]->deriv[(int)DerivEnum::coord][y][i] + elemL;
			}
		}
	}
	void calcLib::LinearModel::initLoad(int freq, float amp, array<float>^ time, array<Node^>^% N)
	{
		for (int i = 1; i < time->Length; i++)
		{
			N[0]->deriv[i][(int)DerivEnum::u][x] = amp * (float)Math::Sin(time[i] * 2.0f * Math::PI * freq);
			//N[0]->deriv[(int)DerivEnum::u][x][i] = N[0]->deriv[(int)DerivEnum::coord][x][i] - N[0]->deriv[(int)DerivEnum::coord][x][i - 1];
		}
	}
