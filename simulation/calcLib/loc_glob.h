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
	public ref class preob
	{
	public:
		ref class _cos
		{
			static double _L;
			static double _xX;
			static double _xY;
			static double _xZ;
			static double _yX;
			static double _yY;
			static double _yZ;
			static double _zX;
			static double _zY;
			static double _zZ;

			static inline double Xx(double L, double X1, double X2) { return (X2 - X1) / L; };
		public:
			_cos() {};
			~_cos() {};
		};
		static inline double getL(double x1, double x2, double y1, double y2) { return Math::Sqrt(Math::Pow(x2 - x1, 2) + Math::Pow(y2 - y1, 2)); }
		static inline double getCosXx(double L, double x1, double x2) { return (x2 - x1) / L; };
		static inline double getCosYx(double L, double x1, double x2) { return (x2 - x1) / L; };
		static inline double getCosZx(double L, double x1, double x2) { return (x2 - x1) / L; };
		static inline double getCosXy(double L, double x1, double x2) { return (x2 - x1) / L; };
		static inline double getCos(double L, double x1, double x2) { return (x2 - x1) / L; };
		static inline double getCosa(double L, double x1, double x2) { return (x2 - x1) / L; };
		static void to_glob(array<double>^ offset, array<double>^ loc, double sina, double cosa, double L, array<double>^ %glob)
		{
			glob[x] = offset[x] + cosa * loc[x] - sina * loc[y] + 0 * loc[z];
			glob[y] = offset[y] + cosa * loc[y] + sina * loc[x] + 0 * loc[z];
			glob[z] = offset[z] + 0 * loc[y] + 0 * loc[y] + 1 * loc[z];
		}
		static void to_loc(array<double>^ offset, array<double>^ glob, double sina, double cosa, double L, array<double>^ %loc)
		{
			loc[x] = cosa * (glob[x] - offset[x]) + sina * (glob[y] - offset[y]) + 0 * (glob[z] - offset[z]);
			loc[y] = cosa * (glob[y] - offset[y]) - sina * (glob[x] - offset[x]) + 0 * (glob[z] - offset[z]);
			loc[z] = 0 * (glob[x] - offset[x]) + 0 * (glob[y] - offset[y]) + 1 * (glob[z] - offset[z]);
		}
	};
}