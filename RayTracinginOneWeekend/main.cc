#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double HitSphere(const Point3& center, double radius, const Ray& r)
{
	Vec3 oc = center - r.Origin();
	auto a = r.Direction().LengthSquared();
	auto h = Dot(r.Direction(), oc);
	auto c = oc.LengthSquared() - radius * radius;
	auto discriminant = h * h -  a * c;

	if (discriminant < 0)
	{
		return -1.0;
	}
	return (h - std::sqrt(discriminant)) / a;
}	

Color RayColor(const Ray& r, const Hittable& world)
{
	HitRecord hitRecord;
	if(world.Hit(r, Interval(0.0, Infinity), hitRecord))
	{
		return 0.5 * Color(hitRecord.Normal + Color(1.0, 1.0, 1.0));
	}

	Vec3 unitDirection = UnitVector(r.Direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);

	return (1.0 - a) * Color(1.0, 1.0, 1.0) 
		+ a * Color(0.5, 0.7, 1.0);
}

int main()
{
	//Image
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;
	int imageHeight = int(imageWidth / aspectRatio); // calculate image height
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	//World
	HittableList world;
	world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

	//Camera
	auto focalLength = 1.0;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double)imageWidth / (double)imageHeight;
	auto cameraCenter = Point3(0, 0, 0);

	auto viewportU = Vec3(viewportWidth, 0, 0); // horizontal vector
	auto viewportV = Vec3(0, -viewportHeight, 0); // vertical vector

	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	auto viewportUpperLeft = 
		cameraCenter 
		- Vec3(0, 0, focalLength) 
		- viewportU / 2 
		- viewportV / 2;
	auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	// Render
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int scanlineIndex = 0; scanlineIndex < imageHeight; scanlineIndex++)
	{
		std::clog << "\rScanlines remaining: " 
			<< imageHeight - scanlineIndex
			<< ' ' 
			<< std::flush;
		for (int pixelIndex = 0; pixelIndex < imageWidth; pixelIndex++)
		{
			auto pixelCenter = pixel00Loc 
				+ (pixelIndex * pixelDeltaU)
				+ (scanlineIndex * pixelDeltaV);

			auto rayDirection = pixelCenter - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			Color pixelColor = RayColor(r, world);
			WriteColor(std::cout, pixelColor);
		}
	}

	std::clog << "\rDone.                                   \n";
}