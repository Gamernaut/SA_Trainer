///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>		// For sleep function
#include "sa_trainer.h"


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

	// Create the screens (Start screen, Options and main HSD, the only one in this version but have FCR in future versions)
	start_screen_ = std::make_unique<StartScreen>(renderer_, 0, 180, kMfdImageHeight, kMfdImageWidth);
	start_screen_->Draw();
	SDL_RenderPresent(renderer_);

	options_screen_ = std::make_unique<OptionsScreen>(renderer_, 0, 180, kMfdImageHeight, kMfdImageWidth);
	//hsd_screen_ = std::make_unique<HSD>(renderer_, 0, 180, kMfdImageHeight, kMfdImageWidth);
	// fcr_screen_ = std::make_unique<FCR>(0, 180, kMfdImageHeight, kMfdImageWidth);
	round_manager_ = std::make_unique<RoundManager>(renderer_);
}


void SA_Trainer::CloseDown() {
	TTF_CloseFont(font_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_Quit();
	SDL_Quit();
}


void SA_Trainer::RenderGameScreen() {

	round_manager_->Draw(renderer_, gameDifficulty, game_state);
	SDL_RenderPresent(renderer_);
}


void SA_Trainer::RenderStartScreen() {

	start_screen_->Draw();
	SDL_RenderPresent(renderer_);
}


void SA_Trainer::RenderOptionsSceen() {

	options_screen_->Draw(logging_level);

	if (gameDifficulty == Difficulty::kRecruit) {
		options_screen_->DrawRecruitText();
	} else 	if (gameDifficulty == Difficulty::kCadet) {
		options_screen_->DrawCadetText();
	}
	else	if (gameDifficulty == Difficulty::kRookie) {
		options_screen_->DrawRookieText();
	}
	else	if (gameDifficulty == Difficulty::kVeteran) {
		options_screen_->DrawVeteranText();
	}
	else	if (gameDifficulty == Difficulty::kAce) {
		options_screen_->DrawAceText();
	}
	else {

	}

	SDL_RenderPresent(renderer_);
}


void SA_Trainer::Render() {
	// basically check the game state and then render the appropriate view
	switch (game_state) {
	case GameState::kStartScreen:
		RenderStartScreen();
		break;
	case GameState::kOptionsScreen:
		RenderOptionsSceen();
		break;
	case GameState::kRoundWon:
		RenderGameScreen();
		break;
	case GameState::kRoundFail:
		RenderGameScreen();
		break;
	case GameState::kRoundPlaying:
		RenderGameScreen();
		break;
	case GameState::kNewRound:
		RenderGameScreen();
		break;
	}
}


void SA_Trainer::ProcessInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			game_state = GameState::kGameEnded;
			is_game_running = false;
			PLOG_INFO << "Close widget clicked -> game state set to kGameEnded";
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				game_state = GameState::kGameEnded;
				is_game_running = false;
				PLOG_INFO << "ESC key pressed -> game state set to kGameEnded";
				break;
			}

		case SDL_MOUSEBUTTONUP:
			//Get mouse position
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			// std::cout << "Mouse position is x = " << mouseX << " and y = " << mouseY << std::endl;

			// Handle clicks whilst on the start screen. Can only transition to the Main screen from here through OSB 13
			if (game_state == GameState::kStartScreen) {
				if (mouseX >= kOSB13LeftEdge && mouseX <= kOSB13RightEdge && mouseY >= kOSB13TopEdge && mouseY <= kOSB13BottomEdge) {
					game_state = GameState::kNewRound;
					PLOG_INFO << "Start screen -> Start button clicked";
					break;
				}
			}

			// Handle clicks when a new round has just begun. User can enter Options Screen from this state only. 
			// Once they make their first guess they cannot change their settings
			if (game_state == GameState::kNewRound) {
				// Handle Setup button press (should not be active when round is being played)
				if (mouseX >= kOSB14LeftEdge && mouseX <= kOSB14RightEdge && mouseY >= kOSB14TopEdge && mouseY <= kOSB14BottomEdge) {
					tempDiff = gameDifficulty;	// Store the setting the user had when they enter the setup screen so if they cancel it can be restored
					temp_game_state = game_state;	// Store the game state so we can restore when we come out of the setup screen if they cancel
					game_state = GameState::kOptionsScreen;
					PLOG_INFO << "Main screen -> Setup button clicked, saving game difficulty and game state";
					break;
				} 
				// Exit if OSB 12
				else if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					game_state = GameState::kGameEnded;
					is_game_running = false;
					PLOG_INFO << "Main screen -> Exit button clicked";
					break;
				}

				/////////////////////////////////////////////////////////////////////
				// 
				//	These 3 are repeated below in the round playing bit as well
				// 
				// ////////////////////////////////////////////////////////////////
				
				// Handle DEP button press, toggle between centered and not centered
				if (mouseX >= kOSB1LeftEdge && mouseX <= kOSB1RightEdge && mouseY >= kOSB1TopEdge && mouseY <= kOSB1BottomEdge) {
					if (round_manager_->hsd_screen_->GetCenteredState()) {
						round_manager_->hsd_screen_->SetCenteredState(false);
						PLOG_INFO << "HSD DEP button press -> HSD centered state set to false";
						break;
					}
					else {
						round_manager_->hsd_screen_->SetCenteredState(true);
						PLOG_INFO << "HSD DEP button press -> HSD state changed to centered";
					}
				}
				// Handle Increase Range button press
				if (mouseX >= kOSB20LeftEdge && mouseX <= kOSB20RightEdge && mouseY >= kOSB20TopEdge && mouseY <= kOSB20BottomEdge) {
					round_manager_->hsd_screen_->IncreaseRange();
					PLOG_INFO << "HSD increase range button pressed";
					break;
				}

				// Handle Decrease Range button press
				if (mouseX >= kOSB19LeftEdge && mouseX <= kOSB19RightEdge && mouseY >= kOSB19TopEdge && mouseY <= kOSB19BottomEdge) {
					round_manager_->hsd_screen_->DecreaseRange();
					PLOG_INFO << "HSD decrease range button pressed";
					break;
				}
			}

			// Handle clicks in the options screen, can set the difficulty and logging level here
			if (game_state == GameState::kOptionsScreen) {

				// Set logging level to High
				if (mouseX >= kOSB7LeftEdge && mouseX <= kOSB7RightEdge && mouseY >= kOSB7TopEdge && mouseY <= kOSB7BottomEdge) {
					logging_level = 1;
					plog::get()->setMaxSeverity(plog::verbose);
					PLOG_INFO << "Logging level changed to High";
					break;
				}

				// Set logging level to Medium
				if (mouseX >= kOSB8LeftEdge && mouseX <= kOSB8RightEdge && mouseY >= kOSB8TopEdge && mouseY <= kOSB8BottomEdge) {
					logging_level = 2;
					plog::get()->setMaxSeverity(plog::info);
					PLOG_INFO << "Logging level changed to Medium";
					break;
				}

				// Set logging level to Low
				if (mouseX >= kOSB9LeftEdge && mouseX <= kOSB9RightEdge && mouseY >= kOSB9TopEdge && mouseY <= kOSB9BottomEdge) {
					logging_level = 3;
					plog::get()->setMaxSeverity(plog::warning);
					PLOG_INFO << "Logging level changed to Low";
					break;
				}

				// Handle the Cancel button and restore previous difficulty as this was updated in real time to match the users clicks in the options screen
				if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					// Restore the difficulty level to the one before the user entered the setup screen
					gameDifficulty = tempDiff;
					// Reset the game mode to NewRound from OptionsScreen
					game_state = GameState::kNewRound;
					PLOG_INFO << "Options screen Cancel button pressed -> restoring previous game state";
					// As neither the game state nor the logging level are updated "real time" in the options screen we do not need to restore them
					break;
				}

				// Handle the select button (set the selected options as the current states)
				if (mouseX >= kOSB14LeftEdge && mouseX <= kOSB14RightEdge && mouseY >= kOSB14TopEdge && mouseY <= kOSB14BottomEdge) {
// Reset the game mode to NewRound from OptionsScreen
game_state = GameState::kNewRound;
PLOG_INFO << "Options screen Select button pressed -> Reset game state to NewRound";
break;
				}


				// Set Recruit difficulty selection in options screen
				if (mouseX >= kOSB20LeftEdge && mouseX <= kOSB20RightEdge && mouseY >= kOSB20TopEdge && mouseY <= kOSB20BottomEdge) {
					gameDifficulty = Difficulty::kRecruit;
					PLOG_INFO << "Difficulty changed to Recruit";
					break;
				}

				// Set Cadet difficulty selection in options screen
				if (mouseX >= kOSB19LeftEdge && mouseX <= kOSB19RightEdge && mouseY >= kOSB19TopEdge && mouseY <= kOSB19BottomEdge) {
					gameDifficulty = Difficulty::kCadet;
					PLOG_INFO << "Difficulty changed to Cadet";
					break;
				}

				// Set Rookie difficulty selection in options screen
				if (mouseX >= kOSB18LeftEdge && mouseX <= kOSB18RightEdge && mouseY >= kOSB18TopEdge && mouseY <= kOSB18BottomEdge) {
					gameDifficulty = Difficulty::kRookie;
					PLOG_INFO << "Difficulty changed to Rookie";
					break;
				}

				// Set Veteran difficulty selection in options screen
				if (mouseX >= kOSB17LeftEdge && mouseX <= kOSB17RightEdge && mouseY >= kOSB17TopEdge && mouseY <= kOSB17BottomEdge) {
					gameDifficulty = Difficulty::kVeteran;
					PLOG_INFO << "Difficulty changed to Veteran";
					break;
				}

				// Set Ace difficulty selection in options screen
				//if (mouseX >= kOSB16LeftEdge && mouseX <= kOSB16RightEdge && mouseY >= kOSB16TopEdge && mouseY <= kOSB16BottomEdge) {
				//	gameDifficulty = Difficulty::kAce;
				//	PLOG_INFO << "Difficulty changed to Ace";
				//	break;
				//}
			}

			// Handle clicks when game is running
			if (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound) {

				// Handle a click that's inside the MFD surround (not a button press but a guess by the user)
				if (mouseX >= kMfdScreenLeftInsideEdge && mouseX <= kMfdScreenRightInsideEdge &&
					mouseY >= kMfdScreenTopInsideEdge && mouseY <= kMfdScreenBottomInsideEdge) {
					mouse_click_position.x = mouseX;
					mouse_click_position.y = mouseY;
					PLOG_INFO << "HSD guess made -> Calling CheckGuessAgainstWinCondition()";
					game_state = GameState::kRoundPlaying;
					round_manager_->CheckGuessAgainstWinCondition(gameDifficulty, game_state, mouse_click_position);
					break;
				}

				// Handle DEP button press, toggle between centered and not centered
				if (mouseX >= kOSB1LeftEdge && mouseX <= kOSB1RightEdge && mouseY >= kOSB1TopEdge && mouseY <= kOSB1BottomEdge) {
					if (round_manager_->hsd_screen_->GetCenteredState()) {
						round_manager_->hsd_screen_->SetCenteredState(true);
						PLOG_INFO << "HSD DEP button press -> HSD state changed to centered";
						break;
					}
					else {
						round_manager_->hsd_screen_->SetCenteredState(false);
						PLOG_INFO << "HSD DEP button press -> HSD centered state set to false";
					}
				}

				// Handle Increase Range button press
				if (mouseX >= kOSB20LeftEdge && mouseX <= kOSB20RightEdge && mouseY >= kOSB20TopEdge && mouseY <= kOSB20BottomEdge) {
					round_manager_->hsd_screen_->IncreaseRange();
					PLOG_INFO << "HSD increase range button pressed";
					break;
				}

				// Handle Decrease Range button press
				if (mouseX >= kOSB19LeftEdge && mouseX <= kOSB19RightEdge && mouseY >= kOSB19TopEdge && mouseY <= kOSB19BottomEdge) {
					round_manager_->hsd_screen_->DecreaseRange();
					PLOG_INFO << "HSD decrease range button pressed";
					break;
				}

				// Handle Exit button press
				else if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					game_state = GameState::kGameEnded;
					is_game_running = false;
					PLOG_INFO << "HSD Exit button pressed -> game state set to kGameEnded";
					break;
				}
			}	// end of game state == kRoundPlaying if loop
		}	// end of switch
	}	// end of while loop
}


void SA_Trainer::Run() {


	while (is_game_running ) {
		// Delay at the start of each round to allow player to see results before new round
		round_manager_->SetupRound(gameDifficulty, game_state);
		
		while (game_state != GameState::kGameEnded) {
			// Limit speed to consistent frame rate. Not really needed in this application, but good practice to include it anyway.
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), milliseconds_previous_frame_ + kmilliseconds_per_frame));

			// Store the current frame time
			milliseconds_previous_frame_ = SDL_GetTicks();

			ProcessInput();
			Render();
		}
		// Sleep(2000);
		round_manager_->ResetRound();
		game_state = GameState::kNewRound;
	}
}