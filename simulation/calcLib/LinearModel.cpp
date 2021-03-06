#include "stdafx.h"
#include "LinearModel.h"

namespace calcLib {
	void Linear::Model::calcOneMove(int now, int prev)
	{
		_A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < E[now]->Length; i++)
		{
			double forceNow1 = P[now][E[now][i]->p1]->force[0];
			double forceNow2 = P[now][E[now][i]->p2]->force[0];
			double displPrev1 = N[prev][E[now][i]->n1]->deriv->displ[0];
			double displPrev2 = N[prev][E[now][i]->n2]->deriv->displ[0];
			/*transform displ from glob to loc*/
			//double L = preob::getL();

			double l = preob::getL(N[now][E[now][i]->n1]->deriv->coord[0], N[now][E[now][i]->n2]->deriv->coord[0], N[now][E[now][i]->n1]->deriv->coord[1], N[now][E[now][i]->n2]->deriv->coord[1]);
			array<double>^ locDispl1 = gcnew array<double>(3);
			array<double>^ locDispl2 = gcnew array<double>(3);
			preob::to_loc(N[0][E[now][i]->n1]->deriv->displ, N[prev][E[now][i]->n1]->deriv->displ, E[now][i]->mP, locDispl1);
			preob::to_loc(N[0][E[now][i]->n2]->deriv->displ, N[prev][E[now][i]->n2]->deriv->displ, E[now][i]->mP, locDispl2);

			array<double>^ locforceNow1 = gcnew array<double>(3);
			array<double>^ locforceNow2 = gcnew array<double>(3);
			locforceNow1[0] = ((_elastic * _A / l) * (locDispl2[0] - locDispl1[0]));
			locforceNow2[0] = -((_elastic * _A / l) * (locDispl2[0] - locDispl1[0]));

			preob::to_glob(P[0][E[now][i]->p1]->force, locforceNow1, E[now][i]->mP, P[now][E[now][i]->p1]->force);
			preob::to_glob(P[0][E[now][i]->p2]->force, locforceNow2, E[now][i]->mP, P[now][E[now][i]->p2]->force);
		}
		for (int i = 1; i < N[now]->Length - 1; i++)
		{
			_L = preob::getL(N[now][i - 1]->deriv->coord[0], N[now][i]->deriv->coord[0], N[now][i - 1]->deriv->coord[1], N[now][i]->deriv->coord[1]);
			_m = _ro * _A * _L;
			//sum all
			for (int j = 0; j < N[now][i]->ListOfPoints->Length; j++)
			{
				N[now][i]->deriv->force[0] += P[now][N[now][i]->ListOfPoints[j]]->force[0];
				N[now][i]->deriv->force[1] += P[now][N[now][i]->ListOfPoints[j]]->force[1];
			}
			double acclNow1 = N[now][i]->deriv->accl[0];
			double velosPrev1 = N[prev][i]->deriv->velos[0];
			double velosNow1 = N[now][i]->deriv->velos[0];
			double displNow1 = N[now][i]->deriv->displ[0];
			acclNow1 = N[now][i]->deriv->force[0] / _m;
			velosNow1 = acclNow1 * time[1];
			displNow1 = velosNow1 * time[1];
			N[now][i]->deriv->accl[0] += acclNow1;
			N[now][i]->deriv->velos[0] += velosNow1;
			N[now][i]->deriv->displ[0] += displNow1;
			N[now][i]->deriv->coord[0] += displNow1;
		}
	}
}