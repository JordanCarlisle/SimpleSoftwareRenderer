#include <cstring>
#include <iostream>

inline texture::texture()
	: pixels(nullptr)
{}

inline texture::texture(rgba32* buffer, unsigned int width, unsigned int height)
{
	pixels = buffer;
}

inline texture::~texture()
{
	if(pixels != nullptr)
		delete[] pixels;
}