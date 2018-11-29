#include "BitmapLoader.h"
#include "Windows.h"
#include <fstream>
#include <iostream>

BitmapLoader::BitmapLoader() {}
BitmapLoader::~BitmapLoader() {}

void BitmapLoader::load(const char* filename, texture* tex)
{
	std::ifstream file;
	file.open(filename, std::ios::binary);

	if (file.is_open())
	{
		unsigned char* headerBuffers[2] = { nullptr, nullptr };
		unsigned char* pixels = nullptr;

		headerBuffers[0] = new unsigned char[sizeof(BitmapFileHeader)];
		headerBuffers[1] = new unsigned char[sizeof(BitmapInfoHeader)];

		file.read((char*)headerBuffers[0], sizeof(BitmapFileHeader));
		file.read((char*)headerBuffers[1], sizeof(BitmapInfoHeader));

		BitmapFileHeader* header = (BitmapFileHeader*)headerBuffers[0];
		BitmapInfoHeader* info = (BitmapInfoHeader*)headerBuffers[1];

		std::cout << "Loading bitmap: " << info->width << " x " << info->height << std::endl;

		if (header->type == 0x4D42)
		{
			pixels = new unsigned char[info->sizeImage];

			file.seekg(header->offBits);
			file.read((char*)pixels, info->sizeImage);

			int n = info->width * info->height;
			rgba32* texturePixels = new rgba32[n];
			
			for (unsigned long i = 0; i < info->height; i++)
			{
				unsigned long k = 0;
				for (unsigned long j = 0; j < info->width*3; j +=3 )
				{
					unsigned long yoff = i * info->width;
					unsigned long ioff = (info->width * info->height) - ((i+1) * info->width);
					texturePixels[yoff + k] = rgba32((char)pixels[ioff *3 + j + 2], (char)pixels[ioff *3 +j + 1], (char)pixels[ioff *3 + j], (char)255);
					k++;
				}
			}

			tex->pixels = texturePixels;
			tex->height = info->height;
			tex->width = info->width;
		}
		else
		{
			std::cout << filename << " not a bitmap\n";
		}

		if (headerBuffers[0] != nullptr)
			delete[] headerBuffers[0];

		if (headerBuffers[1] != nullptr)
			delete[] headerBuffers[1];

		if (pixels != nullptr)
			delete[] pixels;

		file.close();

	}
	else
	{
		std::cout << "can't open file " << filename << std::endl;
	}
}