#include "stdafx.h"
#include "cosMatrix.h"
#include "axesEnum.h"
#include "cosEnum.h"

void calcLib::cosMatrix::getAngles(array<float>^ p1, array<float>^ p2, float L, array<float>^% angle)
{
	angle[(int)cosEnum::Xx] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Xy] = _cos(p1[y], p2[y], L); angle[(int)cosEnum::Xz] = _cos(p1[z], p2[x], L);
	angle[(int)cosEnum::Yx] = _cos(p2[y], p1[y], L); angle[(int)cosEnum::Yy] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Yz] = _cos(p1[z], p2[y], L);
	angle[(int)cosEnum::Zx] = _cos(p1[x], p2[z], L); angle[(int)cosEnum::Zy] = _cos(p1[y], p2[z], L); angle[(int)cosEnum::Zz] = _cos(p1[z], p2[z], L);
}
