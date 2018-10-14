#include "stdafx.h"
#include "LinearElem.h"
#include "axesEnum.h"
#include "DerivEnum.h"
#include "loc_glob.h"

calcLib::LinearElem::LinearElem()
{
}

void calcLib::LinearElem::getDisturb(float E, float A, float l, array<array<float>^>^ prev, array<array<float>^>^ now)
{
	array<float>^ locU;
	//traslate member movement, to loc
	preob::to_loc(prev[(int)DerivEnum::u], locU);

	//calc force
	getForce();
	//translate force to glob
	preob::to_glob(Finternal, E[i]->force[0], E[i]->angles, now[(int)DerivEnum::force]);
	//integrate it
	integr::euler(N[E[i]->n1]->deriv, prev, now, m, l, _dt);
	integr::euler(N[E[i]->n2]->deriv, prev, now, m, l, _dt);
}

void calcLib::LinearElem::getForce(float E, float A, array<array<float>^>^ prev, array<array<float>^>^ now)
{
	//calc Length of current member
	float l = preob::getL
	(
		E[mIndx]->deriv[prev][(int)DerivEnum::coord][x],
		N[E[i]->n1]->deriv[prev][(int)DerivEnum::coord][y],
		N[E[i]->n2]->deriv[prev][(int)DerivEnum::coord][x],
		N[E[i]->n2]->deriv[prev][(int)DerivEnum::coord][y]
	);
	if (l == 0 || l >= FLT_MAX) { throw gcnew NotFiniteNumberException(); }

	//traslate member movement, to loc
//preob::to_loc(N[E[i]->n1]->deriv[prev][(int)DerivEnum::u], N[E[i]->n1]->deriv[0][(int)DerivEnum::u], E[i]->angles, p1);
//preob::to_loc(N[E[i]->n2]->deriv[prev][(int)DerivEnum::u], N[E[i]->n1]->deriv[0][(int)DerivEnum::u], E[i]->angles, p2);
	//calc force
	array<float>^ Finternal = (E * A / l) * (prev[(int)DerivEnum::u][x] - l));
	now[(int)DerivEnum::force][(int)ForcePlaceEnum::N] =
		//translate force to glob
		preob::to_glob(Finternal, E[i]->force[0], E[i]->angles, now[(int)DerivEnum::force]);
	//integrate it
	integr::euler(N[E[i]->n1]->deriv, prev, now, m, l, _dt);
	integr::euler(N[E[i]->n2]->deriv, prev, now, m, l, _dt);
}