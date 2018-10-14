#pragma once
#include "MemberTypeEnum.h"

namespace calcLib
{
	ref class Member
	{
	public:
		array<int>^ nodes;
		mtEnum MrType;
		Member(int n1Index, int n2Index, mtEnum MemberType);
		void getDisturb(array<array<array<float>^>^>^ %deriv, int prev, int now);
	};
};