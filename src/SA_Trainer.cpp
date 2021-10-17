///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <windows.h>		// For sleep function
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SA_Trainer.h"
#include "Main.h"
#include "Bullseye.h"
#include "aircraft.h"
#include "ImageObject.h"
#include "TextObject.h"
#include "RoundManager.h"

using namespace cpv;

SA_Trainer::SA_Trainer() {
}

SA_Trainer::~SA_Trainer() {
}

bool SA_Trainer::LoadAndSetUpSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL library" << std::endl;
		return false;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Error initializing TTF library" << std::endl;
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	window_ = SDL_CreateWindow(
		"SA Trainer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		kWindowWidth,
		kWindowHeight,
		NULL
	);

	if (!window_) {
		std::cerr << "Error creating SDL window" << std::endl;
		return false;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, 0);

	if (!renderer_) {
		std::cerr << "Error creating SDL Renderer" << std::endl;
		return false;
	}

	font_ = TTF_OpenFont(kFontName, kFontSize1);
	if (!font_) {
		std::cerr << "Error opening font Renderer" << std::endl;
		return false;
	}

	// Set the random seed for this game
	std::srand((unsigned int)std::time(NULL));

	is_game_running = true;

	return true;
}

bool SA_Trainer::SetupLoadingScreen() {
	// Allocate on the heap not the stack or when the function ends the object is destroyed and it looses it's link to the texture even though the object is copied into the vector the texture is lost.
	// 
	ImageObject* loadingScreenTitle = new ImageObject(renderer_, kGameTitleFilename, (kWindowWidth / 2) - (kGameTitleWidth / 2), (kMfdPaddingTop / 2) - (kGameTitleHeight / 2));
	loading_screen_image_list_.push_back(loadingScreenTitle);

	ImageObject* mfdSurround = new ImageObject(renderer_, kGameStartMenuFileName, kMfdPaddingLeft, kMfdPaddingTop);
	loading_screen_image_list_.push_back(mfdSurround);
	// 
	// 
	// 
	//std::unique_ptr<ImageObject> loadingScreenTitle = std::make_unique<ImageObject>(renderer_, kGameTitleFilename, (kWindowWidth / 2) - (kGameTitleWidth / 2), (kMfdPaddingTop / 2) - (kGameTitleHeight / 2));
	//loading_screen_image_list_.push_back(loadingScreenTitle);

	//std::unique_ptr<ImageObject> mfdSurround = std::make_unique<ImageObject>(renderer_, kGameStartMenuFileName, kMfdPaddingLeft, kMfdPaddingTop);
	//loading_screen_image_list_.push_back(mfdSurround);

	return true;
}

bool SA_Trainer::SetupGameScreen() {
	// create distance rings
	hsd_distance_rings_ = std::make_unique<ImageObject>(renderer_, kDistRingsFileName, kMFDCenter.x - (kDistRingsImageWidth / 2), (kMFDCenter.y - (kDistRingsImageHeight / 2)) + kDepOffset);

	// create Bearing ring image
	bearing_ring_ = std::make_unique<ImageObject>(renderer_, kBearingCircle, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);
	bearing_pointer_ = std::make_unique<ImageObject>(renderer_, kBearingPointer, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 85);

	// create my aircraft
	my_aircraft_ = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), (kMFDCenter.y - 5) + kDepOffset);

	// create 3 bogey's even if we don't use the all. Which are used are decided by the RoundManager
	//bogeys[0] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
	//bogeys[1] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
	//bogeys[2] = std::make_unique<Aircraft>(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
	bogeys[0] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
	bogeys[1] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);
	bogeys[2] = new Aircraft(renderer_, kAircraftFileName, kMFDCenter.x - (kAircraftImageWidth / 2), kMFDCenter.y - 5);

	// Create bullseye
	bullseye_ = std::make_unique<Bullseye>(renderer_, kBullsFileName, 359 - (kBullsImageWidth / 2), 750 - (kBullsImageHeight / 2));

	// create MFD background
	mfd_frame_ = std::make_unique<ImageObject>(renderer_, kMfdFileName, kMfdPaddingLeft, kMfdPaddingTop);

	// Create the pie slices to indicate a correct or incorrect guess
	correct_guess_arc_ = std::make_unique<ImageObject>(renderer_, kGreenPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
	wrong_guess_arc_ = std::make_unique<ImageObject>(renderer_, kRedPieSlice, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);

	// Create the rectangles to indicate a correct or incorrect guess
	correct_guess_rect_ = std::make_unique<ImageObject>(renderer_, kGreenRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);
	wrong_guess_rect_ = std::make_unique<ImageObject>(renderer_, kRedRectangle, my_aircraft_->image_center_.x, my_aircraft_->image_center_.y);

	// Create fonts in 22 and 16 point sizes
	font_26_ = std::make_unique<TextObject>(renderer_, kFontName, 26);
	font_24_ = std::make_unique<TextObject>(renderer_, kFontName, 24);
	font_22_ = std::make_unique<TextObject>(renderer_, kFontName, 22);
	font_20_ = std::make_unique<TextObject>(renderer_, kFontName, 20);
	font_18_ = std::make_unique<TextObject>(renderer_, kFontName, 18);
	font_16_ = std::make_unique<TextObject>(renderer_, kFontName, 16);
	font_14_ = std::make_unique<TextObject>(renderer_, kFontName, 14);

	// Create the round manager
	round_manager_ = std::make_unique<RoundManager>(my_aircraft_.get(), bullseye_.get(), hsd_distance_rings_.get(), bearing_pointer_.get());

	return true;
}

void SA_Trainer::Initialise() {
	// 1 - Import and set up SDl and libraries

	if (!LoadAndSetUpSDL()) {
		std::cerr << "Error setting up SDL" << std::endl;
	}

	// 2 - create the MFD objects (HSD only in this version but maybe FCR in future versions
	// 3 - put game in start screen mode

	if (!SetupLoadingScreen()) {
		std::cerr << "Error creating Loading screen" << std::endl;
	}

	if (!SetupGameScreen()) {
		std::cerr << "Error creating Game screen" << std::endl;
	}
}

void SA_Trainer::CloseDown() {
	loading_screen_image_list_.clear();
	options_screen_image_list_.clear();
	TTF_CloseFont(font_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_Quit();
	SDL_Quit();
}

void SA_Trainer::RenderGameScreen() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	// Draw images on game screen, call them with those on the lowest layer first so they get written over
	hsd_distance_rings_->Draw(renderer_);
	bearing_ring_->Draw(renderer_);
	bearing_pointer_->Draw(renderer_);
	my_aircraft_->Draw(renderer_);

	// Bearing to bullseye
	std::string bearing_text = std::to_string(bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_->image_center_, bullseye_->image_center_));
	// Add leading zeros if bearing less than 100 deg
	std::string padded_bearing_text = std::string(3 - bearing_text.length(), '0') + bearing_text;
	font_16_->Draw(renderer_, padded_bearing_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 34, kMfdScreenBottomInsideEdge - 20);

	// Distance to bullseye
	std::string distance_text = std::to_string(round_manager_->GetBullsDistance());
	std::string padded_dist_text = std::string(3 - distance_text.length(), '0') + distance_text;
	font_16_->Draw(renderer_, padded_dist_text, kMfdBlueColour, kMfdScreenLeftInsideEdge + 35, kMfdScreenBottomInsideEdge - 59);

	// Increase and decrease range arrows
		//Setting the actual draw color.
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

	// Increase Range
	SDL_RenderDrawLine(renderer_, 90, 395, 105, 380);
	SDL_RenderDrawLine(renderer_, 105, 380, 120, 395);
	SDL_RenderDrawLine(renderer_, 120, 395, 90, 395);

	// Decrease Range
	SDL_RenderDrawLine(renderer_, 90, 445, 120, 445);
	SDL_RenderDrawLine(renderer_, 120, 445, 105, 460);
	SDL_RenderDrawLine(renderer_, 105, 460, 90, 445);

	// HSD Scale Range
	//std::string hsd_scale_range_text = std::to_string(round_manager_->GetHSDRange());
	std::string hsd_scale_range_text = std::to_string(hsd_range_[hsd_range_level_]);
	font_18_->Draw(renderer_, hsd_scale_range_text, kMfdWhiteColour, kMfdScreenLeftInsideEdge + 5, kMfdScreenTopInsideEdge + 152);

	// Display remaining guesses
	auto guesses = std::to_string(round_manager_->GetRemaingGuesses());
	font_16_->Draw(renderer_, "Guesses left " + guesses, kMfdGreenColour, 475, 280);

	// Text for buttons
	font_16_->Draw(renderer_, kExitButtonText, kMfdWhiteColour, 433, 795);
	// if a round is in progress then don't display the setup button as we don't want to change the difficulty mid round
	if (roundstate == RoundState::kRoundStarting || roundstate == RoundState::kEnded) { font_16_->Draw(renderer_, kSetupButtonText, kMfdWhiteColour, 260, 795); }

	// AWACS header
	font_20_->DrawCenteredText(renderer_, "AWACS Call:", kMfdWhiteColour, kMfdPaddingTop - 150);

	// AWACS call text
	std::string call_text = "Hostile group bulls 230 for 20, Angels 20, tracking South West";
	font_18_->DrawCenteredText(renderer_, call_text, kMfdWhiteColour, kMfdPaddingTop - 100);

	// Description of what to do
	std::string difficulty_text1, difficulty_text2;
	if (gameDifficulty == Difficulty::kAce && gameState == GameState::kPlaying) {
		difficulty_text1 = "Difficulty: ACE";
		difficulty_text2 = "Click on HSD close to all groups of bogey's";
	}
	else if (gameDifficulty == Difficulty::kCadet && gameState == GameState::kPlaying) {
		difficulty_text1 = "Difficulty: CADET";
		difficulty_text2 = "Click on HSD close to the bullseye";
	}
	else if (gameDifficulty == Difficulty::kRecruit && gameState == GameState::kPlaying) {
		difficulty_text1 = "Difficulty: RECRUIT";
		difficulty_text2 = "Click on HSD in the direction of the bullseye";
	}
	else if (gameDifficulty == Difficulty::kRookie && gameState == GameState::kPlaying) {
		difficulty_text1 = "Difficulty: ROOKIE";
		difficulty_text2 = "Click on HSD in the direction of the bogey from the bullseye";
	}
	else if (gameDifficulty == Difficulty::kVeteran && gameState == GameState::kPlaying) {
		difficulty_text1 = "Difficulty: VETERAN";
		difficulty_text2 = "Click on HSD close to the bogey's";
	}

	font_14_->DrawCenteredText(renderer_, difficulty_text1, kMfdBlueColour, kMfdPaddingTop - 50);
	font_14_->DrawCenteredText(renderer_, difficulty_text2, kMfdBlueColour, kMfdPaddingTop - 30);

	// TODO: refactor this so that we're just getting a previously calculated and stored value rather than recalculating
	user_bearing_guess = bullseye_->Bearing_FromPoint1ToPoint2(my_aircraft_->image_center_, mouse_click_position);

	// Using the roundState which is set in ResultManager and display the correct win symbology
	switch (gameDifficulty) {
	case Difficulty::kRecruit:
		if (roundstate == RoundState::kWon) {
			// Display the green arc with the bullseye after a correct guess
			correct_guess_arc_->DrawArc(renderer_, user_bearing_guess);  // need to know the user bearing guess
			bullseye_->Draw(renderer_);
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kFail) {
			// Display the red arc with the bullseye after 3 guesses
			wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
			bullseye_->Draw(renderer_);
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kPlaying) {
			// Display the red arc but keep going with the remaining guesses
			wrong_guess_arc_->DrawArc(renderer_, user_bearing_guess);
		}
		break;

	case Difficulty::kCadet:
		if (roundstate == RoundState::kWon) {
			// Display the green arc with the bullseye after a correct guess
			correct_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
			bullseye_->Draw(renderer_);
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kFail) {
			// Display the red arc with the bullseye after 3 guesses
			wrong_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
			bullseye_->Draw(renderer_);
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kPlaying) {
			// Display the red arc but keep going with the remaining guesses
			wrong_guess_rect_->DrawCenteredAt(renderer_, mouse_click_position);
		}
		break;

	case Difficulty::kRookie:
		if (roundstate == RoundState::kWon) {
			// Display the green arc with the bullseye after a correct guess
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kFail) {
			// Display the red arc with the bullseye after 3 guesses
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kPlaying) {
			// Display the red arc but keep going with the remaining guesses
		}
		break;

	case Difficulty::kVeteran:
		if (roundstate == RoundState::kWon) {
			// Display the green arc with the bullseye after a correct guess
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kFail) {
			// Display the red arc with the bullseye after 3 guesses
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kPlaying) {
			// Display the red arc but keep going with the remaining guesses
		}
		break;

	case Difficulty::kAce:
		if (roundstate == RoundState::kWon) {
			// Display the green arc with the bullseye after a correct guess
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kFail) {
			// Display the red arc with the bullseye after 3 guesses
			roundstate = RoundState::kEnded;
		}
		else if (roundstate == RoundState::kPlaying) {
			// Display the red arc but keep going with the remaining guesses
		}
		break;
	}

	// Always call last so that it appears on top of everything else
	//if (roundstate == RoundState::kEnded) {
	//	// Delay at the start of each round to allow player to see results before new round
	//	Sleep(1500);
	//}
	mfd_frame_->Draw(renderer_);
	SDL_RenderPresent(renderer_);
}

void SA_Trainer::RenderLoadingScreen() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	for (std::size_t i = 0; i < loading_screen_image_list_.size(); ++i) {
		loading_screen_image_list_[i]->Draw(renderer_);
	}

	SDL_RenderPresent(renderer_);
}

void SA_Trainer::RenderOptionsSceen() {
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);

	font_26_->DrawCenteredText(renderer_, "Choose the level of difficulty", kMfdWhiteColour, kMfdPaddingTop + 123);
	font_16_->Draw(renderer_, "Recruit", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 200);
	font_16_->Draw(renderer_, "Cadet", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 275);
	font_16_->Draw(renderer_, "Rookie", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 355);
	font_16_->Draw(renderer_, "Veteran", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 430);
	font_16_->Draw(renderer_, "Ace", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 510);
	font_16_->Draw(renderer_, "CANCEL", kMfdWhiteColour, 430, 795);
	font_16_->Draw(renderer_, "SELECT", kMfdWhiteColour, 255, 795);
	font_16_->DrawCenteredText(renderer_, "Click on a level to get a description.", kMfdWhiteColour, kMfdPaddingTop + 570);

	if (gameDifficulty == Difficulty::kAce) {
		font_18_->DrawCenteredText(renderer_, "Description for Ace level", kMfdWhiteColour, kMfdPaddingTop + 225);
		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
		font_16_->Draw(renderer_, "where you think the bogey's are, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
		font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
		font_16_->Draw(renderer_, "bearing and distance from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
		font_16_->Draw(renderer_, "to each bogey counts.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
		font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
		font_16_->Draw(renderer_, "distance to the bogey's.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
	}
	else if (gameDifficulty == Difficulty::kCadet) {
		font_18_->DrawCenteredText(renderer_, "Description for Cadet level", kMfdWhiteColour, kMfdPaddingTop + 225);
		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
		font_16_->Draw(renderer_, "where you think the bullseye is. Both", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
		font_16_->Draw(renderer_, "bearing and distance count.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
		font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
		font_16_->Draw(renderer_, "distance to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
	}
	else if (gameDifficulty == Difficulty::kRecruit) {
		font_18_->DrawCenteredText(renderer_, "Description for Recruit level", kMfdWhiteColour, kMfdPaddingTop + 225);
		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
		font_16_->Draw(renderer_, "where you think the bullseye is,", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
		font_16_->Draw(renderer_, "distance is NOT important.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
		font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
		font_16_->Draw(renderer_, "to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
	}
	else if (gameDifficulty == Difficulty::kRookie) {
		font_18_->DrawCenteredText(renderer_, "Description for Rookie level", kMfdWhiteColour, kMfdPaddingTop + 225);

		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
		font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
		font_16_->Draw(renderer_, "where you think the bullseye is. Only ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
		font_16_->Draw(renderer_, "bearing to the bogey from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
		font_16_->Draw(renderer_, "counts.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
		font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
		font_16_->Draw(renderer_, "the bogey from the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
	}
	else if (gameDifficulty == Difficulty::kVeteran) {
		font_18_->DrawCenteredText(renderer_, "Description for Veteran level", kMfdWhiteColour, kMfdPaddingTop + 225);
		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
		font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
		font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
		font_16_->Draw(renderer_, "bearing and distance to the bogey", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
		font_16_->Draw(renderer_, "count.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
		font_16_->Draw(renderer_, "Get within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
		font_16_->Draw(renderer_, "distance to the bogey.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
	}

	mfd_frame_->Draw(renderer_);

	SDL_RenderPresent(renderer_);
}

void SA_Trainer::Render() {
	// basically check the game state and then render the appropriate view
	switch (gameState) {
	case GameState::kMenu:
		RenderLoadingScreen();
		break;
	case GameState::kSetup:
		RenderOptionsSceen();
		break;
	case GameState::kPlaying:
		RenderGameScreen();
		break;
	}
}

void SA_Trainer::ProcessInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			roundstate = RoundState::kEnded;
			is_game_running = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				roundstate = RoundState::kEnded;
				is_game_running = false;
				break;
			}

		case SDL_MOUSEBUTTONUP:
			//Get mouse position
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			std::cout << "Mouse position is x = " << mouseX << " and y = " << mouseY << std::endl;

			// Handle click inside MFD, if game running assume it's the user indicating where the bogey is
			if (mouseX >= kMfdScreenLeftInsideEdge && mouseX <= kMfdScreenRightInsideEdge && mouseY >= kMfdScreenTopInsideEdge && mouseY <= kMfdScreenBottomInsideEdge && gameState == GameState::kPlaying) {
				roundstate = RoundState::kPlaying;
				mouse_click_position.x = mouseX;
				mouse_click_position.y = mouseY;
				round_manager_->CheckWinStatus(gameDifficulty, roundstate, mouse_click_position, hsd_range_[hsd_range_level_]);
				break;
			}

			// Handle Start button on main screen
			if (mouseX >= kStartButtonLeftEdge && mouseX <= kStartButtonRightEdge && mouseY >= kStartButtonTopEdge && mouseY <= kStartButtonBottomEdge) {
				if (gameState == GameState::kMenu) {
					gameState = GameState::kPlaying;
					break;
				}
			}

			// Handle Setup/Select button
			if (mouseX >= kSetupButtonLeftEdge && mouseX <= kSetupButtonRightEdge && mouseY >= kSetupButtonTopEdge && mouseY <= kSetupButtonBottomEdge) {
				// Handle Setup button click
				if (gameState == GameState::kPlaying) {
					tempDiff = gameDifficulty;	// Store the setting the user had when they enter the setup screen so if they cancel it can be restored
					temproundstate = roundstate;	// Store the game state so we can restore when we come out of the setup screen
					gameState = GameState::kSetup;
					break;
				}
				// Handle Select button press in setup screen
				if (gameState == GameState::kSetup) {
					gameState = GameState::kPlaying;
					break;
				}
			}

			// Handle the Cancel/Exit button
			if (mouseX >= kExitButtonLeftEdge && mouseX <= kExitButtonRightEdge && mouseY >= kExitButtonTopEdge && mouseY <= kExitButtonBottomEdge) {
				// Handle the exit button on the main game screen
				if (gameState == GameState::kPlaying) {
					std::cout << "Mouse is inside the Exit button" << std::endl;
					roundstate = RoundState::kEnded;
					is_game_running = false;
					break;
				}
				// Handle the Cancel button in the setup screen
				if (gameState == GameState::kSetup) {
					gameState = GameState::kPlaying; // This is probably what is causing the arc to appear when we come out of the setup (if state is kStarting)
					roundstate = temproundstate;
					gameDifficulty = tempDiff;		// restore the difficulty level to the one before they entered the setup screen
					break;
				}
			}

			// Handle inc HSD range button in playing screen
			if (mouseX >= kRecruitButtonLeftEdge && mouseX <= kRecruitButtonRightEdge && mouseY >= kRecruitButtonTopEdge && mouseY <= kRecruitButtonBottomEdge && gameState == GameState::kPlaying) {
				if (hsd_range_level_ < 5) {
					hsd_range_level_ += 1;
				}
				std::cout << "Increase HSD range to " << hsd_range_[hsd_range_level_] << std::endl;
				break;
			}

			// Handle dec HSD range button in playing screen
			if (mouseX >= kCadetButtonLeftEdge && mouseX <= kCadetButtonRightEdge && mouseY >= kCadetButtonTopEdge && mouseY <= kCadetButtonBottomEdge && gameState == GameState::kPlaying) {
				if (hsd_range_level_ != 0) {
					hsd_range_level_ -= 1;
				}
				std::cout << "Decrease HSD range to " << hsd_range_[hsd_range_level_] << std::endl;
				break;
			}

			// Handle Recruit difficulty selection in setup screen
			if (mouseX >= kRecruitButtonLeftEdge && mouseX <= kRecruitButtonRightEdge && mouseY >= kRecruitButtonTopEdge && mouseY <= kRecruitButtonBottomEdge && gameState == GameState::kSetup) {
				gameDifficulty = Difficulty::kRecruit;
				std::cout << "Difficulty changed to Recruit" << std::endl;
				break;
			}

			// Handle Cadet selection in setup screen
			if (mouseX >= kCadetButtonLeftEdge && mouseX <= kCadetButtonRightEdge && mouseY >= kCadetButtonTopEdge && mouseY <= kCadetButtonBottomEdge && gameState == GameState::kSetup) {
				gameDifficulty = Difficulty::kCadet;
				std::cout << "Difficulty changed to Cadet" << std::endl;
				break;
			}

			// Handle Rookie selection in setup screen
			if (mouseX >= kRookieButtonLeftEdge && mouseX <= kRookieButtonRightEdge && mouseY >= kRookieButtonTopEdge && mouseY <= kRookieButtonBottomEdge && gameState == GameState::kSetup) {
				gameDifficulty = Difficulty::kRookie;
				std::cout << "Difficulty changed to Rookie" << std::endl;
				break;
			}

			// Handle Veteran selection in setup screen
			if (mouseX >= kVeteranButtonLeftEdge && mouseX <= kVeteranButtonRightEdge && mouseY >= kVeteranButtonTopEdge && mouseY <= kVeteranButtonBottomEdge && gameState == GameState::kSetup) {
				gameDifficulty = Difficulty::kVeteran;
				std::cout << "Difficulty changed to Veteran" << std::endl;
				break;
			}

			// Handle Ace selection in setup screen
			if (mouseX >= kAceButtonLeftEdge && mouseX <= kAceButtonRightEdge && mouseY >= kAceButtonTopEdge && mouseY <= kAceButtonBottomEdge && gameState == GameState::kSetup) {
				gameDifficulty = Difficulty::kAce;
				std::cout << "Difficulty changed to Ace" << std::endl;
				break;
			}

		}
	}
}

void SA_Trainer::SetupRound() {
	roundstate = RoundState::kRoundStarting;

	// Create round manager object and setup round
	round_manager_->StartRound(gameDifficulty, roundstate, bogeys);
}

void SA_Trainer::Run() {


	while (is_game_running ) {
		// Delay at the start of each round to allow player to see results before new round
		Sleep(1500);
		SetupRound();
		
		while (roundstate != RoundState::kEnded) {
			// Limit speed to consistent frame rate. Not really needed in this app, but good practice to include it anyway.
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), milliseconds_previous_frame_ + kmilliseconds_per_frame));

			// Store the current frame time
			milliseconds_previous_frame_ = SDL_GetTicks();

			ProcessInput();
			Render();
		}
		round_manager_->ResetRound();
	}
}