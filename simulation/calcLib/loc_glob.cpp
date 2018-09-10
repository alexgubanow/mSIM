#include "stdafx.h"
#include "loc_glob.h"

void calcLib::preob::to_glob(array<float>^ loc, array<float>^ offset, array<float>^ angles, array<float>^% glob)
{
	glob[x] = offset[x] + angles[(int)cosEnum::Xx] * loc[x] + angles[(int)cosEnum::Xy] * loc[y] + angles[(int)cosEnum::Xz] * loc[z];
	glob[y] = offset[y] + angles[(int)cosEnum::Yx] * loc[y] + angles[(int)cosEnum::Yy] * loc[x] + angles[(int)cosEnum::Yx] * loc[z];
	glob[z] = offset[z] + angles[(int)cosEnum::Zx] * loc[y] + angles[(int)cosEnum::Zy] * loc[y] + angles[(int)cosEnum::Zz] * loc[z];
}

void calcLib::preob::to_loc(array<float>^ glob, array<float>^ offset, array<float>^ angles, array<float>^% loc)
{
	loc[x] = angles[(int)cosEnum::Xx] * (glob[x] - offset[x]) + angles[(int)cosEnum::Xy] * (glob[y] - offset[y]) + angles[(int)cosEnum::Xz] * (glob[z] - offset[z]);
	loc[y] = angles[(int)cosEnum::Yx] * (glob[x] - offset[x]) + angles[(int)cosEnum::Yy] * (glob[y] - offset[y]) + angles[(int)cosEnum::Yz] * (glob[z] - offset[z]);
	loc[z] = angles[(int)cosEnum::Zx] * (glob[x] - offset[x]) + angles[(int)cosEnum::Zy] * (glob[y] - offset[y]) + angles[(int)cosEnum::Zz] * (glob[z] - offset[z]);
}