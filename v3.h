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
	float length();
	v3& normalize();
	v3 normalized();
	float dot(const v3 &v);
	v3 cross(const v3 &v);

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

namespace maths
{ 
	float length(v3& v);
	void normalize(v3& v);
	float dot(const v3& v1, const v3& v2);
	v3 cross(const v3& v1, const v3& v2);
}


#include "v3.inl"
