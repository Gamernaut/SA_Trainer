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
	hsd_distance_rings_ = std::make_unique<ImageObject>(renderer_, kHSD_DistRingsFileName, kHSDDepInactive.x , kHSDDepInactive.y);


	PLOG_VERBOSE << "HSD constructor -> creating aircraft datum";
	// create my aircraft
	my_aircraft_ = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kHSDDepInactive.x , kHSDDepInactive.y);


	PLOG_VERBOSE << "HSD constructor -> creating HSD bearing ring and pointer";
	// create Bearing ring image
	bearing_ring_ = std::make_unique<ImageObject>(renderer_, kBearingCircle, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);
	bearing_pointer_ = std::make_unique<ImageObject>(renderer_, kBearingPointer, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);
	// needs to be set from round manager
//	bearing_pointer_->RotateToFinalAngle(bullseye_->GetBearing());

	// Create the up and down arrows for setting the scale
	scale_up_arrow_ = std::make_unique<ImageObject>(renderer_, kIncScaleFileName, kHSDDepInactive.x, kHSDDepInactive.y);
	scale_down_arrow_ = std::make_unique<ImageObject>(renderer_, kDecScaleFileName, kHSDDepInactive.x, kHSDDepInactive.y);


	// Add On Screen Buttons
	exit_button = std::make_unique<OnSceenButton>(kOSB12LeftEdge, kOSB12TopEdge, kOSB12RightEdge, kOSB12BottomEdge, false, "OSB12", "EXIT");
	setup_button = std::make_unique<OnSceenButton>(kOSB14LeftEdge, kOSB14TopEdge, kOSB14RightEdge, kOSB14BottomEdge, false, "OSB14", "SETUP");
	inc_rng_button = std::make_unique<OnSceenButton>(kOSB20LeftEdge, kOSB20TopEdge, kOSB20RightEdge, kOSB20BottomEdge, false, "OSB20");
	dec_rng_button = std::make_unique<OnSceenButton>(kOSB19LeftEdge, kOSB19TopEdge, kOSB19RightEdge, kOSB19BottomEdge, false, "OSB19");
	dep_rng_button = std::make_unique<OnSceenButton>(kOSB1LeftEdge, kOSB1TopEdge, kOSB1RightEdge, kOSB1BottomEdge, false, "OSB1", "DEP");

	PLOG_VERBOSE << "HSD constructor -> creating fonts";
	font_20_ = std::make_unique<TextObject>(renderer_, kFontName, 20);
	font_18_ = std::make_unique<TextObject>(renderer_, kFontName, 18);
	font_16_ = std::make_unique<TextObject>(renderer_, kFontName, 16);
}

HSD::~HSD() {

}


void HSD::AddRandomBullsToHSD(std::unique_ptr<Bullseye>& bullseye) {
//	PLOG_VERBOSE << "HSD AddRandomBullsToHSD -> creating bullseye";
//	// Create bullseye
//	bullseye_ = std::make_unique<Bullseye>(renderer_, kBullsFileName, kHSDDepInactive.x , kHSDDepInactive.y);
////	bullseye_->SetVisibility(false);
//	bullseye_->RandomiseBearingAndDistance();
////	bullseye_->SetPosition({45 , 20});
}


void HSD::AddRandomBogeyToHSD(std::unique_ptr<Aircraft>& bogey) {

}

void HSD::AddAwacsCallToDisplay(std::string awacs_call) {

}

void HSD::SetCenteredState(bool new_state) {
	// Do I need to tie this into the display
	centered_ = new_state;
}

bool HSD::GetCenteredState(void) {
	return centered_;
}

double HSD::GetMilesPerPixel(void) {
	// Take the number of pixels between the center and the outer ring, about 305px, and divide by range in miles to get miles per pixel
	double current_hsd_range = static_cast<double>(GetHSDCurrentRange());
	double pixels_from_my_aircraft_to_outer_ring = static_cast<double>(305);
	return  (current_hsd_range / pixels_from_my_aircraft_to_outer_ring );
}

void HSD::IncreaseRange(void) {
	int range_size = HSD_ranges.size() - 1;

	if (range_level_ < range_size) {
		range_level_ += 1;
	}
	else {
		range_level_ = range_size;
	}
}

void HSD::DecreaseRange(void) {
	if (range_level_ > 0) {
		range_level_ -= 1;
	}
	else {
		range_level_ = 0;
	}
}

int HSD::GetHSDCurrentRange() {
	if (GetCenteredState()) {
		return HSD_centered_ranges[range_level_];
	}
	else {
		return HSD_ranges[range_level_];
	}
}

//std::unique_ptr<OnSceenButton> HSD::AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text) {
//	PLOG_VERBOSE << "HSD::AddObcButton called with 7 parameters";
//	return std::make_unique<OnSceenButton>(xPos, yPos, xPosEnd, yPosEnd, toggelable, button_name, onscreen_text);
//}
//
//std::unique_ptr<OnSceenButton> HSD::AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name) {
//	PLOG_VERBOSE << "HSD::AddObcButton called with 6 parameters";
//	return std::make_unique<OnSceenButton>(xPos, yPos, xPosEnd, yPosEnd, toggelable, button_name);
//}



//void HSD::Draw(SDL_Renderer* renderer, std::unique_ptr<Bullseye>& bullseye, std::unique_ptr<Aircraft>& bogey1, std::string const& bogey_1_awacs, std::unique_ptr<Aircraft>& bogey2, std::string bogey_2_awacs, std::unique_ptr<Aircraft>& bogey3, std::string bogey_3_awacs, int remaining_guesses) {
void HSD::Draw(SDL_Renderer * renderer, std::unique_ptr<Bullseye>&bullseye, std::unique_ptr<Aircraft>&bogey1, std::unique_ptr<Aircraft>&bogey2, std::unique_ptr<Aircraft>&bogey3, int remaining_guesses) {
	// This method separates the data from the visuals.
	PLOG_VERBOSE << "HSD::Draw with bulls and bogey info called";

	// 1 - clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw images on game screen, call them with those on the lowest layer first so they get written over
	bearing_ring_->Draw(renderer);
	bearing_pointer_->Draw(renderer);

	// HSD Scale Range
	scale_up_arrow_->DrawCenteredAt(renderer, 105, 385);
	scale_down_arrow_->DrawCenteredAt(renderer, 105, 455);
	std::string hsd_scale_range_text = std::to_string(GetHSDCurrentRange());
	font_16_->Draw(renderer, hsd_scale_range_text, kMfdWhiteColour, kMfdScreenLeftInsideEdge + 12, kMfdScreenTopInsideEdge + 152);


	// Text for buttons
	font_16_->Draw(renderer, kExitButtonText, kMfdWhiteColour, 433, 795);
	// if a round is in progress then don't display the setup button as we don't want to change the difficulty mid round
	// if (game_state == RoundState::kRoundStarting || game_state == RoundState::kGameEnded) { font_16_->Draw(renderer_, kSetupButtonText, kMfdWhiteColour, 260, 795); }
	font_16_->Draw(renderer, kSetupButtonText, kMfdWhiteColour, 260, 795);
	font_16_->Draw(renderer, kDepButtonText, kMfdWhiteColour, 183, 276);


	if (bullseye) {
		// display bulls distance
		std::string distance_text = std::to_string(bullseye->GetDistance());
		std::string padded_dist_text = std::string(3 - distance_text.length(), '0') + distance_text;
		font_16_->Draw(renderer, padded_dist_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 35, kMfdScreenBottomInsideEdge - 59);

		// Bearing to bullseye
		std::string bearing_text = std::to_string(bullseye->GetBearing());
		std::string padded_bearing_text = std::string(3 - bearing_text.length(), '0') + bearing_text; // Add leading zeros if bearing less than 100 deg
		font_16_->Draw(renderer, padded_bearing_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 34, kMfdScreenBottomInsideEdge - 20);
	}

	// Let the user know how many guesses they have left
	font_16_->Draw(renderer_, "Guesses left " + remaining_guesses, kMfdGreenColour, 475, 280);




	// Draw on screen buttons
	exit_button->DrawOutline(renderer);
	setup_button->DrawOutline(renderer);
	inc_rng_button->DrawOutline(renderer);
	dec_rng_button->DrawOutline(renderer);
	dep_rng_button->DrawOutline(renderer);

	// Text for the instruction box 
	// AWACS header
	font_20_->DrawCenteredText(renderer, "AWACS Call:", kMfdGreenColour, kMfdPaddingTop - 150);
	if (bogey1) {
		font_18_->DrawCenteredText(renderer_, bogey1->GetAwacsString(), kMfdWhiteColour, kMfdPaddingTop - 100);
	}
	if (bogey2) {
		font_18_->DrawCenteredText(renderer_, bogey2->GetAwacsString(), kMfdWhiteColour, kMfdPaddingTop - 80);
	}
	if (bogey3) {
		font_18_->DrawCenteredText(renderer_, bogey3->GetAwacsString(), kMfdWhiteColour, kMfdPaddingTop - 60);
	}

	// Adjust the position of these depending on if the HSD is centered or not and if the object is in range
	if (GetCenteredState()) {
		hsd_distance_rings_->DrawCenteredAt(renderer, kHSDDepActive.x, kHSDDepActive.y);
		// Offset image in y axis so it looks better lined up
		my_aircraft_->DrawCenteredAt(renderer, kHSDDepActive.x, kHSDDepActive.y + 15);
		// Draw the following if they are in range and their visibility is set to true
		int debug_current_range = GetHSDCurrentRange();
		if (bullseye && bullseye->GetDistance() <= debug_current_range) {
			// Need to scale the distance to match the HSD range esp. if the HSD range is much bigger than the distance to the bulls
			float scale = (static_cast<float>(bullseye->GetDistance() / static_cast<float>(GetHSDCurrentRange())));
			float scaled_dist_to_bulls = static_cast<float>(GetHSDCurrentRange()) * scale;
			Coordinate bulls_pos = endpoint_given_start_and_bearing(kHSDDepActive, bullseye->GetBearing(), 0, static_cast<int>(scaled_dist_to_bulls), GetMilesPerPixel());
			bullseye->DrawCenteredAt(renderer, bulls_pos.x, bulls_pos.y);
			// Code to draw bogey in testing mode
			if (bogey1 ) {
				int total_range = bullseye->GetDistance() + bogey1->GetDistanceFromBullseye();
				if (total_range <= debug_current_range) {
					bogey1->SetVisibility(true);
					bogey1->DrawBogey(renderer_, my_aircraft_, bulls_pos, GetMilesPerPixel());
				}
			}
		}
	}
	else {
		hsd_distance_rings_->DrawCenteredAt(renderer, kHSDDepInactive.x, kHSDDepInactive.y);
		// Offset image in y axis so it looks better lined up
		my_aircraft_->DrawCenteredAt(renderer_, kHSDDepInactive.x, kHSDDepInactive.y + 15);
		// Draw the following if they are in range and their visibility is set to true
		int debug_current_range = GetHSDCurrentRange();
		if (bullseye && bullseye->GetDistance() <= debug_current_range) {
			// Need to scale the distance to match the HSD range esp. if the HSD range is much bigger than the distance to the bulls
			float scale = (static_cast<float>(bullseye->GetDistance() / static_cast<float>(GetHSDCurrentRange())));
			float scaled_dist_to_bulls = static_cast<float>(GetHSDCurrentRange()) * scale;
			Coordinate bulls_pos = endpoint_given_start_and_bearing(kHSDDepInactive, bullseye->GetBearing(), 0, static_cast<int>(scaled_dist_to_bulls), GetMilesPerPixel());
			bullseye->DrawCenteredAt(renderer, bulls_pos.x, bulls_pos.y);
			// Code to draw bogey in testing mode
			if (bogey1) {
				int total_range = bullseye->GetDistance() + bogey1->GetDistanceFromBullseye();
				if (total_range <= debug_current_range) {
					bogey1->SetVisibility(true);
					bogey1->DrawBogey(renderer_, my_aircraft_, bulls_pos, GetMilesPerPixel());
				}
			}
		}
	}

	// Always draw frame last so it's on top of everything
	mfd_frame_->Draw(renderer);

	// Render screen
	SDL_RenderPresent(renderer);

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
//
//	// Create the pie slices to indicate a correct or incorrect guess
//	correct_guess_arc_ = std::make_unique<ImageObject>(renderer_, kGreenPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//	wrong_guess_arc_ = std::make_unique<ImageObject>(renderer_, kRedPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//
//	// Create the rectangles to indicate a correct or incorrect guess
//	correct_guess_rect_ = std::make_unique<ImageObject>(renderer_, kGreenRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//	wrong_guess_rect_ = std::make_unique<ImageObject>(renderer_, kRedRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
//
//	// Create the round manager
//	round_manager_ = std::make_unique<RoundManager>(my_aircraft_.get(), bullseye_.get(), hsd_distance_rings_.get(), bearing_pointer_.get());
//
//	return true;
//}


////////////////////////////////// Render Game Screen code

//

//

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
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kGameEnded;
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
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				wrong_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
//				bullseye_->Draw(renderer_);
//				game_state = RoundState::kGameEnded;
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
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc from the bulls eye to the bogey after 3 guesses
//				wrong_guess_arc_->DrawArc(renderer_, bogey_bearing_from_bulleye);
//				bullseye_->Draw(renderer_);
//				// bogeys[0]->Draw(renderer_);
//				game_state = RoundState::kGameEnded;
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
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundPlaying) {
//				// Display the red arc but keep going with the remaining guesses
//			}
//			break;
//
//		case Difficulty::kAce:
//			if (game_state == RoundState::kRoundWon) {
//				// Display the green arc with the bullseye after a correct guess
//				game_state = RoundState::kGameEnded;
//			}
//			else if (game_state == RoundState::kRoundFail) {
//				// Display the red arc with the bullseye after 3 guesses
//				game_state = RoundState::kGameEnded;
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
//	//if (game_state == RoundState::kGameEnded) {
//	//	// Delay at the start of each round to allow player to see results before new round
//	//	Sleep(1500);
//	//}