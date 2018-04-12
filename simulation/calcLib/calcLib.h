#pragma once
namespace calcLib
{
	public enum class models
	{
		linear = 0,
		nonlinear = 1,
		particles = 2
	};
	enum class ForcePlace
	{
		N = 0,
		Qy = 1,
		Qz = 2,
		Mx = 3,
		My = 4,
		Mz = 5
	};
	public ref class Derivatives
	{
	public:
		array<double>^ coord;
		array<double>^ force;
		array<double>^ displ;
		array<double>^ velos;
		array<double>^ accl;
		array<double>^ jerk;
		Derivatives(int demesia)
		{
			coord = gcnew array<double>(demesia);
			force = gcnew array<double>(demesia);
			displ = gcnew array<double>(demesia);
			velos = gcnew array<double>(demesia);
			accl = gcnew array<double>(demesia);
			jerk = gcnew array<double>(demesia);
		}
	};
}