#pragma once

namespace calcLib
{
	public ref class Element
	{
	public:
		int n1;
		int n2;
		array<float>^ angles;
		array<array<float>^>^ force;
		Element(int n1Index, int n2Index, int counts);
	};
}