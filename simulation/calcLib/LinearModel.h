#pragma once
#include "calcLib.h"
#include "loc_glob.h"
using namespace System;
using namespace System::IO;

namespace calcLib
{
	public ref class Linear
	{
		static double _elastic = 215 * Math::Pow(10, 9);
	public:
		enum class nodeFreedoms { x, y, z, xy, xz, yz, xyz };
		//derivatives

		ref class Point
		{
		public:
			/*Derivatives*/
			array<double>^ force;
			Point(int demesia)
			{
				force = gcnew array<double>(demesia);
			}
		};

		ref class Element
		{
		public:
			int p1;
			int p2;
			int n1;
			int n2;
			Element(int p1Index, int p2Index, int n1Index, int n2Index, int demesia)
			{
				p1 = p1Index;
				p2 = p2Index;
				n1 = n1Index;
				n2 = n2Index;
			}
		};
		ref class Node
		{
		public:
			nodeFreedoms nodeFreedom;
			array<int>^ ListOfLinks;
			array<int>^ ListOfPoints;
			Derivatives^ deriv;
			Node(nodeFreedoms newnodeFreedom, array<int>^ newListOfLinks, array<int>^ newListOfPoints, int demesia)
			{
				nodeFreedom = newnodeFreedom;
				ListOfLinks = newListOfLinks;
				ListOfPoints = newListOfPoints;
				deriv= gcnew Derivatives(demesia);
			}
		};

		ref class timeMoment
		{
		public:
			/*Nodes*/
			array<Node^>^ N;
			/*Elements*/
			array<Element^>^ E;
			/*Points*/
			array<Point^>^ P;
			timeMoment(int numNodes, int numElements, int demesia)
			{
				N = gcnew array<Node^>(numNodes);
				E = gcnew array<Element^>(numElements);
				P = gcnew array<Point^>(numElements * 2);
				for (int i = 0, j = 0; i < numElements; i++, j += 2)
				{
					E[i] = gcnew Element(j, j + 1, i, i + 1, demesia);
					P[j] = gcnew Point(demesia);
					P[j + 1] = gcnew Point(demesia);
				}
				N[0] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { 0 }, gcnew array<int>(1) { 0 }, demesia);
				for (int i = 1, j = 1; i < numNodes - 1; i++, j += 2)
				{
					N[i] = gcnew Node(nodeFreedoms::x, gcnew array<int>(2) { i - 1, i }, gcnew array<int>(2) { j, j + 1 }, demesia);
				}
				N[numNodes - 1] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { numNodes - 2 }, gcnew array<int>(2) { numNodes }, demesia);
			}
		};
		ref class Model
		{
			void calcOneMove(int momentNow, int prevMoment);
		public:
			/*time moments*/
			array<timeMoment^>^ tM;
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
				init::Time(_counts, _dt, time);
				init::TimeMoments(numNodes, numElements, _counts, 3, tM);
			}
			ref class init
			{
			public:
				static void Time(int counts, double deltaT, array<double>^ %time)
				{
					time = gcnew array<double>(counts);
					for (int i = 1; i < counts; i++)
					{
						time[i] = time[i - 1] + deltaT;
					}
				}
				static void TimeMoments(int numNodes, int numElements, int counts, int demensia, array<timeMoment^>^ %tM)
				{
					tM = gcnew array<timeMoment^>(counts);
					for (int i = 0; i < counts; i++)
					{
						tM[i] = gcnew timeMoment(numNodes, numElements, demensia);
					}
				}
				static void Coords(double elemL, array<timeMoment^>^ %tM)
				{
					for (int i = 0; i < tM->Length; i++)
					{
						
					}
				}
				static void Load(int freq, double amp, array<double>^ time, array<timeMoment^>^ %tM)
				{
					for (int i = 0; i < tM->Length; i++)
					{
						tM[i]->N[0]->deriv->displ[0] = amp * Math::Sin(time[i] * 2 * Math::PI * freq);
					}
				}
			};
			
			void calcMove()
			{
				for (int i = 1; i < tM->Length; i++)
				{
					calcOneMove(i, i - 1);
				}
			}
		};
	};
}