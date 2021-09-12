///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:	
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Bullseye.h"
#include "Main.h"


// Call the constructor in then base class to load the image
Bullseye::Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {
	// currentPosition.x = xPosition;
	// currentPosition.y = yPosition;
}


Bullseye::~Bullseye() {

}


void Bullseye::SetPosition(Coordinates newPosition) {
	position_.x = newPosition.x;
	position_.y = newPosition.y;
}


Coordinates Bullseye::GetPosition() {
	return position_;
}


int Bullseye::CalculateBearingToBullseye(Coordinates aircraftPosition) {
	// We'll be using the difference in x1,y1 and x2,y2 coordinates
	// we can use the atan2(y,x) function where y = y2 - y1 and x = x2 -x1 where x1,y1 is the starting point
	// However, this function can return a negative value when x < 0 so need to adapt formula to give a result between 0 and 359 deg

	const double kTwoPI = 6.2831853071795865;
	const double kRad2Deg = 57.2957795130823209;

	double x2 = static_cast<double>(position_.x);
	double y2 = static_cast<double>(position_.y);
	double x1 = static_cast<double>(aircraftPosition.x);
	double y1 = static_cast<double>(aircraftPosition.y);
	double theta = 0.0;

	theta = atan2(x2 - x1, y1 - y2);
	if (theta < 0.0)
		theta += kTwoPI;
	return static_cast<int>(kRad2Deg * theta);
}


int Bullseye::CalculateBearingToBogey(Coordinates aircraftPosition) {

	return 0;
}


int Bullseye::CalculateDistanceTo(Coordinates coord1) {
	int xdist = position_.x - coord1.x;
	int ydist = position_.y - coord1.y;
	double distance = sqrt((xdist * xdist) + (ydist * ydist));
	return static_cast<int>(distance);
}