#pragma once


struct rgba16
{
	char a;
	char b;
	char g;
	char r;

	rgba16() : r(0x00), g(0x00), b(0x00), a(0x00)
	{}

	rgba16(char red, char green, char blue, char alpha) : r(red), g(green), b(blue), a(alpha)
	{}
};