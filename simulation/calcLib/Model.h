#pragma once
#include "loc_glob.h"
#include "Member.h"
#include "Node.h"
#include "axesEnum.h"
#include "DerivEnum.h"

using namespace System;
using namespace System::IO;

namespace calcLib
{
	public ref class Model
	{
	public:
		/*Nodes*/
		array<Node^>^ N;
		/*Elements*/
		array<Member^>^ Mr;
		/*time array*/
		array<float>^ time;
		float _E;
		float _ro;
		float _b;
		float _h;
		int _counts;
		float _dt;
		int _maxMembers;
		Model(int counts, float dt, int numNodes, int maxMembers, float ro, float E, float b, float h);
		void initTime(float deltaT, array<float>^ %time);
		void initarrays(int numNodes, array<Node^>^ %N, array<Member^>^ %Mr);
		void initCoords(float elemL, array<Node^>^ %N);
		void initLoad(int freq, float amp, array<float>^ time, array<Node^>^ %N);
		void calcOneStep(int momentNow, int prevMoment);
		void calcMove();
	};
}