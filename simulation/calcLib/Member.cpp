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

void calcLib::Member::getDisturb(array<Node^>^% N, int actNode, int prev, int now, float _dt)
{
	array<float>^ locUactNode = gcnew array<float>(6);
	array<float>^ loocUlinkedNode = gcnew array<float>(6);
	array<float>^ locForce = gcnew array<float>(6);
	array<float>^ globForce = gcnew array<float>(6);
	//translate displ to loc
	preob::to_loc(N[actNode]->deriv[prev][(int)DerivEnum::u], DCM, locUactNode);
	preob::to_loc(N[actNode == n1 ? n2 : n1]->deriv[prev][(int)DerivEnum::u], DCM, loocUlinkedNode);
	//get force of member, in glob
	getForce(locUactNode, loocUlinkedNode, locForce);
	//translate force to glob
	preob::to_glob(locForce, DCM, globForce);
	//put it to node
	for (int i = 0; i < 6; i++)
	{
		N[actNode]->deriv[prev][(int)DerivEnum::force][i] += globForce[i];
	}
}

void calcLib::Member::calcDCM(array<Node^>^ N, int actNode, int t)
{
	switch (MrType)
	{
	case LinElem:
		//calc DCM for linear item
		cosMatrix::getAngles(N[actNode == n1 ? n2 : n1]->deriv[t][(int)DerivEnum::coord], N[actNode == n1 ? n2 : n1]->deriv[t][(int)DerivEnum::coord], l, DCM);
		break;
	}
}

void calcLib::Member::getForce(array<float>^ Ux1, array<float>^ Ux2, array<float>^% memberForce)
{
	switch (MrType)
	{
	case LinElem:
		//calc force of member like of discrete element
		LinearElem::getForce(E, A, l, Ux1, Ux2, memberForce);
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
