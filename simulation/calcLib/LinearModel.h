#pragma once
#include "calcLib.h"
using namespace System;
using namespace System::IO;

namespace calcLib
{
	public ref class LinearModel
	{
		static double _elastic = 215 * Math::Pow(10, 9);
	public:
		enum class nodeFreedoms { x, y, z, xy, xz, yz, xyz };
		//derivatives

		ref class Point
		{
		public:
			Derivatives ^ derivatives;
			Point(int demesia)
			{
				derivatives = gcnew Derivatives(demesia);
			}
		};

		ref class Element
		{
		public:
			int point1;
			int point2;
			Element(int point1Index, int point2Index, int demesia)
			{
				point1 = point1Index;
				point2 = point2Index;
			}
		};
		ref class Node
		{
		public:
			nodeFreedoms nodeFreedom;
			array<int>^ ListOfLinks;
			array<int>^ ListOfPoints;
			Derivatives^ derivatives;
			Node(nodeFreedoms newnodeFreedom, array<int>^ newListOfLinks, array<int>^ newListOfPoints, int demesia)
			{
				nodeFreedom = newnodeFreedom;
				ListOfLinks = newListOfLinks;
				ListOfPoints = newListOfPoints;
				derivatives = gcnew Derivatives(demesia);
			}
		};

		ref class timeMoment
		{
		public:
			array<Node^>^ Nodes;
			array<Element^>^ Elements;
			array<Point^>^ Points;
			timeMoment(int numNodes, int numElements, int demesia)
			{
				Nodes = gcnew array<Node^>(numNodes);
				Elements = gcnew array<Element^>(numElements);
				Points = gcnew array<Point^>(numElements * 2);
				for (int i = 0, j = 0; i < numElements; i++, j += 2)
				{
					Elements[i] = gcnew Element(j, j + 1, demesia);
					Points[j] = gcnew Point(3);
					Points[j + 1] = gcnew Point(3);
				}
				Nodes[0] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { 0 }, gcnew array<int>(1) { 0 }, demesia);
				for (int i = 1, j = 1; i < numNodes - 1; i++, j += 2)
				{
					Nodes[i] = gcnew Node(nodeFreedoms::x, gcnew array<int>(2) { i - 1, i }, gcnew array<int>(2) { j, j + 1 }, demesia);
				}
				Nodes[numNodes - 1] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { numNodes - 2 }, gcnew array<int>(2) { numNodes }, demesia);
			}
		};
		ref class Model
		{
			void calcOneMove(int momentNow, int prevMoment);

			void euler(Derivatives^ prevMoment, Derivatives^ %moment, double deltat, double massa, double l)
			{
				if (moment->force[0] != 0)
				{
					moment->accl[0] = prevMoment->accl[0] + moment->force[0] / massa;
					moment->velos[0] = prevMoment->velos[0] + moment->accl[0] * deltat;
					moment->displ[0] = prevMoment->displ[0] + moment->velos[0] * deltat;
					moment->coord[0] = prevMoment->coord[0] + moment->displ[0];
				}
				//ap[2] = F[2] / massa * l * l * 0.5;
			};
		public:
			array<timeMoment^>^ timeMoments;
			array<double>^ time;
			double _m;
			double _l;
			double _b;
			double _h;
			int _counts;
			double _dt;
			Model(int counts, double dt, int numNodes, int numElements, double massa, double lenght, double b, double h)
			{
				_m = massa;
				_l = lenght;
				_b = b;
				_h = h;
				_counts = counts;
				_dt = dt;
				initTime();
				initTimeMoments(numNodes, numElements);
			}
			void initTime()
			{
				time = gcnew array<double>(_counts);
				for (int i = 1; i < _counts; i++)
				{
					time[i] = time[i - 1] + _dt;
				}
			}
			void initTimeMoments(int numNodes, int numElements)
			{
				timeMoments = gcnew array<timeMoment^>(_counts);
				for (int i = 0; i < _counts; i++)
				{
					timeMoments[i] = gcnew timeMoment(numNodes, numElements, 3);
				}
			}
			void applyLoad(int freq, double amp)
			{
				for (int i = 0; i < timeMoments->Length; i++)
				{
					timeMoments[i]->Nodes[0]->derivatives->displ[0] = amp * Math::Sin(time[i] * 2 * Math::PI * freq);
					for (int j = 0; j < timeMoments[i]->Nodes[0]->ListOfPoints->Length; j++)
					{
						timeMoments[i]->Points[timeMoments[i]->Nodes[0]->ListOfPoints[j]]->derivatives->displ[0] = timeMoments[i]->Nodes[0]->derivatives->displ[0];
					}
				}
			}
			void calcMove()
			{
				for (int i = 1; i < timeMoments->Length; i++)
				{
					calcOneMove(i, i - 1);
				}
			}
		};
	};
}