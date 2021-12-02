///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <stdlib.h>
//#include <iostream>
//#include <math.h>
#include "Bullseye.h"

using namespace cpv;

// Call the constructor in the base class to load the image
Bullseye::Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {
}

Bullseye::~Bullseye() {
}

void Bullseye::SetPosition(Coordinate newPosition) {
	image_center_.x = newPosition.x;
	image_center_.y = newPosition.y;
}

Coordinate Bullseye::GetPosition() {
	return image_center_;
}

// TODO: Remove this function once HSD code is integrated
int Bullseye::Bearing_FromPoint1ToPoint2(Coordinate point1, Coordinate point2) {
	// We'll be using the difference in x1,y1 and x2,y2 coordinates
	// we can use the atan2(y,x) function where y = y2 - y1 and x = x2 - x1 where x1,y1 is the starting point
	// However, this function can return a negative value when x < 0 so need to adapt formula to give a result between 0 and 359 deg

	const double kTwoPi = 6.2831853071795865;
	const double kRad2Deg = 57.2957795130823209;

	double x1 = static_cast<double>(point1.x);
	double y1 = static_cast<double>(point1.y);
	double x2 = static_cast<double>(point2.x);
	double y2 = static_cast<double>(point2.y);
	double theta = 0.0;

	theta = atan2(x2 - x1, y1 - y2);
	if (theta < 0.0)
		theta += kTwoPi;
	return static_cast<int>(kRad2Deg * theta);
}


// TODO: Remove this function once HSD code is integrated
int Bullseye::Distance_BetweenPoint1AndPoint2(Coordinate start_point, Coordinate end_point) {
	int xdist = start_point.x - end_point.x;
	int ydist = start_point.y - end_point.y;
	double distance = sqrt((xdist * xdist) + (ydist * ydist));
	return static_cast<int>(distance);
}