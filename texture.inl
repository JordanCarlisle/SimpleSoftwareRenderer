#include <cstring>
#include <iostream>

inline texture::texture()
	: pixels(nullptr)
{}

inline texture::texture(rgba32* buffer, unsigned int width, unsigned int height)
{
	pixels = buffer;
//	pixels = new PixelFormat[width * height];
//	std::memcpy(pixels, buffer, sizeof(PixelFormat) * (width * height));
}

inline texture::~texture()
{
	if(pixels != nullptr)
		delete[] pixels;
}