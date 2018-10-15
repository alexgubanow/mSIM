#include "stdafx.h"
#include "Member.h"
#include "LinearElem.h"
#include "loc_glob.h"
#include "float.h"
#include "DerivEnum.h"
#include "cosMatrix.h"


calcLib::Member::Member(int n1Index, int n2Index, mtEnum MemberType)
{
	MrType = MemberType;
	nodes = gcnew array<int>(2) { n1Index, n2Index };
}

void calcLib::Member::getDisturb(float E, float A, array<Node^>^% N, int prev, int now)
{
		array<array<float>^>^ DCM;
		cosMatrix::getAngles(N[nodes[0]]->deriv[prev][(int)DerivEnum::coord], N[nodes[1]]->deriv[prev][(int)DerivEnum::coord], l, DCM);
	switch (MrType)
	{
	case LinElem:
		//get length
		float l = preob::getL(N[nodes[0]]->deriv[prev][(int)DerivEnum::coord], N[nodes[1]]->deriv[prev][(int)DerivEnum::coord]);
		if (l == 0 || l >= FLT_MAX) { throw gcnew NotFiniteNumberException(); }
		//calc DCM for it
		//calc force of member like of discrete element
		LinearElem::getDisturb(E,A,l, N[nodes[0]]->deriv[prev], N[nodes[0]]->deriv[now]);
		break;
	case pointLoad:
		//get force of point loading
		break;
	case Pressure:
		//get force of lodaing by pressure
		break;
	}
}
