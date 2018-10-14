#include <cstring>
#include <cmath>
#include "maths.h"

inline mat4::mat4()
{
	std::memset(val, 0, sizeof(float) * 16);
}

inline float* mat4::operator [] (unsigned int i)
{
	return val[i];
}

inline const float* mat4::operator[](unsigned int i) const
{
	return val[i];
}

inline mat4 mat4::operator + (const float operand) const
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] += operand;
	return m;
}

inline mat4 mat4::operator + (const mat4 &operand) const
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] += operand[i][j];
	return m;
}

inline mat4 mat4::operator - (const float operand) const
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] -= operand;
	return m;
}


inline mat4 mat4::operator - (const mat4 &operand) const
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] -= operand[i][j];
	return m;
}



inline mat4 mat4::operator*(const mat4 &operand) const
{
	mat4 m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = val[i][0] * operand[0][j] + val[i][1] * operand[1][j] + val[i][2] * operand[2][j] + val[i][3] * operand[3][j];
		}
	return m;
}

inline v4 mat4::operator*(const v4 &operand) const
{
	v4 v;
	v.x = val[0][0] * operand.x + val[0][1] * operand.y + val[0][2] * operand.z + val[0][3] * operand.w;
	v.y = val[1][0] * operand.x + val[1][1] * operand.y + val[1][2] * operand.z + val[1][3] * operand.w;
	v.z = val[2][0] * operand.x + val[2][1] * operand.y + val[2][2] * operand.z + val[2][3] * operand.w;
	v.w = val[3][0] * operand.x + val[3][1] * operand.y + val[3][2] * operand.z + val[3][3] * operand.w;

	return v;
}

inline mat4 mat4::operator/(const mat4 &operand) const
{
	return *this;
}



inline mat4& mat4::operator+=(const mat4 &operand)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			val[i][j] += operand[i][j];
	return *this;
}



inline mat4& mat4::operator-=(const mat4 &operand)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			val[i][j] -= operand[i][j];
	return *this;
}


inline mat4& mat4::operator*=(const mat4 &operand)
{
	*this = (*this) * operand;
	return *this;
}


inline mat4& mat4::operator/=(const mat4 &operand)
{
	return *this;
}

inline bool mat4::operator==(mat4 &operand) const
{
	if (!std::memcmp(&val, &operand, sizeof(float) * 16))
		return true;
	return false;
}

inline mat4 mat4::scalar(float s)
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] *= s;
	return m;
}

inline mat4 mat4::scalar(const mat4& s)
{
	mat4 m = *this;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] *= s[i][j];
	return m;
}

inline void mat4::identity()
{
	val[0][0] = 1.0f;
	val[1][0] = 0.0f;
	val[2][0] = 0.0f;
	val[3][0] = 0.0f;

	val[0][1] = 0.0f;
	val[1][1] = 1.0f;
	val[2][1] = 0.0f;
	val[3][1] = 0.0f;

	val[0][2] = 0.0f;
	val[1][2] = 0.0f;
	val[2][2] = 1.0f;
	val[3][2] = 0.0f;

	val[0][3] = 0.0f;
	val[1][3] = 0.0f;
	val[2][3] = 0.0f;
	val[3][3] = 1.0f;
}

namespace maths
{
	inline mat4 scale(const mat4 &m, const v3& factor)
	{
		mat4 s;
		s.identity();

		s[0][0] = factor.x;
		s[1][1] = factor.y;
		s[2][2] = factor.z;
		return s * m;
	}

	inline mat4 rotate(const mat4 &m, const v3& angle)
	{
		mat4 x;
		x.identity();

		//x-axis
		x[1][1] = cosf(degToRad(angle.x));
		x[1][2] = -sinf(degToRad(angle.x));
		x[2][1] = sinf(degToRad(angle.x));
		x[2][2] = cosf(degToRad(angle.x));

		//y-axis
		mat4 y;
		y.identity();
		y[0][0] = cos(degToRad(angle.y));
		y[0][2] = sin(degToRad(angle.y));
		y[2][0] = -sin(degToRad(angle.y));
		y[2][2] = cos(degToRad(angle.y));

		//z-axis
		mat4 z;
		z.identity();
		z[0][0] = cosf(degToRad(angle.z));
		z[0][1] = -sinf(degToRad(angle.z));
		z[1][0] = sinf(degToRad(angle.z));
		z[1][1] = cosf(degToRad(angle.z));
		
		return x * y * z * m;
	}

	inline mat4 translate(const mat4 &m, const v3& v)
	{
		mat4 r;
		r.identity();
		r[0][3] = v.x;
		r[1][3] = v.y;
		r[2][3] = v.z;
		return r * m;
	}
}