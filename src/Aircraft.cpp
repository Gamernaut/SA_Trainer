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
#include "aircraft.h"
#include "Main.h"


// Call the constructor in then base class to load the image
Aircraft::Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {

}


Aircraft::~Aircraft() {

}


void Aircraft::SetRandomHeading() {

	srand((unsigned)time(0));
	current_heading_ = (rand() % 360);
}


int Aircraft::GetHeading() {

	return static_cast<int>(current_heading_);
}
