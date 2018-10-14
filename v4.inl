
inline v4::v4() : x(.0f), y(.0f)
{}

inline v4::v4(const float &x_, const float &y_, const float &z_, const float &w_)
{
	set(x_, y_, z_, w_);
}

inline v4::v4(const v3& v, const float& w_)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = w_;
}

inline v4 v4::operator=(const float& operand) const
{
	return v4(operand, operand, operand, operand);
}

//Adding float
inline v4 v4::operator+(const float &operand) const
{
	return v4(x + operand, y + operand, z + operand, w + operand);
}

//Adding another v4
inline v4 v4::operator+(const v4 &operand) const
{
	return v4(x + operand.x, y + operand.y, z + operand.z, w + operand.w);
}

//Subtract float
inline v4 v4::operator-(const float &operand) const
{
	return v4(x - operand, y - operand, z - operand, w - operand);
}

//Subtracting v4
inline v4 v4::operator-(const v4 &operand) const
{
	return v4(x - operand.x, y - operand.y, z - operand.z, w - operand.w);
}

//Multiplying by float
inline v4 v4::operator*(const float &operand) const
{
	return v4(x * operand, y * operand, z * operand, w * operand);
}

//Multiplying by v4
inline v4 v4::operator*(const v4 &operand) const
{
	return v4(x * operand.x, y * operand.y, z * operand.z, w * operand.w);
}

//Diviging by float
inline v4 v4::operator/(const float &operand) const
{
	return v4(x / operand, y / operand, z / operand, w / operand);
}

//Dividing by v4
inline v4 v4::operator/(const v4 &operand) const
{
	return v4(x / operand.x, y / operand.y, z / operand.z, w / operand.w);
}

//Compound Add float
inline v4 &v4::operator+=(const float &operand)
{
	x += operand;
	y += operand;
	z += operand;
	w += operand;
	return *this;
}

//Compound Add v4
inline v4 &v4::operator+=(const v4 &operand)
{
	x += operand.x;
	y += operand.y;
	z += operand.z;
	w += operand.w;
	return *this;
}

//Compound Subtract float
inline v4 &v4::operator-=(const float &operand)
{
	x -= operand;
	y -= operand;
	z -= operand;
	w -= operand;
	return *this;
}


//Compound Subtract v4
inline v4 &v4::operator-=(const v4 &operand)
{
	x -= operand.x;
	y -= operand.y;
	z -= operand.z;
	w -= operand.w;
	return *this;
}

//Compound Multiply by float
inline v4 &v4::operator*=(const float &operand)
{
	x *= operand;
	y *= operand;
	z *= operand;
	w *= operand;
	return *this;
}

//Compound Multiply by v4
inline v4 &v4::operator*=(const v4 &operand)
{
	x *= operand.x;
	y *= operand.y;
	z *= operand.z;
	w *= operand.w;
	return *this;
}

//Compound Divide by float
inline v4 &v4::operator/=(const float &operand)
{
	x /= operand;
	y /= operand;
	z /= operand;
	w /= operand;
	return *this;
}

//Compound Divide by v4
inline v4 &v4::operator/=(const v4 &operand)
{
	x /= operand.x;
	y /= operand.y;
	z /= operand.z;
	w /= operand.w;
	return *this;
}

//Comparison v4 with v4
inline bool v4::operator==(v4 &operand) const
{
	return (x == operand.x && y == operand.y && z == operand.z && w == operand.w) ? true : false;
}

//Set x and y
inline void v4::set(const float &x_, const float &y_, const float &z_, const float &w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}
