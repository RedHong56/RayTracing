#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

#include <iostream>

using Color = Vec3; // RGB color alias

void WriteColor(std::ostream& out, Color pixelColor)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();
	// 0~1 -> 0~255
	int rByte = int(255.999 * r);
	int gByte = int(255.999 * g);
	int bByte = int(255.999 * b);

	// Write the translated [0,255] value of each color component.
	out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}
#endif