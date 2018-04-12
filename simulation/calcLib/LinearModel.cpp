#include "stdafx.h"
#include "LinearModel.h"

namespace calcLib {
	void LinearModel::Model::calcOneMove(int now, int prev)
	{
		double A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < tM[now]->E->Length; i++)
		{
			double ro = 7.8 * Math::Pow(10, 3);
			//double ro = 6.12 * Math.Pow(10, 4);
			double massa = ro * A * _l;
			/*calc each link*/
			double forcePrev1 = tM[prev]->P[tM[prev]->E[i]->p1]->deriv->force[0];
			double acclNow1 = tM[now]->P[tM[now]->E[i]->p1]->deriv->accl[0];
			double velosPrev1 = tM[prev]->P[tM[prev]->E[i]->p1]->deriv->velos[0];
			double displPrev1 = tM[prev]->P[tM[prev]->E[i]->p1]->deriv->displ[0];
			double velosNow1 = tM[now]->P[tM[now]->E[i]->p1]->deriv->velos[0];
			double displNow1 = tM[now]->P[tM[now]->E[i]->p1]->deriv->displ[0];

			double forcePrev2 = tM[prev]->P[tM[prev]->E[i]->p2]->deriv->force[0];
			double acclNow2 = tM[now]->P[tM[now]->E[i]->p2]->deriv->accl[0];
			double velosPrev2 = tM[prev]->P[tM[prev]->E[i]->p2]->deriv->velos[0];
			double displPrev2 = tM[prev]->P[tM[prev]->E[i]->p2]->deriv->displ[0];
			double velosNow2 = tM[now]->P[tM[now]->E[i]->p2]->deriv->velos[0];
			double displNow2 = tM[now]->P[tM[now]->E[i]->p2]->deriv->displ[0];

			forcePrev1 = ((_elastic * A / _l) * (displPrev2 - displPrev1));
			acclNow1 = forcePrev1 / massa;
			velosNow1 = acclNow1 * time[1];
			displNow1 = velosNow1 * time[1];

			forcePrev2 = -((_elastic * A / _l) * (displPrev2 - displPrev1));
			acclNow2 = forcePrev2 / massa;
			velosNow2 = acclNow2 * time[1];
			displNow2 = velosNow2 * time[1];

			tM[prev]->P[tM[prev]->E[i]->p1]->deriv->force[0] += forcePrev1;
			tM[now]->P[tM[now]->E[i]->p1]->deriv->accl[0] += acclNow1;
			tM[now]->P[tM[now]->E[i]->p1]->deriv->displ[0] += displNow1;
			tM[now]->P[tM[now]->E[i]->p1]->deriv->velos[0] += velosNow1;

			tM[prev]->P[tM[prev]->E[i]->p2]->deriv->force[0] += forcePrev2;
			tM[now]->P[tM[now]->E[i]->p2]->deriv->accl[0] += acclNow2;
			tM[now]->P[tM[now]->E[i]->p2]->deriv->velos[0] += velosNow2;
			tM[now]->P[tM[now]->E[i]->p2]->deriv->displ[0] += displNow2;
		}
		for (int i = 0; i < tM[now]->N->Length - 1; i++)
		{
			//sum all
			for (int j = 0; j < tM[now]->N[i]->ListOfPoints->Length; j++)
			{
				tM[now]->N[i]->deriv->force[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->force[0];
				tM[now]->N[i]->deriv->accl[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->accl[0];
				tM[now]->N[i]->deriv->velos[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->velos[0];
				tM[now]->N[i]->deriv->displ[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->displ[0];
				tM[now]->N[i]->deriv->coord[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->coord[0];
			}
			//update final value of P inside node
			for (int j = 0; j < tM[now]->N[i]->ListOfPoints->Length; j++)
			{
				tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->force[0] = tM[now]->N[i]->deriv->force[0];
				tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->accl[0] = tM[now]->N[i]->deriv->accl[0];
				tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->velos[0] = tM[now]->N[i]->deriv->velos[0];
				tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->displ[0] = tM[now]->N[i]->deriv->displ[0];
				tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->deriv->coord[0] = tM[now]->N[i]->deriv->coord[0];
			}
		}
	}
}