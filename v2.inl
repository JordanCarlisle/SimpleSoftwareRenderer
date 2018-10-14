#include <cmath>


inline v2::v2() : x(.0f), y(.0f)
{}

inline v2::v2(const float &x_, const float &y_)
{
	set(x_, y_);
}

inline v2 v2::operator=(const float& operand) const
{
	return v2(operand, operand);
}

//Adding float
inline v2 v2::operator+(const float &operand) const
{
	return v2(x + operand, y + operand);
}

//Adding another v2
inline v2 v2::operator+(const v2 &operand) const
{
	return v2(x + operand.x, y + operand.y);
}

//Subtract float
inline v2 v2::operator-(const float &operand) const
{
	return v2(x - operand, y - operand);
}

//Subtracting v2
inline v2 v2::operator-(const v2 &operand) const
{
	return v2(x - operand.x, y - operand.y);
}

//Multiplying by float
inline v2 v2::operator*(const float &operand) const
{
	return v2(x * operand, y * operand);
}

//Multiplying by v2
inline v2 v2::operator*(const v2 &operand) const
{
	return v2(x * operand.x, y * operand.y);
}

//Diviging by float
inline v2 v2::operator/(const float &operand) const
{
	return v2(x / operand, y / operand);
}

//Dividing by v2
inline v2 v2::operator/(const v2 &operand) const
{
	return v2(x / operand.x, y / operand.y);
}

//Compound Add float
inline v2& v2::operator+=(const float &operand)
{
	x += operand;
	y += operand;
	return *this;
}

//Compound Add v2
inline v2 &v2::operator+=(const v2 &operand)
{
	x += operand.x;
	y += operand.y;
	return *this;
}

//Compound Subtract float
inline v2 &v2::operator-=(const float &operand)
{
	x -= operand;
	y -= operand;
	return *this;
}


//Compound Subtract v2
inline v2 &v2::operator-=(const v2 &operand)
{
	x -= operand.x;
	y -= operand.y;
	return *this;
}

//Compound Multiply by float
inline v2 &v2::operator*=(const float &operand)
{
	x *= operand;
	y *= operand;
	return *this;
}

//Compound Multiply by v2
inline v2 &v2::operator*=(const v2 &operand)
{
	x *= operand.x;
	y *= operand.y;
	return *this;
}

//Compound Divide by float
inline v2 &v2::operator/=(const float &operand)
{
	float inv = 1 / operand;
	x *= inv;
	y *= inv;
	return *this;
}

//Compound Divide by v2
inline v2 &v2::operator/=(const v2 &operand)
{
	x /= operand.x;
	y /= operand.y;
	return *this;
}

//Comparison v2 with v2
inline bool v2::operator==(v2 &operand) const
{
	return (x == operand.x && y == operand.y) ? true : false;
}

//Set x and y
inline void v2::set(const float &x_, const float &y_)
{
	x = x_;
	y = y_;
}

inline float v2::length()
{
	float sqr = x*x + y*y;
	return sqrt(sqr);
}

inline v2& v2::normalize()
{
	float len = length();
	if (len > 0)
	{
		float inv = 1 / len;
		*this *= inv;
	}
	return *this;
}

inline v2 v2::normalized()
{
	v2 norm(x, y);
	norm.normalize();
	return norm;
}

inline float v2::dot(const v2& v)
{
	return (x * v.x) + (y * v.y);
}

namespace maths
{
	inline float length(const v2& v)
	{
		return sqrtf(v.x*v.x + v.y*v.y);
	}

	inline void normalize(v2& v)
	{
		float len = length(v);
		if (len > 0)
		{
			float inv = 1 / len;
			v *= inv;
		}
	}

	inline float dot(const v2 &v1, const v2 &v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline float distance(const v2& v1, const v2& v2)
	{
		return sqrtf(pow(v2.x - v1.x, 2) + pow(v2.x - v1.x, 2));
	}

	inline float grad(const v2& v1, const v2& v2)
	{
		return (v2.y - v1.y) / (v2.x - v1.x);
	}

	inline float invgrad(const v2& v1, const v2& v2)
	{
		return (v2.x - v1.x) / (v2.y - v1.y);
	}
}
