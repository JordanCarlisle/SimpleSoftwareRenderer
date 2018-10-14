#pragma once


struct rgb24
{
	unsigned char b;
	unsigned char g;
	unsigned char r;

	rgb24() : r(0x00), g(0x00), b(0x00)
	{}

	rgb24(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : r(red), g(green), b(blue)
	{}
};