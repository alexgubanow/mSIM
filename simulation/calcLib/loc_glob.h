#pragma once
using namespace System;
namespace calcLib
{
	ref class preob
	{
		static inline double cosa(double l, double x1, double x2) { return (x2 - x1) / l; };
		static inline double sina(double l, double y1, double y2) { return (y2 - y1) / l; };
	public:
		static inline double getL(double x1, double x2, double y1, double y2)
		{
			return Math::Sqrt(Math::Pow(x2 - x1, 2) + Math::Pow(y2 - y1, 2));
		}
		static void to_loc(double cosa, double x_g, array<double>^ %x_l)
		{
			x_l[0] = cosa * x_l[0] + cosa * x_l[1] + cosa * x_l[2];
		}
		static double to_glob(double cosa, array<double>^ x_l)
		{
			return cosa * x_l[0] + cosa * x_l[1] + cosa * x_l[2];
		}
	};
}