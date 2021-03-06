#pragma once
#include "calcLib.h"
#include "loc_glob.h"
using namespace System;
using namespace System::IO;

namespace calcLib
{
	public ref class Linear
	{
	public:
		enum class nodeFreedoms { x, y, z, xy, xz, yz, xyz };
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
			matrixPreob^ mP;
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
		ref class Model
		{
			void calcOneMove(int momentNow, int prevMoment);
		public:
			/*time moments*/
			/*Nodes*/
			array<array<Node^>^>^ N;
			/*Elements*/
			array<array<Element^>^>^ E;
			/*Points*/
			array<array<Point^>^>^ P;
			array<double>^ time;
			double _m;
			double _elastic;
			double _ro;
			double _L;
			double _b;
			double _h;
			double _A;
			int _counts;
			double _dt;
			Model(int counts, double dt, int numNodes, int numElements, double ro, double Elast, double lenght, double b, double h)
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
				init::Time(_counts, _dt, time);
				init::arrays(numNodes, numElements, _counts, 3, N,E,P);
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
				static void arrays(int numNodes, int numElements, int counts, int demensia, array<array<Node^>^>^ %N, array<array<Element^>^>^ %E, array<array<Point^>^>^ %P)
				{
					N = gcnew array<array<Node^>^>(counts);
					E = gcnew array<array<Element^>^>(counts);
					P = gcnew array<array<Point^>^>(counts);
					for (int i = 0; i < N->Length; i++)
					{
						N[i] = gcnew array<Node^>(numNodes);
						E[i] = gcnew array<Element^>(numElements);
						P[i] = gcnew array<Point^>(numElements * 2);
						N[i][0] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { 0 }, gcnew array<int>(1) { 0 }, demensia);
						for (int n = 1, p = 1; n < numNodes - 1; n++, p += 2)
						{
							N[i][n] = gcnew Node(nodeFreedoms::x, gcnew array<int>(2) { n - 1, n }, gcnew array<int>(2) { p, p + 1 }, demensia);
						}
						N[i][numNodes - 1] = gcnew Node(nodeFreedoms::x, gcnew array<int>(1) { numNodes - 2 }, gcnew array<int>(2) { numNodes }, demensia);
						for (int e = 0, p = 0; e < numElements; e++, p += 2)
						{
							E[i][e] = gcnew Element(p, p + 1, e, e + 1, demensia);
							P[i][p] = gcnew Point(demensia);
							P[i][p + 1] = gcnew Point(demensia);
						}
					}
				}
				static void Coords(double elemL, array<array<Node^>^>^ %N, array<array<Element^>^>^ %E)
				{
					for (int i = 0; i < N->Length; i++)
					{
						for (int j = 1; j < N[i]->Length; j++)
						{
							N[i][j]->deriv->coord[0] = N[i][j - 1]->deriv->coord[0] + elemL;
							N[i][j]->deriv->coord[1] = N[i][j - 1]->deriv->coord[1] + elemL;
							E[i][j - 1]->mP = gcnew matrixPreob(N[i][j - 1]->deriv->coord, N[i][j]->deriv->coord,
								preob::getL(N[i][j - 1]->deriv->coord[0], N[i][j]->deriv->coord[0], N[i][j - 1]->deriv->coord[1], N[i][j]->deriv->coord[1]));
						}
					}
				}
				static void Load(int freq, double amp, array<double>^ time, array<array<Node^>^>^ %N)
				{
					for (int i = 0; i < time->Length; i++)
					{
						N[i][0]->deriv->displ[0] = amp * Math::Sin(time[i] * 2 * Math::PI * freq);
					}
				}
			};
			
			void calcMove()
			{
				for (int i = 1; i < time->Length; i++)
				{
					calcOneMove(i, i - 1);
				}
			}
		};
	};
}