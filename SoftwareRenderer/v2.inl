
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
	x /= operand;
	y /= operand;
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

//cross product
/*inline v2& v2::cross()
{

}*/

