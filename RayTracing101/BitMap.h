#pragma once

#include <stdio.h>
#include <stdlib.h>
#include<cmath>

struct RGBType {
	float R;
	float B;
	float G;
};


class BitMap
{
public:
	BitMap();
	~BitMap();
	static void generateBitmapWithCharArray(unsigned char* image, const char* fileName, int height, int width, int bytesPerPixel, int dpi); // generates bitmap and saves it to a file
	static void generateBitmapWithRGB(RGBType* data, const char* fileName, int height, int width, int bytesPerPixel, int dpi); // generates bitmap and saves it to a file

	
private:
	static unsigned char* createBitMapFileHeader(int height, int width, int bytesPerPixel, int paddingSize); // generates the header info for the bitmap file
	static unsigned char* createBitMapInfoHeader(int height, int width, int bytesPerPixel, int dpi); // generates the  file info for the bitmap file
	static const int bitmapFileHeaderSize = 14; // the size of the File Header
	static const int bitmapInfoHeaderSize = 40; // the size of the Info Header
};



