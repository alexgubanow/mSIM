#pragma once
namespace calcLib
{
	public enum class loadType { force, displ };

	public enum class loadDirect { vert, x, y, z };

	public enum class models { linear, nonlinear, particles };

	enum class ForcePlace { N, Qy, Qz, Mx, My, Mz };

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