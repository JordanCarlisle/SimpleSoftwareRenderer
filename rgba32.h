#pragma once


struct rgba32
{
	unsigned char a;
	unsigned char b;
	unsigned char g;
	unsigned char r;

	rgba32() : r(0x00), g(0x00), b(0x00), a(0x00)
	{}

	rgba32(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : r(red), g(green), b(blue), a(alpha)
	{}
};