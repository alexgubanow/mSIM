#pragma once
using namespace System;
#include "axesEnum.h"
#include "cosEnum.h"

namespace calcLib
{
	public ref class preob
	{
	public:
		static inline float getL(array<float>^ p1, array<float>^ p2) { return (float)Math::Sqrt((float)Math::Pow(p2[x] - p1[x], 2) + (float)Math::Pow(p2[y] - p1[y], 2) + (float)Math::Pow(p2[z] - p1[z], 2)); }
		static void to_glob(array<float>^ loc, array<float>^ angles, array<float>^% glob);
		static void to_loc(array<float>^ glob, array<float>^ angles, array<float>^% loc);
	};
}