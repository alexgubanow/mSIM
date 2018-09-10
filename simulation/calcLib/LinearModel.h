#pragma once
#include "loc_glob.h"
#include "Element.h"
#include "Node.h"
#include "axesEnum.h"
#include "DerivEnum.h"

using namespace System;
using namespace System::IO;

namespace calcLib
{
	public ref class LinearModel
	{
	public:
		/*Nodes*/
		array<Node^>^ N;
		/*Elements*/
		array<Element^>^ E;
		/*time array*/
		array<float>^ time;
		float _m;
		float _elastic;
		float _ro;
		float _L;
		float _b;
		float _h;
		float _A;
		int _counts;
		float _dt;
		LinearModel(size_t counts, float dt, int numNodes, int numElements, float ro, float Elast, float lenght, float b, float h);
		static void initTime(size_t counts, float deltaT, array<float>^ %time);
		static void initarrays(int numNodes, int numElements, size_t counts, int demensia, array<Node^>^ %N, array<Element^>^ %E);
		static void initCoords(float elemL, size_t counts, array<Node^>^ %N, array<Element^>^ %E);
		static void initLoad(int freq, float amp, array<float>^ time, array<Node^>^ %N);
		void calcOneStep(int momentNow, int prevMoment);
		void calcMove();
	};
}