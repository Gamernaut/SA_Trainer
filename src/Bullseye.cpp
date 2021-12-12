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

void Bullseye::SetPosition(Coordinate newPosition) {
	image_center_.x = newPosition.x;
	image_center_.y = newPosition.y;
}

Coordinate Bullseye::GetPosition() {
	return image_center_;
}
