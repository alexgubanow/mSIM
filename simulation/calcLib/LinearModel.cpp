#include "stdafx.h"
#include "LinearModel.h"

namespace calcLib {
	void Linear::Model::calcOneMove(int now, int prev)
	{
		double A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < E[now]->Length; i++)
		{
			double forceNow1 = P[now][E[now][i]->p1]->force[0];
			double forceNow2 = P[now][E[now][i]->p2]->force[0];
			double displPrev1 = N[prev][E[now][i]->n1]->deriv->displ[0];
			double displPrev2 = N[prev][E[now][i]->n2]->deriv->displ[0];
			/*transform displ from glob to loc*/
			//double L = preob::getL();
			
			forceNow1 = ((_elastic * A / _l) * (displPrev2 - displPrev1));
			forceNow2 = -((_elastic * A / _l) * (displPrev2 - displPrev1));

			P[now][E[now][i]->p1]->force[0] = forceNow1;
			P[now][E[now][i]->p2]->force[0] = forceNow2;
		}
		for (int i = 1; i < N[now]->Length - 1; i++)
		{
			double ro = 7.8 * Math::Pow(10, 3);
			double massa = ro * A * _l;
			//sum all
			for (int j = 0; j < N[now][i]->ListOfPoints->Length; j++)
			{
				N[now][i]->deriv->force[0] += P[now][N[now][i]->ListOfPoints[j]]->force[0];
			}
			double acclNow1 = N[now][i]->deriv->accl[0];
			double velosPrev1 = N[prev][i]->deriv->velos[0];
			double velosNow1 = N[now][i]->deriv->velos[0];
			double displNow1 = N[now][i]->deriv->displ[0];
			acclNow1 = N[now][i]->deriv->force[0] / massa;
			velosNow1 = acclNow1 * time[1];
			displNow1 = velosNow1 * time[1];
			N[now][i]->deriv->accl[0] += acclNow1;
			N[now][i]->deriv->velos[0] += velosNow1;
			N[now][i]->deriv->displ[0] += displNow1;
			N[now][i]->deriv->coord[0] += displNow1;
		}
	}
}