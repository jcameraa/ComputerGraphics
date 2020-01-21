/** @file main.cpp
 *  @brief Entry point into our program.
 *
 *  Welcome to the Great Looking Software Render
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with:
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

 // Load our libraries
#include <iostream>

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>

// User libraries
#include "GL.h"
#include "Color.h"
#include "TGA.h"
#include "Maths.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH, WINDOW_HEIGHT);




// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c) {
	bool steep = false;
	if (std::abs(v0.x - v1.x) < std::abs(v0.y - v1.y)) {
		// If the line is steep we want to transpose the image.
		std::swap(v0.x, v0.y);
		std::swap(v1.x, v1.y);
		steep = true;
	}
	if (v0.x > v1.x) {  // make it left-to-right
		std::swap(v0.x, v1.x);
		std::swap(v0.y, v1.y);
	}
	for (int x = v0.x; x <= v1.x; ++x) {
		float t = (x - v0.x) / (float)(v1.x - v0.x);
		int y = v0.y*(1.0f - t) + v1.y*t;
		if (steep) {
			canvas.setPixelColor(y, x, c);
		}
		else {
			canvas.setPixelColor(x, y, c);
		}
	}
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2, TGA& image, ColorRGB c) {
	if (glFillMode == LINE) {
		drawLine(v0, v1, image, c);
		drawLine(v1, v2, image, c);
		drawLine(v2, v0, image, c);
	}
	/*
	if (glFillMode == FILL) {
		std::cout << "Being Filled!" << std::endl;
		if (v1.y == v2.y) {
			fillBottomFlatTriangle(v0, v1, v2, c);
		}
		else if (v0.y == v1.y) {
			fillTopFlatTriangle(v0, v1, v2, c);
		}
		else {
			Vec2 v3;
			v3.x = 3;
			v3.y = 6;
			fillBottomFlatTriangle(v0, v1, v3, c);
			fillTopFlatTriangle(v1, v3, v2, c);
		}

	}
	*/
}



// Main
int main() {
	std::cout << "AJHSAJHJSHJAHSJHSJ" << std::endl;

	// A sample of color(s) to play with
	ColorRGB red;
	red.r = 255; red.g = 0; red.b = 0;


	// Points for our Line
	Vec2 line[2] = { Vec2(0,0), Vec2(100,100) };

	// Set the fill mode
	glPolygonMode(LINE);

	// Draw a line
	drawLine(line[0], line[1], canvas, red);

	// Data for our triangle
	Vec2 tri[3] = { Vec2(160,60),Vec2(150,10),Vec2(75,190) };

	// Draw a triangle
	triangle(tri[0], tri[1], tri[2], canvas, red);

	// Output the final image
	canvas.outputTGAImage("graphics_lab2.ppm");


	return 0;
}
void fillBottomFlatTriangle(Vec2 v0, Vec2 v1, Vec2 v2, ColorRGB c) {
	float invSlope0 = ((v1.x - v1.x) / (v1.y - v0.y));

	float invSlope1 = ((v2.x - v0.x) / (v2.y - v0.y));

	float currX1 = v0.x;
	float currX2 = v0.x;

	for (int scaleY = v0.y; scaleY <= v1.y; scaleY++) {
		Vec2 point1;
		point1.x = currX1;
		point1.y = scaleY;

		Vec2 point2;
		point2.x += currX2;
		point2.y += scaleY;

		drawLine(point1, point2, canvas, c);

		currX1 += invSlope0;
		currX2 += invSlope1;
	}
}

void fillTopFlatTriangle(Vec2 v0, Vec2 v1, Vec2 v2, ColorRGB c) {
	float invSlope0 = ((v2.x - v0.x) / (v2.y - v0.y));

	float invSlope1 = ((v2.x - v1.x) / (v2.y - v1.y));

	float currX1 = v2.x;
	float currX2 = v2.x;

	for (int scaleY = v2.y; scaleY <= v0.y; scaleY--) {
		Vec2 point1;
		point1.x = currX1;
		point1.y = scaleY;

		Vec2 point2;
		point2.x -= currX2;
		point2.y -= scaleY;

		drawLine(point1, point2, canvas, c);

		currX1 -= invSlope0;
		currX2 -= invSlope1;
	}


}







