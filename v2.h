#pragma once

struct v2
{
	float x;
	float y;

	//Constructors
	v2();
	v2(const float &x_, const float &y_);

	void set(const float &x_, const float &y_);
	float length();
	v2& normalize();
	v2 normalized();
	float dot(const v2 &v);
	

	//Operators
	v2 operator=(const float &operand) const;
	v2 operator+(const float &operand) const;
	v2 operator+(const v2 &operand) const;
	v2 operator-(const float &operand) const;
	v2 operator-(const v2 &operand) const;
	v2 operator*(const float &operand) const;
	v2 operator*(const v2 &operand) const;
	v2 operator/(const float &operand) const;
	v2 operator/(const v2 &operand) const;
	v2& operator+=(const float &operand);
	v2& operator+=(const v2 &operand);
	v2& operator-=(const float &operand);
	v2& operator-=(const v2 &operand);
	v2& operator*=(const float &operand);
	v2& operator*=(const v2 &operand);
	v2& operator/=(const float &operand);
	v2& operator/=(const v2 &operand);
	bool operator==(v2 &operand) const;
};

namespace maths
{
	float length(const v2& v);
	void normalize(v2& v);
	float dot(const v2 &v1, const v2 &v2);
	float distance(const v2& v1, const v2& v2);
	float grad(const v2& v1, const v2& v2);
	float invgrad(const v2& v1, const v2& v2);
}

#include "v2.inl"