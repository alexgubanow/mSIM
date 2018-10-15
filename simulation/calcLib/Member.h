#pragma once
#include "MemberTypeEnum.h"
#include "Node.h"

namespace calcLib
{
	ref class Member
	{
	public:
		array<int>^ nodes;
		mtEnum MrType;
		Member(int n1Index, int n2Index, mtEnum MemberType);
		void getDisturb(float E, float A, array<Node^>^% N, int prev, int now);
	};
};