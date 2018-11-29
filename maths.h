#pragma once
#include "v2.h"
#include "v3.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265358979323

namespace maths
{
	bool pointInTriangle(const v2& p, const v2& a, const v2& b, const v2& c);
	v3 barycentricCoords(const v2& p, const v2& a, const v2& b, const v2& c);
	v3 barycentricCoords(const v3& p, const v3& a, const v3& b, const v3& c);
	float degToRad(float degrees);
	float radToDeg(float radians);
}

#include "maths.inl"