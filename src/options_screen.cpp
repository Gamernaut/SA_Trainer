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

#include "options_screen.h"

using namespace cpv;

OptionsScreen::OptionsScreen(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(renderer, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {

	recruit_button_ = std::make_unique<OnSceenButton>(kOSB20LeftEdge, kOSB20TopEdge, kOSB20RightEdge, kOSB20BottomEdge, false, "OSB20", "Recruit");
	cadet_button_ = std::make_unique<OnSceenButton>(kOSB19LeftEdge, kOSB19TopEdge, kOSB19RightEdge, kOSB19BottomEdge, false, "OSB19", "Cadet");
	rookie_button_ = std::make_unique<OnSceenButton>(kOSB18LeftEdge, kOSB18TopEdge, kOSB18RightEdge, kOSB18BottomEdge, false, "OSB18", "Rookie");
	veteran_button_ = std::make_unique<OnSceenButton>(kOSB17LeftEdge, kOSB17TopEdge, kOSB17RightEdge, kOSB17BottomEdge, false, "OSB17", "Veteran");
	ace_button_ = std::make_unique<OnSceenButton>(kOSB16LeftEdge, kOSB16TopEdge, kOSB16RightEdge, kOSB16BottomEdge, false, "OSB16", "Ace");
	select_button_ = std::make_unique<OnSceenButton>(kOSB14LeftEdge, kOSB14TopEdge, kOSB14RightEdge, kOSB14BottomEdge, false, "OSB14", "SELECT");
	cancel_button_ = std::make_unique<OnSceenButton>(kOSB12LeftEdge, kOSB12TopEdge, kOSB12RightEdge, kOSB12BottomEdge, false, "OSB12", "CANCEL");
	verbose_button_ = std::make_unique<OnSceenButton>(kOSB7LeftEdge, kOSB7TopEdge, kOSB7RightEdge, kOSB7BottomEdge, false, "OSB7", "Verbose");
	info_button_ = std::make_unique<OnSceenButton>(kOSB8LeftEdge, kOSB8TopEdge, kOSB8RightEdge, kOSB8BottomEdge, false, "OSB20", "Info");
	critical_button_ = std::make_unique<OnSceenButton>(kOSB9LeftEdge, kOSB9TopEdge, kOSB9RightEdge, kOSB9BottomEdge, false, "OSB20", "Critical");

	font_18_ = std::make_unique<TextObject>(renderer_, kFontName, 18);
	font_16_ = std::make_unique<TextObject>(renderer_, kFontName, 16);

}


OptionsScreen::~OptionsScreen() {

}


void OptionsScreen::Draw(int loggingLevel) {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	font_18_->Draw(renderer_, "Training Difficulty", kMfdGreenColour, kMfdPaddingLeft + 100, kMfdPaddingTop + 123);
	font_16_->Draw(renderer_, "Recruit", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 200);
	font_16_->Draw(renderer_, "Cadet", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 275);
	font_16_->Draw(renderer_, "Rookie", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 355);
	font_16_->Draw(renderer_, "Veteran", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 430);
	font_16_->Draw(renderer_, "Ace", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 510);
	font_16_->Draw(renderer_, "CANCEL", kMfdWhiteColour, 430, 795);
	font_16_->Draw(renderer_, "SELECT", kMfdWhiteColour, 255, 795);
	font_16_->DrawCenteredText(renderer_, "Click on a button to get a description.", kMfdWhiteColour, kMfdPaddingTop + 570);
	
	font_18_->Draw(renderer_, "Logging Level", kMfdGreenColour, kMfdPaddingLeft + 475, kMfdPaddingTop + 123);
	if (loggingLevel == 1) {
		font_16_->HighlightedDraw(renderer_, "High", kMfdBlack, kMfdGreenColour, kMfdPaddingLeft + 596, kMfdPaddingTop + 275);
		font_16_->Draw(renderer_, "Medium", kMfdWhiteColour, kMfdPaddingLeft + 576, kMfdPaddingTop + 355);
		font_16_->Draw(renderer_, "Low", kMfdWhiteColour, kMfdPaddingLeft + 601, kMfdPaddingTop + 430);
	} else if (loggingLevel == 2) {
		font_16_->Draw(renderer_, "High",  kMfdWhiteColour, kMfdPaddingLeft + 596, kMfdPaddingTop + 275);
		font_16_->HighlightedDraw(renderer_, "Medium", kMfdBlack, kMfdGreenColour, kMfdPaddingLeft + 576, kMfdPaddingTop + 355);
		font_16_->Draw(renderer_, "Low", kMfdWhiteColour, kMfdPaddingLeft + 601, kMfdPaddingTop + 430);
	} else if (loggingLevel == 3) {
		font_16_->Draw(renderer_, "High", kMfdWhiteColour, kMfdPaddingLeft + 596, kMfdPaddingTop + 275);
		font_16_->Draw(renderer_, "Medium", kMfdWhiteColour, kMfdPaddingLeft + 576, kMfdPaddingTop + 355);
		font_16_->HighlightedDraw(renderer_, "Low", kMfdBlack, kMfdGreenColour, kMfdPaddingLeft + 601, kMfdPaddingTop + 430);
	}  else {
		PLOG_ERROR << "OptionsScreen::Draw loggingLevel was not 1, 2 or 3. Caught by default else";
	}

	// Draw the outlines for all the on screen buttons
	recruit_button_->DrawOutline(renderer_);
	cadet_button_->DrawOutline(renderer_);
	rookie_button_->DrawOutline(renderer_);
	veteran_button_->DrawOutline(renderer_);
	ace_button_->DrawOutline(renderer_);
	select_button_->DrawOutline(renderer_);
	cancel_button_->DrawOutline(renderer_);
	verbose_button_->DrawOutline(renderer_);
	info_button_->DrawOutline(renderer_);
	critical_button_->DrawOutline(renderer_);

	mfd_frame_->Draw(renderer_);
	SDL_RenderPresent(renderer_);
}



void OptionsScreen::DrawRecruitText() {
	font_16_->Draw(renderer_, "Description for Recruit level", kMfdGreenColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 225);
	font_16_->Draw(renderer_, "Click on the HSD as close as you can", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 260);
	font_16_->Draw(renderer_, "to where you think the bullseye is,", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 280);
	font_16_->Draw(renderer_, "distance is NOT important.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 300);
	font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 400);
	font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 420);
	font_16_->Draw(renderer_, "to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 440);
}


void OptionsScreen::DrawCadetText() {
	font_16_->Draw(renderer_, "Description for Cadet level", kMfdGreenColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 225);
	font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 260);
	font_16_->Draw(renderer_, "where you think the bullseye is. Both", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 280);
	font_16_->Draw(renderer_, "bearing and distance count.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 300);
	font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 400);
	font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 420);
	font_16_->Draw(renderer_, "distance to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 440);
}


void OptionsScreen::DrawRookieText() {
	font_16_->Draw(renderer_, "Description for Rookie level", kMfdGreenColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 225);
	font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 260);
	font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 280);
	font_16_->Draw(renderer_, "where you think the bullseye is. Only ", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 300);
	font_16_->Draw(renderer_, "bearing to the bogey from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 320);
	font_16_->Draw(renderer_, "counts.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 340);
	font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 400);
	font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing to", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 420);
	font_16_->Draw(renderer_, "the bogey from the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 440);
}


void OptionsScreen::DrawVeteranText() {
	font_16_->Draw(renderer_, "Description for Veteran level", kMfdGreenColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 225);
	font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 260);
	font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 280);
	font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 300);
	font_16_->Draw(renderer_, "bearing and distance to the bogey", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 320);
	font_16_->Draw(renderer_, "count.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 340);
	font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 400);
	font_16_->Draw(renderer_, "Get within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 420);
	font_16_->Draw(renderer_, "distance to the bogey.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 440);

}


void OptionsScreen::DrawAceText() {
	font_16_->Draw(renderer_, "Description for Ace level", kMfdGreenColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 225);
	font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 260);
	font_16_->Draw(renderer_, "where you think the bogey's are, using", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 280);
	font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 300);
	font_16_->Draw(renderer_, "bearing and distance from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 320);
	font_16_->Draw(renderer_, "to each bogey counts.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 340);
	font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 400);
	font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 420);
	font_16_->Draw(renderer_, "distance to the bogey's.", kMfdWhiteColour, kMfdPaddingLeft + textOffset, kMfdPaddingTop + 440);
}