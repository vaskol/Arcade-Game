#pragma once


#include <random>

float rand0to1();



struct Shape		
{
	float cx = -100.0f; 
	float cy = -100.0f;

	Shape() {}

	Shape(float sh_cx, float sh_cy)
		:cx(sh_cx), cy(sh_cy)
	{
	}
};

struct Disk : Shape
{
	float radius = 0.0f;	

	Disk() {}

	Disk(float cir_cx, float cir_cy, float cir_radius)
		: Shape(cir_cx, cir_cy), radius(cir_radius)
	{
	}
};

struct Rectangle : Shape
{
	float rec_width = 0.0f;		//rectangle width
	float rec_height = 0.0f;		//rectangle height

	/*float x1, y1;		// (x1,y1) is the bottom left rec's corner.
	float x2, y2;		// (x2, y2) is the top right rec's corner.*/

	float topLeftX = -100.f, topLeftY = -100.0f;		// rectangle's top left corner's coordinates.
	float botRightX = -100.0f, botRightY = -100.0f;		// rectangle's bottom right corner's coordinates.

	Rectangle() {}

	Rectangle(float rec_cx, float rec_cy, float sh_rec_width, float sh_rec_height)
		: Shape(rec_cx, rec_cy), rec_width(sh_rec_width), rec_height(sh_rec_height)
	{
		topLeftX = cx - rec_width / 2;
		topLeftY = cy - rec_height / 2;
		botRightX = cx + rec_width / 2;
		botRightY = cy + rec_height / 2;
	}
};
