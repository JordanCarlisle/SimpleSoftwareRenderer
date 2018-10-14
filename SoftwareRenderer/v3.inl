
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

inline v3 cross(const v3& vec1, const v3& vec2)
{
	v3 cr(
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	);

	return cr;
}