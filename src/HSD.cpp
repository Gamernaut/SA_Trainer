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

#include "hsd.h"

using namespace cpv;

HSD::HSD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(renderer, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
	PLOG_INFO << "HSD constructor called";

	PLOG_VERBOSE << "HSD constructor -> creating HSD rings";
	// create distance rings
	hsd_distance_rings_ = std::make_unique<ImageObject>(renderer_, kHSD_DistRingsFileName, kMFDCenter.x - (kHSDDistRingsImageWidth_ / 2), (kMFDCenter.y -
		(kHSDDistRingsImageHeight_ / 2)) + kDepOffset);

	PLOG_VERBOSE << "HSD constructor -> creating HSD bearing ring and pointer";
	// create Bearing ring image
	bearing_ring_ = std::make_unique<ImageObject>(renderer_, kBearingCircle, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);
	bearing_pointer_ = std::make_unique<ImageObject>(renderer_, kBearingPointer, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);

	PLOG_VERBOSE << "HSD constructor -> creating aircraft datum";
	// create my aircraft
	my_aircraft_ = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), (kMFDCenter.y - 5) + kDepOffset);







	PLOG_VERBOSE << "HSD constructor -> creating MFD surround";
	// create MFD background
	mfd_frame_ = std::make_unique<ImageObject>(renderer_, kMfdFileName, kMfdPaddingLeft, kMfdPaddingTop);
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
		range_level_ = range_size;
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

void HSD::Draw() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	// Draw images on game screen, call them with those on the lowest layer first so they get written over
	hsd_distance_rings_->Draw(renderer_);
	bearing_ring_->Draw(renderer_);
	bearing_pointer_->Draw(renderer_);
	my_aircraft_->Draw(renderer_);
	mfd_frame_->Draw(renderer_);
}

//bool SA_Trainer::SetupGameScreen() {
//
//	// create 3 bogey's even if we don't use the all. Which are used are decided by the RoundManager
//	//bogeys[0] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//	//bogeys[1] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//	//bogeys[2] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//	bogeys[0] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//	bogeys[1] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//	bogeys[2] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
//
//	// Create bullseye
//	bullseye_ = std::make_unique<Bullseye>(renderer_, kBullsFileName, 359 - (kBullsImageWidth / 2), 750 - (kBullsImageHeight / 2));
//
//	// create MFD background
//	mfd_frame_ = std::make_unique<ImageObject>(renderer_, kMfdFileName, kMfdPaddingLeft, kMfdPaddingTop);
//
//	// Create the pie slices to indicate a correct or incorrect guess
//	correct_guess_arc_ = std::make_unique<ImageObject>(renderer_, kGreenPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//	wrong_guess_arc_ = std::make_unique<ImageObject>(renderer_, kRedPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//
//	// Create the rectangles to indicate a correct or incorrect guess
//	correct_guess_rect_ = std::make_unique<ImageObject>(renderer_, kGreenRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//	wrong_guess_rect_ = std::make_unique<ImageObject>(renderer_, kRedRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//
//	// Create fonts in 22 and 16 point sizes
//	font_26_ = std::make_unique<TextObject>(renderer_, kFontName, 26);
//	font_24_ = std::make_unique<TextObject>(renderer_, kFontName, 24);
//	font_22_ = std::make_unique<TextObject>(renderer_, kFontName, 22);
//	font_20_ = std::make_unique<TextObject>(renderer_, kFontName, 20);
//	font_18_ = std::make_unique<TextObject>(renderer_, kFontName, 18);
//	font_16_ = std::make_unique<TextObject>(renderer_, kFontName, 16);
//	font_14_ = std::make_unique<TextObject>(renderer_, kFontName, 14);
//
//	// Create the round manager
//	round_manager_ = std::make_unique<RoundManager>(my_aircraft_.get(), bullseye_.get(), hsd_distance_rings_.get(), bearing_pointer_.get());
//
//	return true;
//}


////////////////////////////////// Render Game Screen code
//	// Bearing to bullseye
//	std::string bearing_text = std::to_string(bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_->image_center_, bullseye_->image_center_));
//	// Add leading zeros if bearing less than 100 deg
//	std::string padded_bearing_text = std::string(3 - bearing_text.length(), '0') + bearing_text;
//	font_16_->Draw(renderer_, padded_bearing_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 34, kMfdScreenBottomInsideEdge - 20);
//
//	// Distance to bullseye
//	std::string distance_text = std::to_string(round_manager_->GetBullsDistance());
//	std::string padded_dist_text = std::string(3 - distance_text.length(), '0') + distance_text;
//	font_16_->Draw(renderer_, padded_dist_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 35, kMfdScreenBottomInsideEdge - 59);
//
//	// Increase and decrease range arrows
//		//Setting the actual draw color.
//	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
//
//	// Increase Range
//	SDL_RenderDrawLine(renderer_, 90, 395, 105, 380);
//	SDL_RenderDrawLine(renderer_, 105, 380, 120, 395);
//	SDL_RenderDrawLine(renderer_, 120, 395, 90, 395);
//
//	// Decrease Range
//	SDL_RenderDrawLine(renderer_, 90, 445, 120, 445);
//	SDL_RenderDrawLine(renderer_, 120, 445, 105, 460);
//	SDL_RenderDrawLine(renderer_, 105, 460, 90, 445);
//
//	// HSD Scale Range
//	//std::string hsd_scale_range_text = std::to_string(round_manager_->GetHSDRange());
//	std::string hsd_scale_range_text = std::to_string(hsd_range_[hsd_range_level_]);
//	font_16_->Draw(renderer_, hsd_scale_range_text, kMfdWhiteColour, kMfdScreenLeftInsideEdge + 12, kMfdScreenTopInsideEdge + 152);
//
//	// Display remaining guesses
//	auto guesses = std::to_string(round_manager_->GetRemaingGuesses());
//	font_16_->Draw(renderer_, "Guesses left " + guesses, kMfdGreenColour, 475, 280);
//
//	// Text for buttons
//	font_16_->Draw(renderer_, kExitButtonText, kMfdWhiteColour, 433, 795);
//	// if a round is in progress then don't display the setup button as we don't want to change the difficulty mid round
//	if (game_state == RoundState::kRoundStarting || game_state == RoundState::kRoundEnded) { font_16_->Draw(renderer_, kSetupButtonText, kMfdWhiteColour, 260, 795); }
//
//	// AWACS header
//	font_20_->DrawCenteredText(renderer_, "AWACS Call:", kMfdWhiteColour, kMfdPaddingTop - 150);
//
//	// This is the call that renders the AWCS call (constructed by RoundManager) to inform the user where the bogey is
//	// TODO: Method needs re-factoring
//	font_18_->DrawCenteredText(renderer_, round_manager_->AwacsCallString(), kMfdWhiteColour, kMfdPaddingTop - 100);
//
//	// Description of what to do
//	std::string difficulty_text1, difficulty_text2;
//	if (gameDifficulty == Difficulty::kAce && gameState == GameState::kRoundPlaying) {
//		difficulty_text1 = "Difficulty: ACE";
//		difficulty_text2 = "Click on HSD close to all groups of bogey's";
//	}
//	else if (gameDifficulty == Difficulty::kCadet && gameState == GameState::kRoundPlaying) {
//		difficulty_text1 = "Difficulty: CADET";
//		difficulty_text2 = "Click on HSD close to the bullseye";
//	}
//	else if (gameDifficulty == Difficulty::kRecruit && gameState == GameState::kRoundPlaying) {
//		difficulty_text1 = "Difficulty: RECRUIT";
//		difficulty_text2 = "Click on HSD in the direction of the bullseye";
//	}
//	else if (gameDifficulty == Difficulty::kRookie && gameState == GameState::kRoundPlaying) {
//		difficulty_text1 = "Difficulty: ROOKIE";
//		difficulty_text2 = "Click on HSD in the direction of the bogey from the bullseye";
//	}
//	else if (gameDifficulty == Difficulty::kVeteran && gameState == GameState::kRoundPlaying) {
//		difficulty_text1 = "Difficulty: VETERAN";
//		difficulty_text2 = "Click on HSD close to the bogey's";
//	}
//
//	font_14_->DrawCenteredText(renderer_, difficulty_text1, kMfdBlueColour, kMfdPaddingTop - 50);
//	font_14_->DrawCenteredText(renderer_, difficulty_text2, kMfdBlueColour, kMfdPaddingTop - 30);
//
//	// Using the roundState which is set in ResultManager and display the correct win symbol
//	switch (gameDifficulty) {
//		case Difficulty::kRecruit:
//			// TODO: re-factor this so that we're just getting a previously calculated and stored value rather than recalculating
//			user_bearing_guess = bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_->image_center_, mouse_click_position);
//
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc with the bullseye after a correct guess
//				correct_guess_arc_->DrawArc(renderer_, user_bearing_guess);  // need to know the user bearing guess
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc but keep going with the remaining guesses
//				wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
//			}
//			break;
//
//		case Difficulty::kCadet:
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc with the bullseye after a correct guess
//				correct_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				wrong_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc but keep going with the remaining guesses
//				wrong_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
//			}
//			break;
//
//		case Difficulty::kRookie:
//			// Determine the bearing of the actual bogey from the bullseye as well as the location the user clicked on
//			user_bearing_guess = bullseye_->Bearing_FromPoint1ToPoint2(bullseye_->image_center_, mouse_click_position);
//			bogey_bearing_from_bulleye = bullseye_->Bearing_FromPoint1ToPoint2(bullseye_->image_center_, bogeys[0]->image_center_);
//
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc from the bullseye to the bogey after a correct guess
//				correct_guess_arc_->DrawArc(renderer_, user_bearing_guess);  // need to know the user bearing guess
//				bullseye_->Draw(renderer_);
//				// bogeys[0]->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc from the bulls eye to the bogey after 3 guesses
//				wrong_guess_arc_->DrawArc(renderer_, bogey_bearing_from_bulleye);
//				bullseye_->Draw(renderer_);
//				// bogeys[0]->Draw(renderer_);
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc from the bulls eye to the clicked on point and keep going with the remaining guesses
//				wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
//			}
//			break;
//
//		case Difficulty::kVeteran:
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc with the bullseye after a correct guess
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc but keep going with the remaining guesses
//			}
//			break;
//
//		case Difficulty::kAce:
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc with the bullseye after a correct guess
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				game_state = RoundState::kRoundEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc but keep going with the remaining guesses
//			}
//			break;
//	}
//
//	// DEBUG - display all objects on the screen all the time if they are in range of the current HSD range setting
//	bogeys[0]->DrawBogey(renderer_, my_aircraft_, hsd_range_level_);
//	// bogeys[1]->DrawBogey(renderer_);
//	// bogeys[2]->DrawBogey(renderer_);
//	bullseye_->Draw(renderer_);
//
//	// Always call last so that it appears on top of everything else
//	//if (game_state == RoundState::kRoundEnded) {
//	//	// Delay at the start of each round to allow player to see results before new round
//	//	Sleep(1500);
//	//}