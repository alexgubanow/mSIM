#include "stdafx.h"
#include "Member.h"
#include "LinearElem.h"
#include "loc_glob.h"
#include "float.h"
#include "DerivEnum.h"
#include "cosMatrix.h"
#include "integr.h"

calcLib::Member::Member(int n1Index, int n2Index, mtEnum MemberType)
{
	MrType = MemberType;
	n1 = n1Index;
	n2 = n2Index;
}

void calcLib::Member::getDisturb(float E, array<Node^>^% N, int actNode, int prev, int now, float _dt)
{
	//get force of member, in glob
	array<array<float>^>^ mDeriv = gcnew array<array<float>^>(6);
	getForce(mDeriv[(int)DerivEnum::force]);
	//integrate it
	integr::euler(mDeriv, prev, now, m, l, _dt);
	//put all deriv to node
}

void calcLib::Member::calcDCM(array<Node^>^ N, int actNode, int t)
{
	switch (MrType)
	{
	case LinElem:
		//calc DCM for linear item
		cosMatrix::getAngles(N[actNode == n1 ? n1 : n2]->deriv[t][(int)DerivEnum::coord], N[actNode == n1 ? n1 : n2]->deriv[t][(int)DerivEnum::coord], l, DCM);
		break;
	}
}

void calcLib::Member::getForce(array<float>^% memberForce)
{
	switch (MrType)
	{
	case LinElem:
		//array<float>^ locU;
		array<float>^ locF;
		////translate to local U of node
		//preob::to_loc(N[actNode]->deriv[prev][(int)DerivEnum::u], N[actNode]->deriv[prev][(int)DerivEnum::u], DCM, locU);
		//calc force of member like of discrete element
		LinearElem::getForce(E, A, l, l0, locF);
		//translate force to glob
		preob::to_glob(locF, DCM, memberForce);
		break;
	}
}

void calcLib::Member::getLength(array<Node^>^ N, int t)
{
	switch (MrType)
	{
	case LinElem:
		//get length
		l = preob::getL(N[n1]->deriv[t][(int)DerivEnum::coord], N[n2]->deriv[t][(int)DerivEnum::coord]);
		if (l == 0 || l >= FLT_MAX) { throw gcnew NotFiniteNumberException(); }
		break;
	}
}
