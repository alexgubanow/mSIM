#include "stdafx.h"
#include "Node.h"
#include "DerivEnum.h"
#include "axesEnum.h"

calcLib::Node::Node(nodeFreedoms newnodeFreedom, int counts, int maxMembers)
{
	nodeFreedom = newnodeFreedom;
	deriv = gcnew array<array<array<float>^>^>(counts);
	for (int i = 0; i < counts; i++)
	{
		deriv[i] = gcnew array<array<float>^>((int)DerivEnum::derivCount);
		for (int derv = 0; derv < (int)DerivEnum::derivCount; derv++)
		{
			deriv[i][derv] = gcnew array<float>(6);
		}
	}
	members = gcnew array<int>(maxMembers) { -1 };
}