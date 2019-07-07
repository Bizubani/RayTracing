#include "BitMap.h"

BitMap::BitMap()
{
}



BitMap::~BitMap()
{

}

void BitMap::generateBitmapWithCharArray(unsigned char* image, const char* fileName, int height, int width, int bytesPerPixel, int dpi)
{
	unsigned char paddingData[3] = { 0, 0, 0 };
	int paddingSize = (4 - (width * bytesPerPixel) % 4) % 4;
	FILE* imageFile;
	errno_t returnValue = fopen_s(&imageFile, fileName, "wb");
	short charSize = sizeof(unsigned char);
	if(returnValue == 0)
	{ 
		fwrite(createBitMapFileHeader(height, width, bytesPerPixel, paddingSize), charSize, bitmapFileHeaderSize, imageFile);
		fwrite(createBitMapInfoHeader(height, width, bytesPerPixel, dpi), charSize, bitmapInfoHeaderSize, imageFile);
		for (int i = 0; i < height; i++)
		{
			fwrite(image + (i * width * bytesPerPixel), bytesPerPixel, width, imageFile);
			fwrite(paddingData, charSize, paddingSize, imageFile);
		}
		fclose(imageFile);
	}
	else {
		printf("Unable to access file %s", fileName);
	}

	
}

void BitMap::generateBitmapWithRGB(RGBType* data, const char* fileName, int height, int width, int bytesPerPixel, int dpi)
{
	unsigned char paddingData[3] = { 0, 0, 0 };
	int paddingSize = (4 - (width * bytesPerPixel) % 4) % 4;
	FILE* imageFile;
	errno_t returnValue = fopen_s(&imageFile, fileName, "wb");
	short charSize = sizeof(unsigned char);
	if (returnValue == 0)
	{
		fwrite(createBitMapFileHeader(height, width, bytesPerPixel, paddingSize), charSize, bitmapFileHeaderSize, imageFile);
		fwrite(createBitMapInfoHeader(height, width, bytesPerPixel, dpi), charSize, bitmapInfoHeaderSize, imageFile);
		for (int i = 0; i < height * width; i++)
		{
			float red = data[i].R;
			float blue = data[i].B;
			float green = data[i].G;
			unsigned char color[3] = { (unsigned char)(blue), (unsigned char)(green), (unsigned char)(red) };
			fwrite(color, charSize, bytesPerPixel, imageFile);
			if ((height * width) % width == 0)
			{
				fwrite(paddingData, charSize, paddingSize, imageFile);// Todo: May break this function, check, padding firstly after every row is drawn
			}
		}
		fclose(imageFile);
	}
	else {
		printf("Unable to access file %s", fileName);
	}


}


unsigned char* BitMap::createBitMapFileHeader(int height, int width, int bytesPerPixel, int paddingSize)
{
	int totalFileSize = bitmapFileHeaderSize + bitmapInfoHeaderSize + (bytesPerPixel * width + paddingSize) * height;
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


unsigned char* BitMap::createBitMapInfoHeader(int height, int width, int bytesPerPixel, int dpi)
{
	int ppm = dpi * 40; //Todo: mess around with this value to see the result
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
	infoHeader[25] = (unsigned char)(ppm    );
	infoHeader[26] = (unsigned char)(ppm>>8 );
	infoHeader[27] = (unsigned char)(ppm>>16);
	infoHeader[28] = (unsigned char)(ppm>>24);
	infoHeader[29] = (unsigned char)(ppm);
	infoHeader[30] = (unsigned char)(ppm >> 8);
	infoHeader[31] = (unsigned char)(ppm >> 16);
	infoHeader[32] = (unsigned char)(ppm >> 24);

	return infoHeader;
}
