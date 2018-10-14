#pragma once
#include "v3.h"

struct v4
{
	float x;
	float y;
	float z;
	float w;

	//Constructors
	v4();
	v4(const float &x_, const float &y_, const float &z_, const float &w_);
	v4(const v3& v, const float& w_);

	void set(const float &x_, const float &y_, const float &z_, const float &w_);

	//Operators
	v4 operator=(const float &operand) const;
	v4 operator+(const float &operand) const;
	v4 operator+(const v4 &operand) const;
	v4 operator-(const float &operand) const;
	v4 operator-(const v4 &operand) const;
	v4 operator*(const float &operand) const;
	v4 operator*(const v4 &operand) const;
	v4 operator/(const float &operand) const;
	v4 operator/(const v4 &operand) const;
	v4 &operator+=(const float &operand);
	v4 &operator+=(const v4 &operand);
	v4 &operator-=(const float &operand);
	v4 &operator-=(const v4 &operand);
	v4 &operator*=(const float &operand);
	v4 &operator*=(const v4 &operand);
	v4 &operator/=(const float &operand);
	v4 &operator/=(const v4 &operand);
	bool operator==(v4 &operand) const;
};

#include "v4.inl"
