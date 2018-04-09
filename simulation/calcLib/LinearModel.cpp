#include "stdafx.h"
#include "LinearModel.h"

namespace calcLib {
	void LinearModel::Model::calcOneMove(int momentNow, int prevMoment)
	{
		double A = _b * _h;
		//overview links of curr node
		for (int i = 0; i < timeMoments[momentNow]->Elements->Length; i++)
		{
			double ro = 7.8 * Math::Pow(10, 3);
			//double ro = 6.12 * Math.Pow(10, 4);
			double massa = ro * A * _l;
			/*calc each link*/
			double forcePrev1 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point1]->derivatives->force[0];
			double acclNow1 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->accl[0];
			double velosPrev1 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point1]->derivatives->velos[0];
			double displPrev1 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point1]->derivatives->displ[0];
			double velosNow1 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->velos[0];
			double displNow1 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->displ[0];

			double forcePrev2 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point2]->derivatives->force[0];
			double acclNow2 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->accl[0];
			double velosPrev2 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point2]->derivatives->velos[0];
			double displPrev2 = timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point2]->derivatives->displ[0];
			double velosNow2 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->velos[0];
			double displNow2 = timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->displ[0];

			forcePrev1 = ((_elastic * A / _l) * (displPrev2 - displPrev1));
			acclNow1 = forcePrev1 / massa;
			velosNow1 = acclNow1 * time[1];
			displNow1 = velosNow1 * time[1];

			forcePrev2 = -((_elastic * A / _l) * (displPrev2 - displPrev1));
			acclNow2 = forcePrev2 / massa;
			velosNow2 = acclNow2 * time[1];
			displNow2 = velosNow2 * time[1];

			timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point1]->derivatives->force[0] += forcePrev1;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->accl[0] += acclNow1;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->displ[0] += displNow1;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point1]->derivatives->velos[0] += velosNow1;

			timeMoments[prevMoment]->Points[timeMoments[prevMoment]->Elements[i]->point2]->derivatives->force[0] += forcePrev2;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->accl[0] += acclNow2;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->velos[0] += velosNow2;
			timeMoments[momentNow]->Points[timeMoments[momentNow]->Elements[i]->point2]->derivatives->displ[0] += displNow2;
		}
		for (int i = 0; i < timeMoments[momentNow]->Nodes->Length - 1; i++)
		{
			//sum all
			for (int j = 0; j < timeMoments[momentNow]->Nodes[i]->ListOfPoints->Length; j++)
			{
				timeMoments[momentNow]->Nodes[i]->derivatives->force[0] += timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->force[0];
				timeMoments[momentNow]->Nodes[i]->derivatives->accl[0] += timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->accl[0];
				timeMoments[momentNow]->Nodes[i]->derivatives->velos[0] += timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->velos[0];
				timeMoments[momentNow]->Nodes[i]->derivatives->displ[0] += timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->displ[0];
				timeMoments[momentNow]->Nodes[i]->derivatives->coord[0] += timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->coord[0];
			}
			//update final value of points inside node
			for (int j = 0; j < timeMoments[momentNow]->Nodes[i]->ListOfPoints->Length; j++)
			{
				timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->force[0] = timeMoments[momentNow]->Nodes[i]->derivatives->force[0];
				timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->accl[0] = timeMoments[momentNow]->Nodes[i]->derivatives->accl[0];
				timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->velos[0] = timeMoments[momentNow]->Nodes[i]->derivatives->velos[0];
				timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->displ[0] = timeMoments[momentNow]->Nodes[i]->derivatives->displ[0];
				timeMoments[momentNow]->Points[timeMoments[momentNow]->Nodes[i]->ListOfPoints[j]]->derivatives->coord[0] = timeMoments[momentNow]->Nodes[i]->derivatives->coord[0];
			}
		}
	}
}