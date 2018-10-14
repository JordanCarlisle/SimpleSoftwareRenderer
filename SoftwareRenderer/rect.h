#pragma once
#include "v2.h"

struct rect
{
	float x;
	float y;
	float width;
	float height;

	rect();
	rect(const float& x_, const float& y_, const float& width_, const float& height_);
	rect(const v2& pos, const v2& size);

	void set(const float& width_, const float& height_);
	void set(const float& x_, const float& y_, const float& width_, const float& height_);
	void set(const v2& _pos, const v2& _size);

	bool operator==(rect &operand) const;
};

#include "rect.inl"