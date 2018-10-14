#pragma once

struct v3
{
	float x;
	float y;
	float z;

	//Constructors
	v3();
	v3(const float &x_, const float &y_, const float &z_);

	void set(const float &x_, const float &y_, const float &z_);

	//Operators
	v3 operator=(const float &operand) const;
	v3 operator+(const float &operand) const;
	v3 operator+(const v3& operand) const;
	v3 operator-(const float &operand) const;
	v3 operator-(const v3& operand) const;
	v3 operator*(const float &operand) const;
	v3 operator*(const v3& operand) const;
	v3 operator/(const float &operand) const;
	v3 operator/(const v3& operand) const;
	v3& operator+=(const float &operand);
	v3& operator+=(const v3& operand);
	v3& operator-=(const float &operand);
	v3& operator-=(const v3& operand);
	v3& operator*=(const float &operand);
	v3& operator*=(const v3& operand);
	v3& operator/=(const float &operand);
	v3& operator/=(const v3& operand);
	bool operator==(v3& operand) const;
};

v3 cross(const v3& vec1, const v3& vec2);

#include "v3.inl"
