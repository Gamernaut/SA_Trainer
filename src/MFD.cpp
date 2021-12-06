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

#include "Main.h"
#include "MFD.h"

using namespace cpv;

MFD::MFD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) {
	PLOG_INFO << "MFD constructor called";
	if (!renderer_) {
		renderer_ = renderer;
	}
	mfd_top_edge_ = mfd_top_edge;
	mfd_left_edge_ = mfd_left_edge;
	mfd_height_ = mfd_height;
	mfd_width_ = mfd_width;
	center_point_.x = mfd_left_edge_ + (mfd_width_ / 2);
	center_point_.y = mfd_top_edge_ + (mfd_height_ / 2);
}

MFD::~MFD() {

}

Coordinate MFD::GetCenterPoint(void) {
	return center_point_;
}


void MFD::Draw() {
	PLOG_VERBOSE << "Need to implement MFD::Draw()";
}
