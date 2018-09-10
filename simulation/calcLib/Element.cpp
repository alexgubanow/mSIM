#include "stdafx.h"
#include "Element.h"
#include "DerivEnum.h"

calcLib::Element::Element(int n1Index, int n2Index, int counts)
{
	n1 = n1Index;
	n2 = n2Index;
	force = gcnew array<array<float>^>(counts);
	angles = gcnew array<float>(9);
	for (size_t i = 0; i < counts; i++)
	{
		force[i] = gcnew array<float>(3);
	}
}