///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


#include "Bullseye.h"


using namespace cpv;

// Call the constructor in the base class to load the image
Bullseye::Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {
}

Bullseye::~Bullseye() {
}

Coordinate Bullseye::GetPosition() {
	return image_center_;
}

// Method to position the bulls eye in any orientation around the aircraft at between 5 and 60nm
void Bullseye::SetRandomBearingAndDistance() {
	bulls_relative_bra_.bearing = rand() % 359 + 1;
	// Create bulls between 5 and 60nm away
	bulls_relative_bra_.distance = rand() % 55 + 5;

}

int Bullseye::GetDistance() {
	return bulls_relative_bra_.distance;
}


int Bullseye::GetBearing() {
	return bulls_relative_bra_.bearing;
}

int Bullseye::GetAltitude() {
	return bulls_relative_bra_.altitude;
}

void Bullseye::SetPosition(BearingRangeAltitude start_position) {
	bulls_relative_bra_.bearing = start_position.bearing;
	bulls_relative_bra_.distance = start_position.distance;
	bulls_relative_bra_.altitude = start_position.altitude;
}