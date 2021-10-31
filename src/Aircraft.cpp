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

using namespace cpv;

// Call the constructor in then base class to load the image
Aircraft::Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) : ImageObject(renderer, filename, xPosition, yPosition) {

}

Aircraft::~Aircraft() {
}


// Public methods
void Aircraft::SetRandomHeading() {
	current_heading_ = (std::rand() % 360);
}

int Aircraft::GetHeading() {
	return static_cast<int>(current_heading_);
}

//void Aircraft::Draw(SDL_Renderer* renderer) {
//	// This is used mainly for bogeys so should render a filled white rectangle at the bogey position
//	int bogey_box_width = 10;
//	int bogey_box_height = 10;
//	SDL_Rect bogey_image = { image_center_.x - (bogey_box_width / 2), image_center_.y - (bogey_box_height / 2), bogey_box_width, bogey_box_height };
//	SDL_RenderFillRect(renderer, &bogey_image);
//	SDL_RenderDrawLine(renderer, image_center_.x, image_center_.y, image_center_.x + 20, image_center_.y + 20);
//}
//
//// Protected methods
//Coordinates Bearing_to_xy_position(int bearing) {
//	return { 0,0 };
//}
