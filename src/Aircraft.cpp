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

void Aircraft::DrawBogey(SDL_Renderer* renderer, std::unique_ptr<Aircraft> &my_aircraft_) {
	// This is used mainly for bogeys so should render a filled white rectangle at the bogey position with a short line indicating the bogeys direction
	int bogey_box_width = 10;
	int bogey_box_height = 10;
	SDL_Rect bogey_image = { image_center_.x - (bogey_box_width / 2), image_center_.y - (bogey_box_height / 2), bogey_box_width, bogey_box_height };
	SDL_RenderFillRect(renderer, &bogey_image);

	// Bit of trigonometry to work out the end co-ordinates based on the relative headings
	// the basic equation is to add the sin of the angle multiplied by the line length to get the new X position
	// for the new y position you use th cosine function. However, as the y position increases in value as you go down the screen we have to use the 
	// -cosine to get the y position. So the formula are:
	// 
	//		new x = old x + ( length of line * sine (bogey heading in radians)
	//		new y = old y + ( length of line * -cosine (bogey heading in radians)
	//
	// However, these formula assume that the F16 is heading north, but that will most likely not be the case so these formula also need to take 
	// account of the F16s heading otherwise the line will always be drawn as if straight up is north. Basically we need the difference in angle
	// between the F16 heading and the bogey heading and use that to calculate the new x,y position for the end of the line. Lets take the 
	// example of the F16 on a heading of 315 (NW) and a bogey heading 90 (East). If we calculate the end of line on the bogeys 90 heading it 
	// actually looks like it's heading SE once you mentally rotate the F16s heading from NW to N. A really easy way to get the difference
	// is to add the 2 headings together and take the modulo with 360 as that effectively divides by 1 "circle" of the compass leaving as
	// a remainder the difference in degrees between the headings. Note Modulo only works on ints so cast to int. The formula would be 
	//
	//		difference in heading = (heading of F16 + Heading of bogey) % 360
	//
	// For the example above that would be (315 + 90) % 360 = 45 
	// now use the formulas above to calculate the new ending positions with an angle of 45 deg (in radians).

	double deg_to_rads = M_PI / 180;
	int new_X = 0, new_Y = 0;
	int difference_in_angle = 0;
	int line_length = 10;

	difference_in_angle = (static_cast<int>(current_heading_) + static_cast<int>(my_aircraft_->current_heading_)) % 360;

	new_X = static_cast<int>(image_center_.x + (line_length * sin(difference_in_angle * deg_to_rads)));
	new_Y = static_cast<int>(image_center_.x + (line_length * -cos(difference_in_angle * deg_to_rads)));

	SDL_RenderDrawLine(renderer, image_center_.x, image_center_.y, new_X, new_Y);
}

// Protected methods
Coordinates Bearing_to_xy_position(int bearing) {
	return { 0,0 };
}
