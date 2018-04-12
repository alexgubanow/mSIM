#include "stdafx.h"
#include "LinearModel.h"

namespace calcLib {
	void LinearModel::Model::calcOneMove(int now, int prev)
	{
		double A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < tM[now]->E->Length; i++)
		{
			/*calc each link*/
			double forceNow1 = tM[now]->P[tM[now]->E[i]->p1]->force[0];
			double displPrev1 = tM[prev]->N[tM[prev]->E[i]->n1]->deriv->displ[0];
			double forceNow2 = tM[now]->P[tM[now]->E[i]->p2]->force[0];
			double displPrev2 = tM[prev]->N[tM[prev]->E[i]->n2]->deriv->displ[0];
			
			forceNow1 = ((_elastic * A / _l) * (displPrev2 - displPrev1));
			forceNow2 = -((_elastic * A / _l) * (displPrev2 - displPrev1));

			tM[now]->P[tM[now]->E[i]->p1]->force[0] = forceNow1;
			tM[now]->P[tM[now]->E[i]->p2]->force[0] = forceNow2;
		}
		for (int i = 1; i < tM[now]->N->Length - 1; i++)
		{
			double ro = 7.8 * Math::Pow(10, 3);
			double massa = ro * A * _l;
			//sum all
			for (int j = 0; j < tM[now]->N[i]->ListOfPoints->Length; j++)
			{
				tM[now]->N[i]->deriv->force[0] += tM[now]->P[tM[now]->N[i]->ListOfPoints[j]]->force[0];
			}
			double acclNow1 = tM[now]->N[i]->deriv->accl[0];
			double velosPrev1 = tM[prev]->N[i]->deriv->velos[0];
			double velosNow1 = tM[now]->N[i]->deriv->velos[0];
			double displNow1 = tM[now]->N[i]->deriv->displ[0];
			acclNow1 = tM[now]->N[i]->deriv->force[0] / massa;
			velosNow1 = acclNow1 * time[1];
			displNow1 = velosNow1 * time[1];
			tM[now]->N[i]->deriv->accl[0] += acclNow1;
			tM[now]->N[i]->deriv->displ[0] += displNow1;
			tM[now]->N[i]->deriv->velos[0] += velosNow1;
		}
	}
}