#include "stdafx.h"
#include "loc_glob.h"

calcLib::matrixPreob::matrixPreob(array<double>^ p1, array<double>^ p2, double L)
{
	_L = L;
	Xx = _cos(p1[x], p2[x]); Xy = _cos(p1[y], p2[y]); Xz = _cos(p1[z], p2[z]);
	//Yx = _cos(X[0], X[1]); Yy = _cos(Y[0], Y[1]); Yz = _cos(Z[0], Z[1]);
	//Zx = _cos(X[0], X[1]); Zy = _cos(Y[0], Y[1]); Zz = _cos(Z[0], Z[1]);
}
