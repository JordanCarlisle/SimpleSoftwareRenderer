#pragma once
#include "rgba32.h"

struct texture
{
	rgba32* pixels;
	unsigned int width;
	unsigned int height;

	texture();
	texture(rgba32* buffer, unsigned int width, unsigned int height);
	~texture();
};

#include "texture.inl"