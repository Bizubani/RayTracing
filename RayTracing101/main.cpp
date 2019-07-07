#include <iostream>
#include "BitMap.h"
#include "camera.h"
#include "Ray.h"
#include "Light.h"

#define BYTESPERPIXEL 3

void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width);

int main(int argc, char* argv[])
{
	int height = 1280;
	int width = 720;

	Vector x(1.0, 0.0, 0.0);
	Vector y(0.0, 1.0, 0.0);
	Vector z(0.0, 0.0, 1.0);

	Point lookTowards; // create a point we that looks towards the origin
	Vector currentCameraPosition(5.0, 15.0, 10.0); // the current camera position
	
	Vector differenceBetween(currentCameraPosition.x - lookTowards.x, currentCameraPosition.y - lookTowards.y, currentCameraPosition.z - lookTowards.z); // figure out where the camera is relative to the point we are looking at
	Vector currentCameraDirection = -differenceBetween.normalized(); // fix the camera to look at the point by reversing it's direction
	Vector currentCamRight = y.crossProduct(currentCameraDirection).normalized; // calculate it's right position and normalize it
	Vector currentCamDown = currentCamRight.crossProduct(currentCameraDirection); // calculate it's down position
	Camera sceneCamera(currentCameraPosition, currentCameraDirection, currentCamRight, currentCamDown); // a variable to hold the information pertaining to the scene camera

	Color whiteLight(1.0, 1.0, 1.0, 0.0);
	Color prettyBlue(0.5, 1.0, 0.5, 0.3);
	Color gray(0.5, 0.5, 0.5, 0.0);
	Color black(0.0, 0.0, 0.0, 0.0);

	Vector lightScenePosition(-7, 10, -10);

	Light sceneLight(lightScenePosition, whiteLight);


	std::cout << currentCameraDirection.x <<" " << currentCameraDirection.y << " " <<currentCameraDirection.z << std::endl;
	
	//generateColorGradient(255, 0, 0, height, width);

	return 0;
}

void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width)
{
	RGBType *mytype = new RGBType[(float)height*(float)width];
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