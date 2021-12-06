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
	ImageObject* loadingScreenTitle = new ImageObject(renderer_, kGameTitleFilename, (kWindowWidth / 2) - (kGameTitleWidth / 2), (kMfdPaddingTop / 2) -
		(kGameTitleHeight / 2));
	loading_screen_image_list_.push_back(loadingScreenTitle);

	ImageObject* mfdSurround = new ImageObject(renderer_, kGameStartMenuFileName, kMfdPaddingLeft, kMfdPaddingTop);
	loading_screen_image_list_.push_back(mfdSurround);
	PLOG_INFO << "StartScreen constructor called";
}


StartScreen::~StartScreen() {
	PLOG_INFO << "StartScreen destructor called";
}


void StartScreen::Draw() {
	PLOG_INFO << "StartScreen::Draw() called";
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	for (std::size_t i = 0; i < loading_screen_image_list_.size(); ++i) {
		loading_screen_image_list_[i]->Draw(renderer_);
	}

	SDL_RenderPresent(renderer_);
}