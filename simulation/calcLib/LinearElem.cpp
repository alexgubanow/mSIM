#include "stdafx.h"
#include "LinearElem.h"
#include "axesEnum.h"
#include "DerivEnum.h"
#include "loc_glob.h"

calcLib::LinearElem::LinearElem()
{
}

void calcLib::LinearElem::getForce(float E, float A, float l, array<float>^ Ux1, array<float>^ Ux2, array<float>^% force)
{
	//calc force(E * A / l0) * (l - l0)
	force[(int)ForcePlaceEnum::N] = (E * A / l) * (Ux2[x] - Ux1[x]);
}