#pragma once
#include "axesEnum.h"
#include "DerivEnum.h"
#include "ForcePlaceEnum.h"

namespace calcLib
{
	public ref class integr
	{
		static const float c0 = 0.1875f;
		static const float c1 = 0.697222222f;
		static const float c2 = 1.0f;
		static const float c3 = 0.611111111f;
		static float FtoA(float massa, float force, ForcePlaceEnum fp, float l);;
		void get_coordsvab_from_dipl(array<float>^ xp,
			array<float>^ lastcoords, array<float>^ lastx, array<float>^ lastv, array<float>^ lasta,
			float dt, array<float>^ %coords, array<float>^  %vp, array<float>^ %ap);;
		//void get_xvab_from_coords(size_t demensia, array<array<array<float>^>^>^ prevState, Derivatives^ %currState);;
	public:

		static void euler(array<array<array<float>^>^>^ %deriv, int prevState, int currState, float massa, float l, float dt);

		static void verlet(array<float>^  lastx, array<float>^  lastv, array<float>^ lasta, array<float>^  F,
			float deltat, float massa, float l,
			array<float>^ %xp, array<float>^  %vp, array<float>^  %ap);

		static void gearp(array<float>^ lastx, array<float>^lastv, array<float>^ lasta, array<float>^ lastb, array<float>^ F,
			float deltat, float massa, float l,
			array<float>^ %xp, array<float>^ %vp, array<float>^ %ap, array<float>^ %bp);

		static void gearc(array<float>^ xp, array<float>^ vp, array<float>^ ap, array<float>^ bp, array<float>^ F,
			double deltat, float massa, float l,
			array<float>^ %xc, array<float>^ %vc, array<float>^ %ac, array<float>^ %bc);
		enum class Schems
		{
			euler = 0,
			verlet = 1,
			gear = 2
		};
	};
}