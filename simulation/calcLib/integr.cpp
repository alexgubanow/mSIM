#include "stdafx.h"
#include "integr.h"
//void integr::get_xvab_from_coords(size_t demensia, Derivatives ^ prevState, Derivatives ^% currState)
	//{
	//	for (size_t i = 0; i < demensia; i++)
	//	{
	//		/*xp[i] = lastx[i] + (newcoords[i] - lastcoords[i]) / dt;
	//		vp[i] = lastv[i] + (xp[i] - lastx[i]) / dt;
	//		ap[i] = lasta[i] + (vp[i] - lastv[i]) / dt;*/
	//	}
	//}
inline float calcLib::integr::FtoA(float massa, float force, ForcePlaceEnum fp, float l)
{
	switch (fp)
	{
	case ForcePlaceEnum::N:
		return force / massa;
	case ForcePlaceEnum::Qy:
		return force / massa;
	case ForcePlaceEnum::Qz:
		return force / massa;
	case ForcePlaceEnum::Mx:
		return force / massa * l * l * 0.5f;
	case ForcePlaceEnum::My:
		return force / massa * l * l * 0.5f;
	case ForcePlaceEnum::Mz:
		return force / massa * l * l * 0.5f;
	default:
		return 13;
	}
}
void calcLib::integr::verlet(array<array<array<float>^>^>^ %deriv, int prev, int now, float massa, float l, float dt)
{
	for (int ax = 0; ax < 3; ax++)
	{
		deriv[now][(int)DerivEnum::a][ax] = FtoA(massa, deriv[now][(int)DerivEnum::force][ax], (ForcePlaceEnum)ax, l);
		deriv[now][(int)DerivEnum::v][ax] = 0.5f * (deriv[prev][(int)DerivEnum::a][ax] + deriv[now][(int)DerivEnum::a][ax]) * dt;
		deriv[now][(int)DerivEnum::u][ax] = deriv[now][(int)DerivEnum::v][ax] * dt + 0.5f * deriv[now][(int)DerivEnum::a][ax] * dt * dt;
		deriv[now][(int)DerivEnum::coord][ax] = deriv[prev][(int)DerivEnum::coord][ax] + deriv[now][(int)DerivEnum::u][ax];
	}
}
void calcLib::integr::gearp(array<array<float>^>^ %derivP, float massa, array<float>^ lastA, array<float>^ lastC, float l, float dt)
{
	for (int ax = 0; ax < 3; ax++)
	{
		derivP[(int)DerivEnum::a][ax] = FtoA(massa, derivP[(int)DerivEnum::force][ax], (ForcePlaceEnum)ax, l);
		derivP[(int)DerivEnum::j][ax] = (derivP[(int)DerivEnum::a][ax] - lastA[ax]) / dt;
		derivP[(int)DerivEnum::v][ax] = derivP[(int)DerivEnum::a][ax] * dt + 0.5f * derivP[(int)DerivEnum::j][ax] * dt * dt;
		derivP[(int)DerivEnum::u][ax] = derivP[(int)DerivEnum::v][ax] * dt + 0.5f * derivP[(int)DerivEnum::a][ax] * dt * dt + (1.0f / 6.0f) * derivP[(int)DerivEnum::a][ax] * dt * dt * dt;
		derivP[(int)DerivEnum::coord][ax] = lastC[ax] + derivP[(int)DerivEnum::u][ax];
	}
}
void calcLib::integr::gearc(array<array<array<float>^>^>^ %deriv, array<array<float>^>^ derivP, int prev, int now, float massa, float l, float dt)
{
	array<float>^ deltaa = gcnew array<float>(3);
	for (int ax = 0; ax < 3; ax++)
	{
		deriv[now][(int)DerivEnum::a][ax] = FtoA(massa, deriv[now][(int)DerivEnum::force][ax], (ForcePlaceEnum)ax, l);
		deltaa[0] = deriv[now][(int)DerivEnum::a][ax] - derivP[(int)DerivEnum::a][ax];
	}
	for (int ax = 0; ax < 3; ax++)
	{
		deriv[now][(int)DerivEnum::j][ax] = derivP[(int)DerivEnum::j][ax] + c3 * deltaa[0];
		deriv[now][(int)DerivEnum::a][ax] = derivP[(int)DerivEnum::a][ax] + c2 * deltaa[0];
		deriv[now][(int)DerivEnum::v][ax] = derivP[(int)DerivEnum::v][ax] + c1 * deltaa[0];
		deriv[now][(int)DerivEnum::u][ax] = derivP[(int)DerivEnum::u][ax] + c0 * deltaa[0];
		deriv[now][(int)DerivEnum::coord][ax] = deriv[prev][(int)DerivEnum::coord][ax] + deriv[now][(int)DerivEnum::u][ax];
	}
}
void calcLib::integr::get_coordsvab_from_dipl(array<float>^ xp, array<float>^ lastcoords, array<float>^ lastx, array<float>^ lastv, array<float>^ lasta, float dt, array<float>^% coords, array<float>^% vp, array<float>^% ap)
{
	ap = gcnew array<float>(3);
	vp = gcnew array<float>(3);
	coords = gcnew array<float>(3);

	coords[0] = xp[0] + lastcoords[0];
	coords[1] = xp[1] + lastcoords[1];
	coords[2] = xp[2] + lastcoords[2];

	vp[0] = lastv[0] + (xp[0] - lastx[0]) / dt;
	vp[1] = lastv[1] + (xp[1] - lastx[1]) / dt;
	vp[2] = lastv[2] + (xp[2] - lastx[2]) / dt;

	ap[0] = lasta[0] + (vp[0] - lastv[0]) / dt;
	ap[1] = lasta[1] + (vp[1] - lastv[1]) / dt;
	ap[2] = lasta[2] + (vp[2] - lastv[2]) / dt;
}
void calcLib::integr::euler(array<array<array<float>^>^>^ %deriv, int prev, int now, float massa, float l, float dt)
{
	for (int ax = 0; ax < 3; ax++)
	{
		deriv[now][(int)DerivEnum::a][ax] = FtoA(massa, deriv[now][(int)DerivEnum::force][ax], (ForcePlaceEnum)ax, l);
		deriv[now][(int)DerivEnum::v][ax] = deriv[now][(int)DerivEnum::a][ax] * dt;
		deriv[now][(int)DerivEnum::u][ax] = deriv[now][(int)DerivEnum::v][ax] * dt;
		deriv[now][(int)DerivEnum::coord][ax] = deriv[prev][(int)DerivEnum::coord][ax] + deriv[now][(int)DerivEnum::u][ax];
	}
}