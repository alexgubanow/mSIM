#include "stdafx.h"
#include "cosMatrix.h"
#include "axesEnum.h"
#include "cosEnum.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

inline float calcLib::cosMatrix::_cos(float p1, float p2, float l) { return (p2 - p1) / l; }
/*
	angle[(int)cosEnum::Xx] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Xy] = _cos(p1[y], p2[y], L); angle[(int)cosEnum::Xz] = _cos(p1[z], p2[x], L);
	angle[(int)cosEnum::Yx] = _cos(p2[y], p1[y], L); angle[(int)cosEnum::Yy] = _cos(p1[x], p2[x], L); angle[(int)cosEnum::Yz] = _cos(p1[z], p2[y], L);
	angle[(int)cosEnum::Zx] = _cos(p1[x], p2[z], L); angle[(int)cosEnum::Zy] = _cos(p1[y], p2[z], L); angle[(int)cosEnum::Zz] = _cos(p1[z], p2[z], L);
	*/

void X_Mat_Handler(array<array<float>^>^% X_Mat, float cosA, float sinA)
{
	X_Mat[x][x] = 1.0f;
	X_Mat[x][y] = 0.0f;
	X_Mat[x][z] = 0.0f;

	X_Mat[y][x] = 0.0f;
	X_Mat[y][y] = cosA;
	X_Mat[y][z] = sinA;

	X_Mat[z][x] = 0.0f;
	X_Mat[z][y] = -sinA;
	X_Mat[z][z] = cosA;
}
void Y_Mat_Handler(array<array<float>^>^% Y_Mat, float cosB, float sinB)
{
	Y_Mat[x][x] = cosB;
	Y_Mat[x][y] = 0.0f;
	Y_Mat[x][z] = -sinB;

	Y_Mat[y][x] = 0.0f;
	Y_Mat[y][y] = 1.0f;
	Y_Mat[y][z] = 0.0f;

	Y_Mat[z][x] = sinB;
	Y_Mat[z][y] = 0.0f;
	Y_Mat[z][z] = cosB;
}
void Z_Mat_Handler(array<array<float>^>^% Z_Mat, float cosG, float sinG)
{
	Z_Mat[x][x] = cosG;
	Z_Mat[x][y] = sinG;
	Z_Mat[x][z] = 0.0f;

	Z_Mat[y][x] = -sinG;
	Z_Mat[y][y] = cosG;
	Z_Mat[y][z] = 0.0f;

	Z_Mat[z][x] = 0.0f;
	Z_Mat[z][y] = 0.0f;
	Z_Mat[z][z] = 1.0f;
}

void mult_matrix(array<array<float>^>^ Fst_Mat, array<array<float>^>^ Sec_Mat, array<array<float>^>^% Result_Mat)
{
	float temp = 0.0f;
	int a, b, c;

	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 3; b++)
		{
			for (c = 0; c < 3; c++)
			{
				temp += Fst_Mat[b][c] * Sec_Mat[c][a];
			}
			Result_Mat[b][a] = temp;
			temp = 0.0f;
		}
	}
}

void Concatenate_Matrices(array<array<float>^>^ First_Mat, array<array<float>^>^ Second_Mat, array<array<float>^>^ Third_Mat, array<array<float>^>^%  Fin_Mat)
{
	array<array<float>^>^ Concat_Mat = gcnew array<array<float>^>(3);
	for (size_t i = 0; i < 3; i++)
	{
		Concat_Mat[i] = gcnew array<float>(3);
	}

	mult_matrix(First_Mat, Second_Mat, Concat_Mat);
	mult_matrix(Concat_Mat, Third_Mat, Fin_Mat);
}

void calcLib::cosMatrix::getAngles(array<float>^ p1, array<float>^ p2, float L, array<array<float>^>^% Final_Matrix)
{
	array<array<float>^>^ Ax = gcnew array<array<float>^>(3);
	for (size_t i = 0; i < 3; i++)
	{
		Ax[i] = gcnew array<float>(3);
	}
	array<array<float>^>^ Ay = gcnew array<array<float>^>(3);
	for (size_t i = 0; i < 3; i++)
	{
		Ay[i] = gcnew array<float>(3);
	}
	array<array<float>^>^ Az = gcnew array<array<float>^>(3);
	for (size_t i = 0; i < 3; i++)
	{
		Az[i] = gcnew array<float>(3);
	}
	float cosA = _cos(p1[x], p2[x], L);
	float sinA = _cos(p1[y], p2[y], L);
	X_Mat_Handler(Ax,cosA,sinA);

	float cosB = _cos(p1[y], p2[y], L);
	float sinB = _cos(p1[z], p2[z], L);
	Y_Mat_Handler(Ay, cosB, sinB);

	float cosG = _cos(p1[z], p2[z], L);
	float sinG = _cos(p1[x], p2[x], L);
	Z_Mat_Handler(Az, cosG, sinG);
	
	Concatenate_Matrices(Ax, Ay, Az, Final_Matrix);

	/*angle[(int)cosEnum::Xx] = cosA * cosB;
	angle[(int)cosEnum::Xy] = cosA * sinB * sinG - cosG * sinA;
	angle[(int)cosEnum::Xz] = sinA * sinG + cosA * cosG*sinB;

	angle[(int)cosEnum::Yx] = cosB * sinA;
	angle[(int)cosEnum::Yy] = sinA * sinB * sinG + cosA * cosG;
	angle[(int)cosEnum::Yz] = cosG * sinA*sinB - cosA * sinG;

	angle[(int)cosEnum::Zx] = 0 - sinB;
	angle[(int)cosEnum::Zy] = cosB * sinG;
	angle[(int)cosEnum::Zz] = cosB * cosG;*/

	/*angle[x][x] = cosA * cosB;
	angle[x][x] = cosB * sinA;
	angle[x][x] = 0 - sinB;

	angle[x][x] = cosA * sinB * sinG - cosG * sinA;
	angle[x][x] = sinA * sinB * sinG + cosA * cosG;
	angle[x][x] = cosB * sinG;

	angle[x][x] = sinA * sinG + cosA * cosG*sinB;
	angle[x][x] = cosG * sinA*sinB - cosA * sinG;
	angle[x][x] = cosB * cosG;*/
}