#pragma once
#include "texture.h"

#pragma pack(push, 1)
struct BitmapFileHeader
{
	unsigned short type;
	unsigned long size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned long offBits;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitmapInfoHeader
{
	unsigned long size;
	long width;
	long height;
	unsigned short planes;
	unsigned short bits;
	unsigned long compression;
	unsigned long sizeImage;
	long xPixelsPerMetre;
	long yPixelsPerMetre;
	unsigned long clrUsed;
	unsigned long clrImportant;
};
#pragma pack(pop)

class BitmapLoader
{
public:
	BitmapLoader();
	~BitmapLoader();

	void load(const char* filename, texture* tex);
};

