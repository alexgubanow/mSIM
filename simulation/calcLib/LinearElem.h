#pragma once
#include "ForcePlaceEnum.h"

namespace calcLib
{
	ref class LinearElem
	{
	public:
		LinearElem();
		void getDisturb(float E, float A, float l, array<array<float>^>^ prev, array<array<float>^>^ now);
		static void getForce(float E, float A, float l, array<float>^ Ux1, array<float>^ Ux2);
	};

};