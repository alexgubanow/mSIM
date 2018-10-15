#include "stdafx.h"
#include "cosMatrix.h"
#include "axesEnum.h"
#include "cosEnum.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

inline float calcLib::cosMatrix::_cos(float p1, float p2, float l) { return (p2 - p1) / l; }
/*
	angle[(int)cosEnum::Xx] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Xy] = _cos(p1[y], p2[y], L); angle[(int)cosEnum::Xz] = _cos(p1[z], p2[x], L);
	angle[(int)cosEnum::Yx] = _cos(p2[y], p1[y], L); angle[(int)cosEnum::Yy] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Yz] = _cos(p1[z], p2[y], L);
	angle[(int)cosEnum::Zx] = _cos(p1[x], p2[z], L); angle[(int)cosEnum::Zy] = _cos(p1[y], p2[z], L); angle[(int)cosEnum::Zz] = _cos(p1[z], p2[z], L);
	*/



void calcLib::cosMatrix::getAngles(array<float>^ p1, array<float>^ p2, float L, array<float>^% angle)
{
	/*angle[(int)cosEnum::Xx] = cosA * cosB;
	angle[(int)cosEnum::Xy] = cosA * sinB * sinG - cosG * sinA;
	angle[(int)cosEnum::Xz] = sinA * sinG + cosA * cosG*sinB;

	angle[(int)cosEnum::Yx] = cosB * sinA;
	angle[(int)cosEnum::Yy] = sinA * sinB * sinG + cosA * cosG;
	angle[(int)cosEnum::Yz] = cosG * sinA*sinB - cosA * sinG;

	angle[(int)cosEnum::Zx] = 0 - sinB;
	angle[(int)cosEnum::Zy] = cosB * sinG;
	angle[(int)cosEnum::Zz] = cosB * cosG;*/

	/*angle[x][x] = cosA * cosB;
	angle[x][x] = cosB * sinA;
	angle[x][x] = 0 - sinB;

	angle[x][x] = cosA * sinB * sinG - cosG * sinA;
	angle[x][x] = sinA * sinB * sinG + cosA * cosG;
	angle[x][x] = cosB * sinG;

	angle[x][x] = sinA * sinG + cosA * cosG*sinB;
	angle[x][x] = cosG * sinA*sinB - cosA * sinG;
	angle[x][x] = cosB * cosG;*/
}