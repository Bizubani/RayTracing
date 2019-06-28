#include "BitMap.h"

BitMap::BitMap(const char* fileName)
{
	bitmapFileHeaderSize = 14;
	bitmapInfoHeaderSize = 40;
	height = 720;
	width = 1268;
	bytesPerPixel = 3;
	this->fileName = fileName;
	padding = (4 - (width * bytesPerPixel) % 4) % 4;
}

BitMap::BitMap(int height, int width, int bytesPerPixel, const char* fileName)
{
	this->height = height;
	this->width = width;
	this->bytesPerPixel = bytesPerPixel;
	bitmapFileHeaderSize = 14;
	bitmapInfoHeaderSize = 40;
	this->fileName = fileName;
	padding = (4 - (width * bytesPerPixel) % 4) % 4;
}

BitMap::~BitMap()
{

}

void BitMap::generateBitmap(unsigned char* image)
{
	FILE* imageFile;
	errno_t returnValue = fopen_s(&imageFile, fileName, "wb");
	short charSize = sizeof(unsigned char);
	if(returnValue == 0)
	{ 
		fwrite(createBitMapFileHeader(), charSize, bitmapFileHeaderSize, imageFile);
		fwrite(createBitMapInfoHeader(), charSize, bitmapInfoHeaderSize, imageFile);
		for (int i = 0; i < height; i++)
		{
			fwrite(image + (i * width * bytesPerPixel), bytesPerPixel, width, imageFile);
			fwrite(paddingData, charSize, padding, imageFile);
		}
		fclose(imageFile);
	}
	else {
		printf("Unable to access file %s", fileName);
	}

	
}

unsigned char* BitMap::createBitMapFileHeader()
{
	int totalFileSize = bitmapFileHeaderSize + bitmapInfoHeaderSize + (bytesPerPixel * width + padding) * height;
	static unsigned char fileHeader[] =
	{
		0, 0,	// signature
		0,0,0,0,// image file size in bytes
		0,0,0,0,// reserved
		0,0,0,0 //start of pixel array
	};

	fileHeader[0] = (unsigned char) ('B');
	fileHeader[1] = (unsigned char) ('M');
	fileHeader[2] = (unsigned char)(totalFileSize    );
	fileHeader[3] = (unsigned char)(totalFileSize>>8 );
	fileHeader[4] = (unsigned char)(totalFileSize>>16);
	fileHeader[5] = (unsigned char)(totalFileSize>>24);
	fileHeader[10] = (unsigned char)(bitmapFileHeaderSize + bitmapInfoHeaderSize);

	return  fileHeader;
}


unsigned char* BitMap::createBitMapInfoHeader()
{
	static unsigned char infoHeader[] =
	{
		0,0,0,0, //header size
		0,0,0,0, //image width
		0,0,0,0, //image height
		0,0,     //number of color planes
		0,0,     //bits per pixel
		0,0,0,0, //compression
		0,0,0,0, //image size
		0,0,0,0, // horizontal resolution
		0,0,0,0, //vertical resolution
		0,0,0,0, // colors in color table
		0,0,0,0 //important color count
	};

	infoHeader[0] = (unsigned char)(bitmapInfoHeaderSize);
	infoHeader[4] = (unsigned char)(width     );
	infoHeader[5] = (unsigned char)(width>>8  );
	infoHeader[6] = (unsigned char)(width >>16);
	infoHeader[7] = (unsigned char)(width >>24);
	infoHeader[8] = (unsigned char)(height    );
	infoHeader[9] = (unsigned char)(height>>8 );
	infoHeader[10] = (unsigned char)(height>>16);
	infoHeader[11] = (unsigned char)(height>>24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(bytesPerPixel * 8);

	return infoHeader;
}
