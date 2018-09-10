#pragma once
namespace calcLib
{
	public ref class cosMatrix
	{
		static inline float _cos(float p1, float p2, float l) { return (p2 - p1) / l; };
	public:
		static void getAngles(array<float>^ p1, array<float>^ p2, float L, array<float>^% angle);
	};
}