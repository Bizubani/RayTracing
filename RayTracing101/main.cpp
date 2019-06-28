#include <iostream>
#include "BitMap.h"

#define	HEIGHT 380
#define WIDTH 860
#define BYTESPERPIXEL 3


int main(int argc, char* argv[])
{
	unsigned char image[HEIGHT][WIDTH][BYTESPERPIXEL] = { 0 };
	const char* imageFileName = "testBitmap.bmp";

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			image[i][j][2] = (unsigned char)((float)i / HEIGHT * 255);
			image[i][j][1] = (unsigned char)((float)i / WIDTH * 255) ;
			image[i][j][0] = (unsigned char)((float)(i+j) /( HEIGHT + WIDTH)* 255);
		}
	}
	BitMap myBitmap = BitMap(HEIGHT, WIDTH, BYTESPERPIXEL, imageFileName);

	myBitmap.generateBitmap((unsigned char*)image);

	return 0;
}