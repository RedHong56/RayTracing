#include "color.h"
#include "vec3.h"

#include <iostream>

int main()
{
	// Image
	const int ImageWidth = 256;
	const int ImageHeight = 256;

	// Render
	std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
	for (int j = 0 ; j < ImageHeight; ++j)
	{
		for (int i = 0; i < ImageWidth; ++i)
		{
			auto PixelColor = Color(double(i) / (ImageWidth - 1), double(j) / (ImageHeight - 1), 0);
			WriteColor(std::cout, PixelColor, 1);
		}
	}
	std::clog << "\nDone.                          \n";
	return 0;
}