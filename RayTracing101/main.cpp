#include <iostream>
#include "BitMap.h"
#include "camera.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"

#define BYTESPERPIXEL 3

void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width);

int main(int argc, char* argv[])
{
	int height = 800;
	int width = 800;
	RGBType* imageData = (RGBType*) calloc(width * height, sizeof(RGBType));
	float aspectRatio = (float) width / height;
	Vector origin(0.0f, 0.5f, 0.0f);
	Vector planePosition(0.0f,-1.0f, 0.0f); 
	Vector x(1.0, 0.0, 0.0);
	Vector y(0.0, 1.0, 0.0);
	Vector z(0.0, 0.0, 1.0);

	Point lookTowards; // create a point we that looks towards the origin
	Vector currentCameraPosition(0.0f, 1.0f, -12.0f); // the current camera position
	
	Camera sceneCamera(lookTowards, currentCameraPosition);

	Color whiteLight(1.0f, 1.0f, 1.0f, 0.0f);
	Color prettyBlue(0.5f, 1.0f, 0.5f, 0.3f);
	Color pureRed(1.0f, 0.0f, 0.0f, 0.0f);
	Color gray(0.5f, 0.5f, 0.5f, 0.0f);
	Color someColor(0.5f, 0.75f, 0.3f, 0.0f);
	Color black(0.0f, 0.0f, 0.0f, 0.0f);

	Vector lightScenePosition( 7.0f, 10.0f, 10.0f);
	Light sceneLight(lightScenePosition, whiteLight);

	ShapeSet sceneObjects; // holds the objects in the scene
	Sphere sceneSphere(origin, 1.75, prettyBlue); // create a default sphere for the scene
	Plane scenePlane(planePosition,y, someColor); //Todo: place a plane just under the scene sphere. Double check
	sceneObjects.addShape(&scenePlane);
	sceneObjects.addShape(&sceneSphere);

	std::cout << sceneCamera.camDown.x << " " << sceneCamera.camDown.y << " " << sceneCamera.camDown.z << std::endl;

	int currentPixel = 0;
	float xOffset = 0, yOffset = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			currentPixel = y * width + x; // set the current pixel we are dealing with
			///create offset rays from the camera Todo: Shift ray generation into the camera class
			if (width > height)
			{
				///if image is wider than it is tall
				xOffset = (x + 0.5) / width * aspectRatio - ((width - height) / height) / 2;
				yOffset = ((height - y) + 0.5f) / height;
			}
			else if (height > width)
			{
				///if image is taller than it is wide
				xOffset = (x + 0.5) / width;
				yOffset = ((height - y) + 0.5f) / height / aspectRatio - ((height - width) / width) / 2;
			}
			else
			{
				///the image is a square
				xOffset = (x + 0.5f) / width;
				yOffset = ((height - y) + 0.5f) / height;
			}

			Point originOfRays = sceneCamera.camPosition; // set the source of camera rays to be, sensibly, the camera. Kept in loop to account for a moving camera.
			Vector directionOfCurrentRay = sceneCamera.camDirection + (sceneCamera.camRight * (xOffset - 0.5)) + (sceneCamera.camDown * (yOffset - 0.5)); // calculate current ray's direction
			directionOfCurrentRay.normalize();

			Ray currentCameraRay(originOfRays, directionOfCurrentRay);// create the new ray to test

			Intersection intersect(currentCameraRay);// create an intersection object with the current ray

			///loop throught the shapeset and if there is an intesect with the current ray and an object in the scene
			if (sceneObjects.findIntersect(intersect) == true)
			{
				Color objectColor = intersect.object->getColor(); // color the appropriate pixel the appropriate color
				if(imageData != nullptr)
				{
					imageData[x * height + y].B = objectColor.blue * 255;
					imageData[x * height + y].G = objectColor.green * 255;
					imageData[x * height + y].R = objectColor.red * 255;
				}
				
			}
			
		}
	}



	BitMap::generateBitmapWithRGB(imageData, "imageText2.bmp", height, width, BYTESPERPIXEL, 72);
	//generateColorGradient(255, 0, 0, height, width);

	free(imageData);
	return 0;
}

void rayTrace(ShapeSet& sceneObjects, Camera& sceneCamera, Light& sceneLight, int width, int height, float aspectRatio) 
{
	int currentPixel = 0;
	float xOffset = 0, yOffset = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			currentPixel = y * width + x; // set the current pixel we are dealing with
			///create offset rays from the camera
			if (width > height)
			{
				///if image is wider than it is tall
				xOffset = (x + 0.5) / width * aspectRatio - ((width - height) / height) / 2;
				yOffset = ((height - y) + 0.5f) / height;
			}
			else if (height > width)
			{
				///if image is taller than it is wide
				xOffset = (x + 0.5) / width;
				yOffset = ((height - y) + 0.5f) / height / aspectRatio - ((height - width) / width) / 2;
			}
			else
			{
				///the image is a square
				xOffset = (x + 0.5f) / width;
				yOffset = ((height - y) + 0.5f) / height;
			}

			Point originOfRays = sceneCamera.camPosition; // set the source of camera rays to be, sensibly, the camera. Kept in loop to account for a moving camera.
			Vector directionOfCurrentRay = sceneCamera.camDirection + (sceneCamera.camRight * (xOffset - 0.5)) + (sceneCamera.camDown * (yOffset - 0.5)); // calculate current ray's direction
			directionOfCurrentRay.normalize();
			
			Ray currentCameraRay(originOfRays, directionOfCurrentRay);
		}

	}
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