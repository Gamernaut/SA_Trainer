///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Aircraft.h"

// Call the constructor in then base class to load the image
Aircraft::Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {

}

Aircraft::~Aircraft() {
}

void Aircraft::SetRandomHeading() {
	current_heading_ = (std::rand() % 360);
}

int Aircraft::GetHeading() {
	return static_cast<int>(current_heading_);
}
