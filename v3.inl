#include <cmath>

inline v3::v3() : x(.0f), y(.0f)
{}

inline v3::v3(const float &x_, const float &y_, const float &z_)
{
	set(x_, y_, z_);
}

inline v3 v3::operator=(const float& operand) const
{
	return v3(operand, operand, operand);
}

//Adding float
inline v3 v3::operator+(const float &operand) const
{
	return v3(x + operand, y + operand, z + operand);
}

//Adding another v3
inline v3 v3::operator+(const v3 &operand) const
{
	return v3(x + operand.x, y + operand.y, z + operand.z);
}

//Subtract float
inline v3 v3::operator-(const float &operand) const
{
	return v3(x - operand, y - operand, z - operand);
}

//Subtracting v3
inline v3 v3::operator-(const v3 &operand) const
{
	return v3(x - operand.x, y - operand.y, z - operand.z);
}

//Multiplying by float
inline v3 v3::operator*(const float &operand) const
{
	return v3(x * operand, y * operand, z * operand);
}

//Multiplying by v3
inline v3 v3::operator*(const v3 &operand) const
{
	return v3(x * operand.x, y * operand.y, z * operand.z);
}

//Diviging by float
inline v3 v3::operator/(const float &operand) const
{
	return v3(x / operand, y / operand, z / operand);
}

//Dividing by v3
inline v3 v3::operator/(const v3 &operand) const
{
	return v3(x / operand.x, y / operand.y, z / operand.z);
}

//Compound Add float
inline v3 &v3::operator+=(const float &operand)
{
	x += operand;
	y += operand;
	z += operand;
	return *this;
}

//Compound Add v3
inline v3 &v3::operator+=(const v3 &operand)
{
	x += operand.x;
	y += operand.y;
	z += operand.z;
	return *this;
}

//Compound Subtract float
inline v3 &v3::operator-=(const float &operand)
{
	x -= operand;
	y -= operand;
	z -= operand;
	return *this;
}


//Compound Subtract v3
inline v3 &v3::operator-=(const v3 &operand)
{
	x -= operand.x;
	y -= operand.y;
	z -= operand.z;
	return *this;
}

//Compound Multiply by float
inline v3 &v3::operator*=(const float &operand)
{
	x *= operand;
	y *= operand;
	z *= operand;
	return *this;
}

//Compound Multiply by v3
inline v3 &v3::operator*=(const v3 &operand)
{
	x *= operand.x;
	y *= operand.y;
	z *= operand.z;
	return *this;
}

//Compound Divide by float
inline v3 &v3::operator/=(const float &operand)
{
	x /= operand;
	y /= operand;
	z /= operand;
	return *this;
}

//Compound Divide by v3
inline v3 &v3::operator/=(const v3 &operand)
{
	x /= operand.x;
	y /= operand.y;
	z /= operand.z;
	return *this;
}

//Comparison v3 with v3
inline bool v3::operator==(v3 &operand) const
{
	return (x == operand.x && y == operand.y && z == operand.z) ? true : false;
}

//Set x and y
inline void v3::set(const float &x_, const float &y_, const float &z_)
{
	x = x_;
	y = y_;
	z = z_;
}

inline float v3::length()
{
	float sqr = x*x + y*y + z*z;
	return sqrt(sqr);
}

inline v3& v3::normalize()
{
	float len = length();
	if (len > 0)
	{
		float inv = 1 / len;
		*this *= inv;
	}
	return *this;
}

inline v3 v3::normalized()
{
	v3 norm(x, y, z);
	norm.normalize();
	return norm;
}

inline float v3::dot(const v3& v)
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

inline v3 v3::cross(const v3& v)
{
	v3 cr(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
		);

	return cr;
}


namespace maths
{
	inline float length(v3& v)
	{
		float sqr = v.x*v.x + v.y*v.y + v.z*v.z;
		return sqrt(sqr);
	}

	inline void normalize(v3& v)
	{
		float len = length(v);
		if (len > 0)
		{
			float inv = 1 / len;
			v *= inv;
		}
	}

	inline float dot(const v3& v1, const v3& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	inline v3 cross(const v3& v1, const v3& v2)
	{
		v3 cr(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
			);

		return cr;
	}

}