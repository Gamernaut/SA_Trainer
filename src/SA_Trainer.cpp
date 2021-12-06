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
#include <plog/Log.h>
#include <random>
#include "sa_trainer.h"
#include "main.h"
#include "image_object.h"
//#include "text_object.h"
//#include "round_manager.h"

using namespace cpv;

SA_Trainer::SA_Trainer() {
}


SA_Trainer::~SA_Trainer() {
}


bool SA_Trainer::LoadAndSetUpSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		PLOG_ERROR << "Error initializing SDL library";
		return false;
	}

	if (TTF_Init() != 0) {
		PLOG_ERROR << "Error initializing TTF library";
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
		PLOG_ERROR << "Error creating SDL window";
		return false;
	}
	PLOG_VERBOSE << "SDL window created";

	renderer_ = SDL_CreateRenderer(window_, -1, 0);

	if (!renderer_) {
		PLOG_ERROR << "Error creating SDL Renderer";
		return false;
	}
	PLOG_VERBOSE << "SDL Renderer created";

	font_ = TTF_OpenFont(kFontName, kFontSize1);
	if (!font_) {
		PLOG_ERROR << "Error opening font Renderer";
		return false;
	}
	PLOG_VERBOSE << "Font Renderer created";

	// Jan's suggested alternative random num generator https://en.cppreference.com/w/cpp/numeric/random
	//std::random_device rd;  //Will be used to obtain a seed for the random number engine
	//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	//std::uniform_int_distribution<> distrib();
	//std::cout << distrib(gen);

	// Set the random seed for this game - original method for now
	std::srand((unsigned int)std::time(NULL));

	is_game_running = true;

	return true;
}


void SA_Trainer::Initialise() {
	// Import and set up SDL and libraries
	PLOG_INFO << "SA_Trainer::Initialise called";

	if (!LoadAndSetUpSDL()) {
		PLOG_ERROR << "Error setting up SDL";
	}

	// Create the screens (HSD only in this version but maybe FCR in future versions
	start_screen_ = std::make_unique<StartScreen>(renderer_, 0, 180, kMfdImageHeight, kMfdImageWidth);
	start_screen_->Draw();
	SDL_RenderPresent(renderer_);

//	options_screen_ = std::make_unique<OptionsScreen>(renderer_, 0, 180, kMfdImageHeight, kMfdImageWidth);
	hsd_screen_ = std::make_unique<HSD>(renderer_, 0, 180 , kMfdImageHeight, kMfdImageWidth);
	// fcr_screen_ = std::make_unique<FCR>(0, 180, kMfdImageHeight, kMfdImageWidth);


	//if (!SetupLoadingScreen()) {
	//	PLOG_ERROR << "Error creating Loading screen";
	//}
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

	hsd_screen_->Draw();
	SDL_RenderPresent(renderer_);
}

void SA_Trainer::RenderLoadingScreen() {
	
	start_screen_->Draw();
	SDL_RenderPresent(renderer_);
}

//void SA_Trainer::RenderOptionsSceen() {
//	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
//	SDL_RenderClear(renderer_);
//
//	font_26_->DrawCenteredText(renderer_, "Choose the level of difficulty", kMfdWhiteColour, kMfdPaddingTop + 123);
//	font_16_->Draw(renderer_, "Recruit", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 200);
//	font_16_->Draw(renderer_, "Cadet", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 275);
//	font_16_->Draw(renderer_, "Rookie", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 355);
//	font_16_->Draw(renderer_, "Veteran", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 430);
//	font_16_->Draw(renderer_, "Ace", kMfdWhiteColour, kMfdPaddingLeft + 90, kMfdPaddingTop + 510);
//	font_16_->Draw(renderer_, "CANCEL", kMfdWhiteColour, 430, 795);
//	font_16_->Draw(renderer_, "SELECT", kMfdWhiteColour, 255, 795);
//	font_16_->DrawCenteredText(renderer_, "Click on a level to get a description.", kMfdWhiteColour, kMfdPaddingTop + 570);
//
//	if (gameDifficulty == Difficulty::kAce) {
//		font_18_->DrawCenteredText(renderer_, "Description for Ace level", kMfdWhiteColour, kMfdPaddingTop + 225);
//		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
//		font_16_->Draw(renderer_, "where you think the bogey's are, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
//		font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
//		font_16_->Draw(renderer_, "bearing and distance from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
//		font_16_->Draw(renderer_, "to each bogey counts.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
//		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
//		font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
//		font_16_->Draw(renderer_, "distance to the bogey's.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
//	}
//	else if (gameDifficulty == Difficulty::kCadet) {
//		font_18_->DrawCenteredText(renderer_, "Description for Cadet level", kMfdWhiteColour, kMfdPaddingTop + 225);
//		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
//		font_16_->Draw(renderer_, "where you think the bullseye is. Both", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
//		font_16_->Draw(renderer_, "bearing and distance count.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
//		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
//		font_16_->Draw(renderer_, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
//		font_16_->Draw(renderer_, "distance to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
//	}
//	else if (gameDifficulty == Difficulty::kRecruit) {
//		font_18_->DrawCenteredText(renderer_, "Description for Recruit level", kMfdWhiteColour, kMfdPaddingTop + 225);
//		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
//		font_16_->Draw(renderer_, "where you think the bullseye is,", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
//		font_16_->Draw(renderer_, "distance is NOT important.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
//		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
//		font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
//		font_16_->Draw(renderer_, "to the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
//	}
//	else if (gameDifficulty == Difficulty::kRookie) {
//		font_18_->DrawCenteredText(renderer_, "Description for Rookie level", kMfdWhiteColour, kMfdPaddingTop + 225);
//
//		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
//		font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
//		font_16_->Draw(renderer_, "where you think the bullseye is. Only ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
//		font_16_->Draw(renderer_, "bearing to the bogey from the bullseye", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
//		font_16_->Draw(renderer_, "counts.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
//		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
//		font_16_->Draw(renderer_, "Get within +/- 15 deg of the bearing to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
//		font_16_->Draw(renderer_, "the bogey from the bullseye.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
//	}
//	else if (gameDifficulty == Difficulty::kVeteran) {
//		font_18_->DrawCenteredText(renderer_, "Description for Veteran level", kMfdWhiteColour, kMfdPaddingTop + 225);
//		font_16_->Draw(renderer_, "Click on the HSD as close as you can to", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 260);
//		font_16_->Draw(renderer_, "where you think the bogey is, using", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 280);
//		font_16_->Draw(renderer_, "where you think the bullseye is. Both ", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 300);
//		font_16_->Draw(renderer_, "bearing and distance to the bogey", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 320);
//		font_16_->Draw(renderer_, "count.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 340);
//		font_16_->Draw(renderer_, "Objective", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 400);
//		font_16_->Draw(renderer_, "Get within +/- 15 deg and 20% of", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 420);
//		font_16_->Draw(renderer_, "distance to the bogey.", kMfdWhiteColour, kMfdPaddingLeft + 200, kMfdPaddingTop + 440);
//	}
//
//	mfd_frame_->Draw(renderer_);
//
//	SDL_RenderPresent(renderer_);
//}

void SA_Trainer::Render() {
	// basically check the game state and then render the appropriate view
	switch (game_state) {
	case GameState::kStartScreen:
		RenderLoadingScreen();
		break;
	//case GameState::kOptionsScreen:
	//	RenderOptionsSceen();
	//	break;
	case GameState::kRoundPlaying:
		RenderGameScreen();
		break;
	}
}

void SA_Trainer::ProcessInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			game_state = GameState::kRoundEnded;
			is_game_running = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				game_state = GameState::kRoundEnded;
				is_game_running = false;
				break;
			}

		case SDL_MOUSEBUTTONUP:
			//Get mouse position
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			std::cout << "Mouse position is x = " << mouseX << " and y = " << mouseY << std::endl;
			std::cout << "Start button x = " << kStartButtonLeftEdge << " x end = " << kStartButtonRightEdge << std::endl;
			std::cout << "Start button y = " << kStartButtonTopEdge << " y end = " << kStartButtonBottomEdge << std::endl;

			// Handle click inside MFD, if game running assume it's the user indicating where the bogey is
			if (mouseX >= kMfdScreenLeftInsideEdge && mouseX <= kMfdScreenRightInsideEdge && mouseY >= kMfdScreenTopInsideEdge && 
					mouseY <= kMfdScreenBottomInsideEdge && game_state == GameState::kRoundPlaying) {
				game_state = GameState::kRoundPlaying;
				mouse_click_position.x = mouseX;
				mouse_click_position.y = mouseY;
// 				round_manager_->CheckWinStatus(gameDifficulty, game_state, mouse_click_position, hsd_range_[hsd_range_level_]);
				break;
			}

			// Handle Start button on the start screen
			if (mouseX >= kStartButtonLeftEdge && mouseX <= kStartButtonRightEdge && mouseY >= kStartButtonTopEdge && mouseY <= kStartButtonBottomEdge) {
				if (game_state == GameState::kStartScreen) {
					game_state = GameState::kRoundPlaying;
					break;
				}
			}

			// Handle Setup/Select button
			if (mouseX >= kSetupButtonLeftEdge && mouseX <= kSetupButtonRightEdge && mouseY >= kSetupButtonTopEdge && mouseY <= kSetupButtonBottomEdge) {
				// Handle Setup button click
				if (game_state == GameState::kRoundPlaying) {
					tempDiff = gameDifficulty;	// Store the setting the user had when they enter the setup screen so if they cancel it can be restored
					temp_game_state = game_state;	// Store the game state so we can restore when we come out of the setup screen
					game_state = GameState::kOptionsScreen;
					break;
				}
				// Handle Select button press in setup screen
				if (game_state == GameState::kOptionsScreen) {
					game_state = GameState::kRoundPlaying;
					break;
				}
			}

			// Handle the Cancel/Exit button
			if (mouseX >= kExitButtonLeftEdge && mouseX <= kExitButtonRightEdge && mouseY >= kExitButtonTopEdge && mouseY <= kExitButtonBottomEdge) {
				// Handle the exit button on the main game screen
				if (game_state == GameState::kRoundPlaying) {
					std::cout << "Mouse is inside the Exit button" << std::endl;
					game_state = GameState::kRoundEnded;
					is_game_running = false;
					break;
				}
				// Handle the Cancel button in the setup screen
				if (game_state == GameState::kOptionsScreen) {
					game_state = GameState::kRoundPlaying; // This is probably what is causing the arc to appear when we come out of the setup (if state is kStarting)
					game_state = temp_game_state;
					gameDifficulty = tempDiff;		// restore the difficulty level to the one before they entered the setup screen
					break;
				}
			}

			// Handle increase HSD range button in playing screen
			if (mouseX >= kRecruitButtonLeftEdge && mouseX <= kRecruitButtonRightEdge && mouseY >= kRecruitButtonTopEdge && 
					mouseY <= kRecruitButtonBottomEdge && game_state == GameState::kRoundPlaying) {
				hsd_screen_->IncreaseRange();
				break;
			}

			// Handle decrease HSD range button in playing screen
			if (mouseX >= kCadetButtonLeftEdge && mouseX <= kCadetButtonRightEdge && mouseY >= kCadetButtonTopEdge && mouseY <= kCadetButtonBottomEdge && 
					game_state == GameState::kRoundPlaying) {
				hsd_screen_->DecreaseRange();
				break;
			}

			// Handle Recruit difficulty selection in setup screen
			if (mouseX >= kRecruitButtonLeftEdge && mouseX <= kRecruitButtonRightEdge && mouseY >= kRecruitButtonTopEdge && mouseY <= kRecruitButtonBottomEdge && 
					game_state == GameState::kOptionsScreen) {
				gameDifficulty = Difficulty::kRecruit;
				std::cout << "Difficulty changed to Recruit" << std::endl;
				break;
			}

			// Handle Cadet selection in setup screen
			if (mouseX >= kCadetButtonLeftEdge && mouseX <= kCadetButtonRightEdge && mouseY >= kCadetButtonTopEdge && mouseY <= kCadetButtonBottomEdge && 
					game_state == GameState::kOptionsScreen) {
				gameDifficulty = Difficulty::kCadet;
				std::cout << "Difficulty changed to Cadet" << std::endl;
				break;
			}

			// Handle Rookie selection in setup screen
			if (mouseX >= kRookieButtonLeftEdge && mouseX <= kRookieButtonRightEdge && mouseY >= kRookieButtonTopEdge && mouseY <= kRookieButtonBottomEdge && 
					game_state == GameState::kOptionsScreen) {
				gameDifficulty = Difficulty::kRookie;
				std::cout << "Difficulty changed to Rookie" << std::endl;
				break;
			}

			// Handle Veteran selection in setup screen
			if (mouseX >= kVeteranButtonLeftEdge && mouseX <= kVeteranButtonRightEdge && mouseY >= kVeteranButtonTopEdge && mouseY <= kVeteranButtonBottomEdge && 
					game_state == GameState::kOptionsScreen) {
				gameDifficulty = Difficulty::kVeteran;
				std::cout << "Difficulty changed to Veteran" << std::endl;
				break;
			}

			// Handle Ace selection in setup screen
			if (mouseX >= kAceButtonLeftEdge && mouseX <= kAceButtonRightEdge && mouseY >= kAceButtonTopEdge && mouseY <= kAceButtonBottomEdge && 
					game_state == GameState::kOptionsScreen) {
				gameDifficulty = Difficulty::kAce;
				std::cout << "Difficulty changed to Ace" << std::endl;
				break;
			}

		}
	}
}

void SA_Trainer::SetupRound() {
	game_state = GameState::kRoundStarting;

	// Create round manager object and setup round
//	round_manager_->StartRound(gameDifficulty, game_state, bogeys);
}

void SA_Trainer::Run() {


	while (is_game_running ) {
		// Delay at the start of each round to allow player to see results before new round
		Sleep(3000);
		// SetupRound();
		
		while (game_state != GameState::kRoundEnded) {
			// Limit speed to consistent frame rate. Not really needed in this application, but good practice to include it anyway.
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), milliseconds_previous_frame_ + kmilliseconds_per_frame));

			// Store the current frame time
			milliseconds_previous_frame_ = SDL_GetTicks();

			ProcessInput();
			Render();
		}
//		round_manager_->ResetRound();
	}
}