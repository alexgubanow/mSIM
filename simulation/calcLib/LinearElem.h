#pragma once
#include "ForcePlaceEnum.h"

namespace calcLib
{
	ref class LinearElem
	{
	public:
		LinearElem();
		static void getForce(float E, float A, float l, array<float>^ Ux1, array<float>^ Ux2, array<float>^% force);
	};

};