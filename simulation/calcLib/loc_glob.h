#pragma once
using namespace System;
namespace calcLib
{
	ref class preob
	{
		inline double cosa(double l, double x_g1, double x_g2) { return (x_g2 - x_g1) / l; };
	public:
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