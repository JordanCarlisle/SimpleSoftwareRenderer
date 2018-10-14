#pragma once

struct v2
{
	float x;
	float y;

	//Constructors
	v2();
	v2(const float &x_, const float &y_);

	void set(const float &x_, const float &y_);
//	void dot(const v2 &v);
//	v2& cross();

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

#include "v2.inl"