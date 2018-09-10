#pragma once
using namespace System;
#include "axesEnum.h"
#include "cosEnum.h"

namespace calcLib
{
	public ref class preob
	{
	public:
		static inline float getL(float x1, float x2, float y1, float y2) { return (float)Math::Sqrt((float)Math::Pow(x2 - x1, 2) + (float)Math::Pow(y2 - y1, 2)); }
		static void to_glob(array<float>^ loc, array<float>^ offset, array<float>^ angles, array<float>^% glob);
		static void to_loc(array<float>^ glob, array<float>^ offset, array<float>^ angles, array<float>^% loc);
	};
}