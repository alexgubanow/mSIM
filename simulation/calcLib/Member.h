#pragma once
#include "MemberTypeEnum.h"
#include "Node.h"

namespace calcLib
{
	public ref class Member
	{
	public:
		float E;
		float A;
		float m;
		float l0;
		float l;
		int n1;
		int n2;
		array<float>^ DCM;
		mtEnum MrType;
		Member(int n1Index, int n2Index, mtEnum MemberType);
		void getDisturb(float E, array<Node^>^% N, int actNode, int prev, int now, float _dt);
		void calcDCM(array<Node^>^ N, int actNode, int t);
		void getForce(array<float>^% memberForce);
		void getLength(array<Node^>^ N, int t);
	};
};