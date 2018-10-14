#include "stdafx.h"
#include "Member.h"
#include "LinearElem.h"
#include "loc_glob.h"
#include "float.h"
#include "DerivEnum.h"


calcLib::Member::Member(int n1Index, int n2Index, mtEnum MemberType)
{
	MrType = MemberType;
	nodes = gcnew array<int>(2) { n1Index, n2Index };
}

void calcLib::Member::getDisturb(array<array<array<float>^>^>^ %deriv, int prev, int now)
{
	switch (MrType)
	{
	case LinElem:
		//get lenght
		float l = preob::getL(deriv[prev][(int)DerivEnum::coord], deriv[prev][(int)DerivEnum::coord]);
		if (l == 0 || l >= FLT_MAX) { throw gcnew NotFiniteNumberException(); }
		//calc DCM for it
		cosMatrix::getAngles();
		//calc force of member like of discrete element
		LinearElem::getForce();
		break;
	case pointLoad:
		//get force of point loading
		break;
	case Pressure:
		//get force of lodaing by pressure
		break;
	}
}
