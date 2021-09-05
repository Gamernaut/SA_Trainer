#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Bullseye.h"
#include "config.h"




Bullseye::Bullseye() {
	srand((unsigned)time(0));

	currentBullseye.x = (rand() % 496) + 50;
	currentBullseye.y = (rand() % 512) + 50;
	//std::cout << "mfdPaddingLeft = " << mfdPaddingLeft << std::endl;
	//std::cout << "mfdPaddingTop = " << mfdPaddingTop << std::endl;
	//std::cout << "setupButtonLeftEdge = " << setupButtonLeftEdge << std::endl;
	//std::cout << "setupButtonRightEdge = " << setupButtonRightEdge << std::endl;
	//std::cout << "setupButtonTopEdge = " << setupButtonTopEdge << std::endl;
	//std::cout << "setupButtonBottomEdge = " << setupButtonBottomEdge << std::endl;
	int bearing = calculateBearingToBullseye(Coordinates{ 460,500 });
	std::cout << "Bullseye location x = " << currentBullseye.x << " and y = " << currentBullseye.y << std::endl;
	std::cout << "Bearing to bullseye is " << bearing << std::endl;
}


Bullseye::~Bullseye() {

}


Coordinates Bullseye::generatePosition() {
	return currentBullseye;
}


int Bullseye::calculateBearingToBullseye(Coordinates aircraftPosition) {
	// We'll be using the difference in x1,y1 and x2,y2 coordinates
	// we can use the atan2(y,x) function where y = y2 - y1 and x = x2 -x1 where x1,y1 is the starting point
	// However, this function can return a negative value when x < 0 so need to adapt formula to give a result between 0 and 359 deg

	double x, y, result;
	x = static_cast<double>(currentBullseye.x) - static_cast<double>(aircraftPosition.x);
	y = static_cast<double>(currentBullseye.y) - static_cast<double>(aircraftPosition.y);
	//result = atan2(y, x) * (180 / PI);
	result = atan2(-y, -x) / (180 * PI) + 180;	// ensures that -x results in a value between 0 -359 deg.
	return static_cast<int>(result);
}

int Bullseye::calculateBearingToBogey(Coordinates aircraftPosition) {

	return 0;
}


Coordinates Bullseye::getCoordinates() {
	return currentBullseye;
}


int Bullseye::calculateDistanceTo(Coordinates coord1) {
	int xdist = currentBullseye.x - coord1.x;
	int ydist = currentBullseye.y - coord1.y;
	double distance = sqrt((xdist * xdist) + (ydist * ydist));
	return static_cast<int>(distance);
}