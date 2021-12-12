///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Implementation of the start up splash screen within a MFD outline
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "start_screen.h"

using namespace cpv;

StartScreen::StartScreen(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(renderer, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
	
	PLOG_INFO << "StartScreen constructor called";

	start_screen_text_ = std::make_unique<ImageObject>(renderer_, kSATrainerStartScreenText, (kWindowWidth / 2) - (kGameTitleWidth / 2), (kMfdPaddingTop / 2) -
		(kGameTitleHeight / 2));

	start_screen_image_ = std::make_unique<ImageObject>(renderer_, kSATrainerStartScreenImage, kMfdPaddingLeft, kMfdPaddingTop);

	// Add OSB13 for the start button
	start_button = std::make_unique<OnSceenButton>(kOSB13LeftEdge, kOSB13TopEdge, kOSB13RightEdge, kOSB13BottomEdge, false, "OSB13");

}


StartScreen::~StartScreen() {
	PLOG_INFO << "StartScreen destructor called";
}


void StartScreen::Draw() {
	PLOG_INFO << "StartScreen::Draw() called";
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	start_screen_text_->Draw(renderer_);
	start_screen_image_->Draw(renderer_);

	// Add code to render button stuff
	start_button->DrawOutline(renderer_);

	SDL_RenderPresent(renderer_);
}