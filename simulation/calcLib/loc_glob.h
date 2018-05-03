#pragma once
using namespace System;
namespace calcLib
{
	public enum axes
	{
		x = 0,
		y = 1,
		z = 2,
	};
	ref class matrixPreob
	{
		inline double _cos(double p1, double p2) { return (p2 - p1) / _L; };
	public:
		double _L;
		double Xx; double Xy; double Xz;
		double Yx; double Yy; double Yz;
		double Zx; double Zy; double Zz;

		matrixPreob() {};
		matrixPreob(array<double>^ p1, array<double>^ p2, double L);
		~matrixPreob() {};
	};
	public ref class preob
	{
	public:
		static inline double getL(double x1, double x2, double y1, double y2) { return Math::Sqrt(Math::Pow(x2 - x1, 2) + Math::Pow(y2 - y1, 2)); }
		static void to_glob(array<double>^ offset, array<double>^ loc, matrixPreob^ cos, array<double>^ %glob)
		{
			glob[x] = offset[x] + cos->Xx * loc[x] + cos->Yx * loc[y] + cos->Zx * loc[z];
			glob[y] = offset[y] + cos->Xy * loc[y] + cos->Yy * loc[x] + cos->Zy * loc[z];
			glob[z] = offset[z] + cos->Xz * loc[y] + cos->Yz * loc[y] + cos->Zz * loc[z];
		}
		static void to_loc(array<double>^ offset, array<double>^ glob, matrixPreob^ cos, array<double>^ %loc)
		{
			loc[x] = cos->Xx * (glob[x] - offset[x]) + cos->Xy * (glob[y] - offset[y]) + cos->Xz * (glob[z] - offset[z]);
			loc[y] = cos->Yx * (glob[y] - offset[y]) + cos->Yy * (glob[x] - offset[x]) + cos->Yz * (glob[z] - offset[z]);
			loc[z] = cos->Zx * (glob[x] - offset[x]) + cos->Zy * (glob[y] - offset[y]) + cos->Zz * (glob[z] - offset[z]);
		}
	};
}