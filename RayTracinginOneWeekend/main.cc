#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

Color RayColor(const Ray& r)
{
	return Color(0, 0, 0);
}

int main()
{
	//Image
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	int imageHeight = int(imageWidth / aspectRatio); // calculate image height
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	//Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHight * (double)imageWidth / (double)imageHeight;
	auto cameraCenter = Point3(0, 0, 0);

	auto viewportU = Vec3(viewportWidth, 0, 0); // horizontal vector
	auto viewportV = Vec3(0, viewportHeight, 0); // vertical vector

	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 + viewportV / 2;
	auto pixel00Loc = viewportUpperLeft + 0.5 *(pixelDeltaU + pixelDeltaV);

	// Render
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for(int j = 0 ; j < imageHeight; ++j)
	{
		for(int i = 0; i < imageWidth; ++i)
		{
			auto pixelLoc = pixel00Loc + (double)i * pixelDeltaU - (double)j * pixelDeltaV;
			auto rayDirection = pixelLoc - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			Color pixelColor = RayColor(r);
			WriteColor(std::cout, pixelColor);
		}
		std::clog << "\rDone.                                   \n";
}