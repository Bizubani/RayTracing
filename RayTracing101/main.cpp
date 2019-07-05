#include <iostream>
#include "BitMap.h"

#define BYTESPERPIXEL 3

void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width);

int main(int argc, char* argv[])
{
	int height = 780;
	int width = 480;
	
	generateColorGradient(255, 0, 0, height, width);

	return 0;
}

void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width)
{
	RGBType *mytype = new RGBType[height*width];
	const char* imageFileName = "testBitmap.bmp";
	const char* imageFileName2 = "testBitmapRGB.bmp";

	for (int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{


			mytype[(i * width) + j].B = (unsigned char)((float)i / height * blueValue);

			mytype[(i * width) + j].G = (unsigned char)((float)i / width * greenValue);

			mytype[(i * width) + j].R = (unsigned char)((float)(i + j) / (height + width) * redValue);
		}
	}
	   	 
	BitMap::generateBitmapWithRGB(mytype, imageFileName2, height, width, BYTESPERPIXEL, 72);
	delete[] mytype;

}