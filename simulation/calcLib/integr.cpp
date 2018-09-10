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
void calcLib::integr::verlet(array<float>^ lastx, array<float>^ lastv, array<float>^ lasta, array<float>^ F, float deltat, float massa, float l, array<float>^% xp, array<float>^% vp, array<float>^% ap)
{
	ap = gcnew array<float>(3);
	vp = gcnew array<float>(3);
	xp = gcnew array<float>(3);

	ap[0] = F[0] / massa;
	ap[1] = F[1] / massa;
	ap[2] = F[2] / massa * l * l * 0.5f;

	vp[0] = lastv[0] + 0.5f * (lasta[0] + ap[0]) * deltat;
	vp[1] = lastv[1] + 0.5f * (lasta[1] + ap[1]) * deltat;
	vp[2] = lastv[2] + 0.5f * (lasta[2] + ap[2]) * deltat;

	xp[0] = lastx[0] + (lastv[0] * deltat) + 0.5f * lasta[0] * deltat * deltat;
	xp[1] = lastx[1] + (lastv[1] * deltat) + 0.5f * lasta[1] * deltat * deltat;
	xp[2] = lastx[2] + (lastv[2] * deltat) + 0.5f * lasta[2] * deltat * deltat;
}
void calcLib::integr::gearp(array<float>^ lastx, array<float>^ lastv, array<float>^ lasta, array<float>^ lastb, array<float>^ F, float deltat, float massa, float l, array<float>^% xp, array<float>^% vp, array<float>^% ap, array<float>^% bp)
{
	bp = gcnew array<float>(3);
	ap = gcnew array<float>(3);
	vp = gcnew array<float>(3);
	xp = gcnew array<float>(3);
	//array<double>^ bp = gcnew array<double>(3);

	bp[0] = ((F[0] / massa) - lasta[0]) / deltat;
	bp[1] = ((F[1] / massa) - lasta[1]) / deltat;
	bp[2] = ((F[2] / massa * l * l * 0.5f) - lasta[2]) / deltat;

	ap[0] = lasta[0] + lastb[0] * deltat;
	ap[1] = lasta[1] + lastb[1] * deltat;
	ap[2] = lasta[2] + lastb[2] * deltat;

	vp[0] = lastv[0] + lasta[0] * deltat + 1.0f / 2.0f * lastb[0] * deltat * deltat;
	vp[1] = lastv[1] + lasta[1] * deltat + 1.0f / 2.0f * lastb[1] * deltat * deltat;
	vp[2] = lastv[2] + lasta[2] * deltat + 1.0f / 2.0f * lastb[2] * deltat * deltat;

	xp[0] = lastx[0] + lastv[0] * deltat + 1.0f / 2.0f * lasta[0] * deltat * deltat + 1.0f / 6.0f * lastb[0] * deltat * deltat * deltat;
	xp[1] = lastx[1] + lastv[1] * deltat + 1.0f / 2.0f * lasta[1] * deltat * deltat + 1.0f / 6.0f* lastb[1] * deltat * deltat * deltat;
	xp[2] = lastx[2] + lastv[2] * deltat + 1.0f / 2.0f * lasta[2] * deltat * deltat + 1.0f / 6.0f * lastb[2] * deltat * deltat * deltat;
}
void calcLib::integr::gearc(array<float>^ xp, array<float>^ vp, array<float>^ ap, array<float>^ bp, array<float>^ F, double deltat, float massa, float l, array<float>^% xc, array<float>^% vc, array<float>^% ac, array<float>^% bc)
{
	bc = gcnew array<float>(3);
	ac = gcnew array<float>(3);
	vc = gcnew array<float>(3);
	xc = gcnew array<float>(3);

	ac[0] = F[0] / massa;
	ac[1] = F[1] / massa;
	ac[2] = F[2] / massa * l * l * 0.5f;

	array<float>^ deltaa = gcnew array<float>(3);

	deltaa[0] = ac[0] - ap[0];
	deltaa[1] = ac[1] - ap[1];
	deltaa[2] = ac[2] - ap[2];

	xc[0] = xp[0] + c0 * deltaa[0];
	xc[1] = xp[1] + c0 * deltaa[1];
	xc[2] = xp[2] + c0 * deltaa[2];

	vc[0] = vp[0] + c1 * deltaa[0];
	vc[1] = vp[1] + c1 * deltaa[1];
	vc[2] = vp[2] + c1 * deltaa[2];

	ac[0] = ap[0] + c2 * deltaa[0];
	ac[1] = ap[1] + c2 * deltaa[1];
	ac[2] = ap[2] + c2 * deltaa[2];

	bc[0] = bp[0] + c3 * deltaa[0];
	bc[1] = bp[1] + c3 * deltaa[1];
	bc[2] = bp[2] + c3 * deltaa[2];
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