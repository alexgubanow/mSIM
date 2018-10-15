#include "stdafx.h"
#include "Model.h"
#include "DerivEnum.h"
#include "integr.h"
#include "float.h"

calcLib::Model::Model(int counts, float dt, int numNodes, int maxMembers, float ro, float Elast, float b, float h)
{
	_E = Elast;
	_b = b;
	_h = h;
	_ro = ro;
	_counts = counts;
	_dt = dt;
	_maxMembers = maxMembers;
	initTime(_dt, time);
	initarrays(numNodes, N, Mr);
}
void calcLib::Model::calcMove()
{
	for (int i = 2; i < time->Length; i++)
	{
		calcOneStep(i, i - 1);
	}
}

void calcLib::Model::calcOneStep(int now, int prev)
{
	//overview members of curr node
	for (int i = 0; i < N->Length; i++)
	{
		int j = 0;
		while (N[i]->members[j] != -1)
		{
			int mIndx = N[i]->members[j];
			//calc current length
			Mr[mIndx]->getLength(N, prev);
			//get angels
			Mr[mIndx]->calcDCM(N, i, prev);
			//put disturb from member to node, like cumulative sum
			Mr[mIndx]->getDisturb(_E, N, i, prev, now, _dt);
			j++;
		}
	}	
}

void calcLib::Model::initTime(float deltaT, array<float>^% time)
{
	time = gcnew array<float>(_counts);
	for (int i = 1; i < _counts; i++)
	{
		time[i] = time[i - 1] + deltaT;
	}
}
void calcLib::Model::initarrays(int numNodes, array<Node^>^% N, array<Member^>^% Mr)
{
	N = gcnew array<Node^>(numNodes);
	for (int i = 0; i < N->Length; i++)
	{
		N[i] = gcnew Node(nodeFreedoms::O_x, _counts, _maxMembers);
	}
	Mr = gcnew array<Member^>(numNodes - 1);
	for (int i = 0; i < Mr->Length; i++)
	{
		Mr[i] = gcnew Member(i, i + 1, mtEnum::LinElem);
	}
}
void calcLib::Model::initCoords(float elemL, array<Node^>^% N)
{
	for (int n = 1; n < N->Length; n++)
	{
		for (int i = 0; i < _counts; i++)
		{
			N[n]->deriv[i][(int)DerivEnum::coord][x] = N[n - 1]->deriv[i][(int)DerivEnum::coord][x] + elemL;
			//N[n]->deriv[(int)DerivEnum::coord][y][i] = N[n - 1]->deriv[(int)DerivEnum::coord][y][i] + elemL;
		}
	}
}
void calcLib::Model::initLoad(int freq, float amp, array<float>^ time, array<Node^>^% N)
{
	for (int i = 1; i < time->Length; i++)
	{
		throw gcnew System::NotImplementedException();
		// TODO: insert return statement here
	}
}