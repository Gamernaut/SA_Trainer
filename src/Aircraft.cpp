///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "aircraft.h"
#include "maths_functions.h"

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

void Aircraft::DrawBogey(SDL_Renderer* renderer, std::unique_ptr<Aircraft>& my_aircraft, Coordinate bulls_pos,/*std::unique_ptr<Bullseye>& bullseye*/ double miles_per_pixel) {

	// Render a filled white rectangle at the bogey position with a short line indicating the bogeys direction
	int bogey_box_width = 10;
	int bogey_box_height = 10;
	int line_length = 10;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Call math function to determine the coordinates of the bulls eye as it depends on HSD scale and aircraft heading
	//Coordinate bulls_pos = endpoint_given_start_and_bearing(my_aircraft->image_center_, bullseye->GetBearing(), my_aircraft.get()->GetHeading(), bullseye->GetDistance(), miles_per_pixel);


	// Call math function to determine the coordinates of the bogey (image_center does not match actual bulls center it's aircraft datum center)
	Coordinate bogey_pos = endpoint_given_start_and_bearing(bulls_pos, GetBearingFromBullseye(), my_aircraft.get()->GetHeading(), GetDistanceFromBullseye(), miles_per_pixel);
	SDL_Rect bogey_image = { bogey_pos.x - (bogey_box_width / 2), bogey_pos.y - (bogey_box_height / 2), bogey_box_width, bogey_box_height };
	SDL_RenderFillRect(renderer, &bogey_image);

	// Call math function to determine the coordinates of the end of the direction line for the bogey
	Coordinate bogey_direction_line = endpoint_given_start_and_bearing(bogey_pos, GetHeading(), 0, line_length, 0.70);
	SDL_RenderDrawLine(renderer, bogey_pos.x, bogey_pos.y, bogey_direction_line.x, bogey_direction_line.y);
	// Render screen
	// SDL_RenderPresent(renderer);
}

// Protected methods
Coordinate Bearing_to_xy_position(int bearing) {
	return { 0,0 };
}

//// Method to position the bogey in any orientation around the bullseye at between 5 and 40nm
//BearingRangeAltitude Aircraft::RandomiseBearingAndDistance() {
//	BearingRangeAltitude tempBearingDist = { 0,0 };
//	tempBearingDist.bearing = rand() % 359 + 1;
//	// Create bulls between 5 and 40nm away
//	tempBearingDist.distance = rand() % 35 + 5;
//	return tempBearingDist;
//}

// Method to position the aircraft in any orientation around the bulls between 5 and 30nm
void Aircraft::SetRandomBearingAndDistanceFromBullseye() {
	aircraft_relative_bra_.bearing = rand() % 359 + 1;
	// Create bulls between 5 and 30nm away
	aircraft_relative_bra_.distance = rand() % 25 + 5;
	// Set altitude between 15,000 and 40,000 feet
	aircraft_relative_bra_.altitude = rand() % 25 + 15;
}

int Aircraft::GetDistanceFromBullseye() {
	return aircraft_relative_bra_.distance;
}


int Aircraft::GetBearingFromBullseye() {
	return aircraft_relative_bra_.bearing;
}


int Aircraft::GetAltitude() {
	return aircraft_relative_bra_.altitude;
}

void Aircraft::SetPosition(BearingRangeAltitude start_position) {
	aircraft_relative_bra_.bearing = start_position.bearing;
	aircraft_relative_bra_.distance = start_position.distance;
	aircraft_relative_bra_.altitude = start_position.altitude;
}

void Aircraft::SetAwacsString(std::string awacs_call) {
	awacs_call_string = awacs_call;
}

std::string Aircraft::GetAwacsString() {
	return awacs_call_string;
}