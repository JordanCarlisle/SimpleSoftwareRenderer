#pragma once


inline rect::rect() : x(0), y(0), width(0), height(0)
{}

inline rect::rect(const float& x_, const float& y_, const float& width_, const float& height_) : x(x_), y(y_), width(width_), height(height_)
{}

inline rect::rect(const v2& pos, const v2& size) : x(pos.x), y(pos.y), width(size.x), height(size.y)
{}

inline void rect::set(const float& width_, const float& height_)
{
	width = width_;
	height = height_;
}

inline void rect::set(const float& x_, const float& y_, const float& width_, const float& height_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}

inline void rect::set(const v2& _pos, const v2& _size)
{
	x = _pos.x;
	y = _pos.y;
	width = _size.x;
	height = _size.y;
}

inline bool rect::operator==(rect &operand) const
{
	return (x == operand.x && y == operand.y && width == operand.width && height == operand.height) ? true : false;
}
