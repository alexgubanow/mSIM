#pragma once
#include "nodeFreedoms.h"
namespace calcLib
{
	public ref class Node
	{
	public:
		nodeFreedoms nodeFreedom;
		array<array<array<float>^>^>^ deriv;
		Node(nodeFreedoms newnodeFreedom, int counts);
	};
}