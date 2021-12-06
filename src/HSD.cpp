///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Abstraction of the Horizontal Situation Display. This is a type of MFD (Multi Function Display) and is surrounded 
//				by OSBs (On-Screen Buttons).
//              This class holds the overall state of the HSD, it knows settings such as the range, in the app world, and where the 
//				various objects are on the HSD. It uses the maths functions and returns the in app distance and angles between various
//				objects. It also knows about the buttons around the edge and updates the state based on their settings.
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "hsd.h"

using namespace cpv;

HSD::HSD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(renderer, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
	PLOG_INFO << "HSD constructor called";
}

HSD::~HSD() {

}

void HSD::SetCenteredState(bool new_state) {
	// Do I need to tie this into the display
	centered_ = new_state;
}

bool HSD::GetCenteredState(void) {
	return centered_;
}

double HSD::GetMilesPerPixel(void) {
	// Take the number of pixels between the center and the outer ring, about 320px, and divide by range in miles to get miles per miles
	return static_cast<double>(kHSDDistRingsImageWidth_) / static_cast<double>(GetCurrentRange());
}

void HSD::IncreaseRange(void) {
	int range_size = HSD_ranges.size();

	if (range_level_ <= range_size) {
		range_level_ += 1;
	}
	else {
		range_level_ = 0;
	}
}

void HSD::DecreaseRange(void) {
	if (range_level_ >= 0) {
		range_level_ -= 1;
	}
	else {
		range_level_ = 0;
	}
}

int HSD::GetCurrentRange() {
	if (GetCenteredState()) {
		return HSD_centered_ranges[range_level_];
	}
	else {
		return HSD_ranges[range_level_];
	}
}


// TODO: Need to rewrite this to use the distance_between_point_a_and_b_in_pixels function in MathsFunctions then multiply by GetMilesPerPixel()
int HSD::Distance_BetweenPoint1AndPoint2(Coordinate point1, Coordinate point2) {
	// Use Pythagoras' therom to calculate the number of pixels between the 2 points
	double xdist = static_cast<double>(point1.x) - static_cast<double>(point2.x);
	double ydist = static_cast<double>(point1.y) - static_cast<double>(point2.y);

	// convert pixels to a distance based on the range setting on the HSD so we have the "in sim" distance between the points
	xdist = xdist * GetMilesPerPixel();
	ydist = ydist * GetMilesPerPixel();

	double distance = sqrt((xdist * xdist) + (ydist * ydist));
	return static_cast<int>(distance);
}

std::unique_ptr<OnSceenButton> HSD::AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text) {
	PLOG_VERBOSE << "HSD::AddObcButton called with 7 parameters";
	return std::make_unique<OnSceenButton>(xPos, yPos, xPosEnd, yPosEnd, toggelable, button_name, onscreen_text);
}

std::unique_ptr<OnSceenButton> HSD::AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name) {
	PLOG_VERBOSE << "HSD::AddObcButton called with 6 parameters";
	return std::make_unique<OnSceenButton>(xPos, yPos, xPosEnd, yPosEnd, toggelable, button_name);
}