#pragma once
#include "v4.h"

struct mat4
{
	float val[4][4];

	mat4();

	mat4 scalar(float s);
	mat4 scalar(const mat4& s);
	void identity();

	//operators
	float* operator [] (unsigned int i);
	const float* operator [] (unsigned int i) const;
	mat4 operator+(const float operand) const;
	mat4 operator+(const mat4 &operand) const;
	mat4 operator-(const float operand) const;
	mat4 operator-(const mat4 &operand) const;
	mat4 operator*(const mat4 &operand) const;
	v4 operator*(const v4 &operand) const;
	mat4 operator/(const mat4 &operand) const;
	mat4& operator+=(const mat4 &operand);
	mat4& operator-=(const mat4 &operand);
	mat4& operator*=(const mat4 &operand);
	mat4& operator/=(const mat4 &operand);
	bool operator==(mat4 &operand) const;

};

namespace maths
{
	mat4 scale(const mat4 &m, const v3& factor);
	mat4 rotate(const mat4 &m, const v3& angle);
	mat4 translate(const mat4 &m, const v3& v);
}

#include "mat4.inl"