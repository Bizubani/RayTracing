#pragma once

#include <stdio.h>
#include <stdlib.h>

class BitMap
{
public:
	BitMap(const char* fileName);
	BitMap(int height, int width, int bytesPerPixel, const char* fileName);
	~BitMap();
	void generateBitmap(unsigned char* image); // generates bitmap and saves it to a file
	unsigned char* createBitMapFileHeader(); // generates the header info for the bitmap file
	unsigned char* createBitMapInfoHeader(); // generates the  file info for the bitmap file
	
private:
	int bitmapFileHeaderSize; // the size of the File Header
	int bitmapInfoHeaderSize; // the size of the Info Header
	int bytesPerPixel; // defaults to 3 unless otherwise specified
	int height; // image height as specified by user
	int width; // image width as specified by user
	int padding; // creates a padding value between  0  - 3
	const char* fileName; // the file name used to save the file
	unsigned char paddingData[3] = { 0, 0, 0 };
};




