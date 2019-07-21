#include <iostream>
#include <time.h>
#include "BitMap.h"
#include "camera.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"


#define BYTESPERPIXEL 3
#define BOUNCE_LIMIT 15

int bounceCount = 0;
void generateColorGradient(int blueValue, int redValue, int greenValue, int height, int width);
Vector calculateReflectionDirection(const Intersection& intersection);
Color getIntersectingColor(const Intersection& intersect, const float& ambientLight, const std::vector<Light*>& lights, ShapeSet& sceneObjects);

int main(int argc, char* argv[])
{
	clock_t startTime, endTime, currentTime, processTime;
	startTime = clock();
	int height = 1600;
	int width = 1200;
	RGBType* imageData = (RGBType*) calloc(width * height, sizeof(RGBType));
	float aspectRatio = (float) width / height;
	Vector origin(0.0f, 1.0f, 0.0f);
	Vector secondSpherePlace(2.0f, 1.0f, -2.0f);
	Vector planePosition(0.0f, -0.25f, 0.0f); 
	Vector wallPosition(0.0f, 0.0f, 7.0f);
	Vector x(1.0, 0.0, 0.0);
	Vector y(0.0, 1.0, 0.0);
	Vector z(0.0, 0.0, 1.0);
	float ambientLight = 0.33;
	Point lookTowards; // create a point we that looks towards the origin
	Vector currentCameraPosition(0.0f, 4.0f, -7.0f); // the current camera position
	
	Camera sceneCamera(lookTowards, currentCameraPosition);

	Color whiteLight(1.0f, 1.0f, 1.0f, 0.0f);
	Color prettyBlue(0.3f, 1.0f, 0.2f, 0.66f);
	Color pureRed(1.0f, 0.0f, 0.0f, 0.7f);
	Color gray(0.5f, 0.5f, 0.5f, 0.80f);
	Color someColor(0.50f, 0.25f, 0.30f, 0.0f);
	Color tiled(1.0f, 1.0f, 1.0f, 2.0f);
	Color black(0.0f, 0.0f, 0.0f, 0.0f);

	/// Todo: try to abstract to light class
	Vector lightScenePosition(7.0f, 8.0f, 5.0f);
	Vector secondSceneLight(-7.0f, 8.0f, 12.0f);
	Light secondLight(secondSceneLight, whiteLight);
	Light sceneLight(lightScenePosition, whiteLight);
	std::vector<Light*> lightSources;
	lightSources.push_back(&sceneLight);
	//lightSources.push_back(&secondLight);

	ShapeSet sceneObjects; // holds the objects in the scene
	Sphere sceneSphere(origin, 1.25, prettyBlue); // create a default sphere for the scene
	Sphere secondSphere(secondSpherePlace, 0.66f, gray);
	Plane wall(wallPosition, z, whiteLight);
	Plane scenePlane(planePosition, y, tiled); //Todo: place a plane just under the scene sphere. Double check
	sceneObjects.addShape(&scenePlane);
	sceneObjects.addShape(&sceneSphere);
	sceneObjects.addShape(&secondSphere);
	sceneObjects.addShape(&wall);

	currentTime = clock(); // get the current time and use it to check how long it took to get to this point.
	std::cout << "Beginning rendering of the scene after " << (currentTime - startTime)/1000.0f << std::endl;
	processTime = currentTime; // start time is now the start of the rendering process
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
				if(imageData != nullptr)
				{
					Color colorAtIntersection = getIntersectingColor(intersect, ambientLight, lightSources, sceneObjects);
					imageData[currentPixel].B = colorAtIntersection.blue * 255 ;
					imageData[currentPixel].G = colorAtIntersection.green  * 255;
					imageData[currentPixel].R = colorAtIntersection.red * 255;
				}				
			}
			
		}
	}
	currentTime = clock();
	std::cout << "Rendering took: " << (currentTime - processTime)/1000.0f << " seconds." << std::endl;
	std::cout << "Beginning generation of the bitmap image" << std::endl;
	BitMap::generateBitmapWithRGB(imageData, "Changed2.bmp", height, width, BYTESPERPIXEL, 72);
	//generateColorGradient(255, 0, 0, height, width);
	free(imageData);
	endTime = clock();
	std::cout << "\nTotal execution time was " << (endTime - startTime)/1000.0f << " seconds." << std::endl;
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

Color getIntersectingColor(const Intersection& intersect, const float& ambientLight, const std::vector<Light*>& lights, ShapeSet& sceneObjects)
{
	Color objectColor = intersect.object->getColor(); // the pure color of the object
	Point intersectionPoint = intersect.ray.origin + intersect.ray.direction * intersect.t; // calculate from the intersection the point of intersection	

	// if the color asked to be checkerboarded, generate the checkerboard.
	if(objectColor.special == 2)
	{
		int squareSize = (int)floor(intersectionPoint.x) + floor(intersectionPoint.z);

		if (squareSize % 2 == 0)
		{
			objectColor = Color(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			objectColor = Color(1.0f, 1.0f, 1.0f, 0.0f);
		}
	}
	Color returnColor = objectColor * ambientLight;	// the color that will be returned
	Vector normalToIntersect = (intersect.object->getNormal(intersectionPoint)).normalized(); // the normal to the point of intersection

	///We will check for reflections before we apply the shadows.
	float objectDot = dotProduct(normalToIntersect, (-intersect.ray.direction));
	Vector specialScalar = normalToIntersect * objectDot;
	Vector specialScalar2 = (specialScalar + intersect.ray.direction) * 2;
	Vector additive = specialScalar2 - intersect.ray.direction;
	Vector reflectionDirection = additive.normalized();

	Ray reflectionRay(intersectionPoint, reflectionDirection); // create the ray that is leaving the intersection point in the reflected direction
	Intersection reflectionIntersects(reflectionRay); // and use it to check for intersections with objects in the scene
	if (sceneObjects.findIntersect(reflectionIntersects) == true && bounceCount <= BOUNCE_LIMIT)
	{
		bounceCount++;
		Color reflectionColor = getIntersectingColor(reflectionIntersects, ambientLight, lights, sceneObjects); // make a recursive call to get the correct colors.
		if (bounceCount > BOUNCE_LIMIT) // monitor how many times we track a reflected ray and limit it to a certain depth
		{
			bounceCount = 0; 
		}

		returnColor += reflectionColor * objectColor.special;
	}
	
	/// for each light source in the scene, determine it's position relative to the intersection point and calculate how to color the scene
	for (Light* light : lights)
	{
		Vector lightDirection = light->position - intersectionPoint; // the light direction as the difference of the light position and intersection point
		Vector lightDirectionNorm = lightDirection.normalized(); 
		// calculate the direction the light has to move in to make it to the intersection point
		float cosineAngle = dotProduct(normalToIntersect, lightDirectionNorm);//since both vectors are normalized, so their dot product is equal to the cos of the angle between them.

		///if the angle of incident is less than 90 degre
		if (cosineAngle > 0.0)
		{
			float distanceToLightSource = lightDirection.length(); // Todo: move shadow ray generation to light class
			Ray shadowRay(intersectionPoint, lightDirectionNorm, distanceToLightSource);
			Intersection shadowIntersects(shadowRay);

			if (sceneObjects.findIntersect(shadowIntersects)== false)
			{		
				// color the non shaded elements in the scene
				returnColor += objectColor * light->lightColor * cosineAngle ;	// this is non commutative and has interesting results when reversed

				// add specular highlights if the special value range is between 0 and 1
				if (objectColor.special > 0.0f && objectColor.special < 1.0f)
				{
					// calculate the direction of the reflection ray to use in specular lighting
					
					float specular = dotProduct(reflectionDirection, lightDirectionNorm);

					if (specular > 0)
					{
						specular = pow(specular, 10);
						Color lightColor = light->lightColor;
						returnColor += lightColor * specular * objectColor.special;
					}
				}
			}
		}
	}
	returnColor.clip();// address coloring issues if they exist.
	return returnColor;
}

///used to calculate the direction of the reflected ray by all calculations that need it.
Vector calculateReflectionDirection(const Intersection& intersection)
{
	Vector intersectionPoint = intersection.ray.origin + intersection.ray.direction * intersection.t; // calculate the point of intersection	
	Vector normalToIntersect = (intersection.object->getNormal(intersectionPoint)).normalized(); // then the normal to the point of intersection

	float objectDot = dotProduct(normalToIntersect, (-intersection.ray.direction));
	Vector specialScalar = normalToIntersect * objectDot;
	Vector specialScalar2 = (specialScalar + intersection.ray.direction) * 2;
	Vector additive = specialScalar2 - intersection.ray.direction;
	Vector reflectionDirection = additive.normalized();

	return reflectionDirection;
}