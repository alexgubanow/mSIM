#pragma once
#include "ForcePlaceEnum.h"

namespace calcLib
{
	ref class LinearElem
	{
	public:
		LinearElem();
		static void getForce(float E, float A, float l, float l0, array<float>^ force);
	};

};