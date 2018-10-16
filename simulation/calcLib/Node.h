#pragma once
#include "nodeFreedoms.h"
namespace calcLib
{
	public ref class Node
	{
	public:
		float m;
		float l;
		nodeFreedoms nodeFreedom;
		array<array<array<float>^>^>^ deriv;
		array<int>^ members;
		Node(nodeFreedoms newnodeFreedom, int counts, int maxMembers);
	};
}