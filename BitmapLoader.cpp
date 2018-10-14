#include "BitmapLoader.h"
#include "Windows.h"
#include <fstream>
#include <iostream>

BitmapLoader::BitmapLoader()
{
}


BitmapLoader::~BitmapLoader()
{
}

void BitmapLoader::load(const char* filename, texture* tex)
{
	std::ifstream file;
	file.open(filename, std::ios::binary);

	if (file.is_open())
	{

		unsigned char* headerBuffers[2] = { nullptr, nullptr };

		unsigned char* pixels = nullptr;

		BITMAPFILEHEADER* header = nullptr;
		BITMAPINFOHEADER* info = nullptr;

		headerBuffers[0] = new unsigned char[sizeof(BITMAPFILEHEADER)];
		headerBuffers[1] = new unsigned char[sizeof(BITMAPINFOHEADER)];

		file.read((char*)headerBuffers[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)headerBuffers[1], sizeof(BITMAPINFOHEADER));

		header = (BITMAPFILEHEADER*)headerBuffers[0];
		info = (BITMAPINFOHEADER*)headerBuffers[1];

		std::cout << info->biWidth << " x " << info->biHeight << std::endl;

		if (header->bfType == 0x4D42)
		{
			pixels = new unsigned char[info->biSizeImage];

			file.seekg(header->bfOffBits);
			file.read((char*)pixels, info->biSizeImage);

			int n = info->biWidth * info->biHeight;
			rgba32* texturePixels = new rgba32[n];
			
			for (unsigned long i = 0; i < info->biHeight; i++)
			{
				unsigned long k = 0;
				for (unsigned long j = 0; j < info->biWidth*3; j +=3 )
				{
					unsigned long yoff = i * info->biWidth;
					unsigned long ioff = (info->biWidth * info->biHeight) - ((i+1) * info->biWidth);
					texturePixels[yoff + k] = rgba32((char)pixels[ioff *3 + j + 2], (char)pixels[ioff *3 +j + 1], (char)pixels[ioff *3 + j], (char)255);
					k++;
				}
			}

			tex->pixels = texturePixels;
			tex->height = info->biHeight;
			tex->width = info->biWidth;
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