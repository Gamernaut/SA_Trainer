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
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SA_Trainer.h"
#include "Main.h"
#include "Bullseye.h"
#include "aircraft.h"
#include "ImageObject.h"
#include "TextObject.h"


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
		
//	TextObject font(renderer, "./assets/fonts/white-rabbit/whitrabt.ttf" , 16);
	font_ = TTF_OpenFont(kFontName1, kFontSize1);
	if (!font_) {
		std::cerr << "Error opening font Renderer" << std::endl;
		return false;
	}
		
	is_game_running = true;
	return true;
}


bool SA_Trainer::SetupLoadingScreen() {
	// Allocate on the heap not the stack or when the function ends the object is destroyed and it looses it's link to the texture even though the object is copied into the vector the texture is lost.
	ImageObject* loadingScreenTitle= new ImageObject(renderer_, kGameTitleFilename, (kWindowWidth / 2) - (kGameTitleWidth / 2), (kMfdPaddingTop / 2) - (kGameTitleHeight / 2));
	loading_screen_image_list_.push_back(loadingScreenTitle);

	ImageObject* mfdSurround = new ImageObject(renderer_, kGameStartMenuFileName, kMfdPaddingLeft, kMfdPaddingTop);
	loading_screen_image_list_.push_back(mfdSurround);

	return true;
}


bool SA_Trainer::SetupGameScreen() {
	// create distance rings 
	hsd_distance_rings_ = new ImageObject(renderer_, kDistRingsFileName, mfdCenter.x - (kDistRingsImageWidth / 2), (mfdCenter.y - (kDistRingsImageHeight / 2)) + kDepOffset);

	// create Bearing ring image
	bearing_ring_ = new ImageObject(renderer_, kBearingCircle, kMfdScreenLeftInsideEdge + 20, kMfdScreenBottomInsideEdge - 80);

	// create my aircraft
	my_aircraft_ = new Aircraft(renderer_, kAircraftFileName, mfdCenter.x - (kAircraftImageWidth / 2), (mfdCenter.y - 5) + kDepOffset);

	// create a bogey
	bogey[0] = new Aircraft(renderer_, kAircraftFileName, mfdCenter.x - (kAircraftImageWidth / 2), mfdCenter.y - 5);

	// Create bullseye
	bullseye_ = new Bullseye(renderer_, kBullsFileName, mfdCenter.x - (kBullsImageWidth / 2), mfdCenter.y - (kBullsImageHeight / 2));

	// create MFD background
	mfd_frame_ = new ImageObject(renderer_, kMfdFileName, kMfdPaddingLeft, kMfdPaddingTop);


	// ALL THIS BELOW NEED REFACTORING BUT NEED TO  THINK ABOUT HOW WE USE TEXT AND IMAGE OBJECTS IN SAME COLLECTION -> COMMON BASE CLASS

	////////////////////////////////////////////////////////////
	//// Font based text for text that changes (numbers etc.)
	////////////////////////////////////////////////////////////

	//int textWidth, textHeight = 0;
	//int textWidth1, textHeight1 = 0;
	//int textWidth2, textHeight2 = 0;

	//// Distance to bullseye
	//SDL_Surface* distTextSurface = TTF_RenderText_Blended(font_, kDistanceText, kMfdBlueColour);
	//SDL_Texture* distTextTexture = SDL_CreateTextureFromSurface(renderer_, distTextSurface);
	//TTF_SizeText(font_, kDistanceText, &textWidth, &textHeight);
	//SDL_Rect distDestRect = {
	//	kMfdScreenLeftInsideEdge + 50,
	//	kMfdScreenBottomInsideEdge - 77,
	//	textWidth,
	//	textHeight
	//};
	//SDL_FreeSurface(distTextSurface);
	//SDL_RenderCopy(renderer_, distTextTexture, NULL, &distDestRect);
	//SDL_DestroyTexture(distTextTexture);


	//// Bearing to bullseye
	//SDL_Surface* bearingTextSurface = TTF_RenderText_Blended(font_, kBearingText, kMfdBlueColour);
	//SDL_Texture* bearingTextTexture = SDL_CreateTextureFromSurface(renderer_, bearingTextSurface);
	//TTF_SizeText(font_, kBearingText, &textWidth, &textHeight);
	//SDL_Rect bearingDestRect = {
	//	kMfdScreenLeftInsideEdge + 47,
	//	kMfdScreenBottomInsideEdge - 20,
	//	textWidth,
	//	textHeight
	//};
	//SDL_FreeSurface(bearingTextSurface);
	//SDL_RenderCopy(renderer_, bearingTextTexture, NULL, &bearingDestRect);
	//SDL_DestroyTexture(bearingTextTexture);

	//// AWACS call text
	//SDL_Surface* awacsTextSurface = TTF_RenderText_Blended(font_, "AWACS Call:", kMfdWhiteColour);
	//SDL_Texture* awacsTextTexture = SDL_CreateTextureFromSurface(renderer_, awacsTextSurface);
	//TTF_SizeText(font_, "AWACS Call:", &textWidth1, &textHeight1);
	//SDL_Rect awacsDestRect = {
	//	(kWindowWidth / 2) - (textWidth1 / 2),
	//	kMfdPaddingTop - 150,
	//	awacsTextSurface->w,
	//	awacsTextSurface->h
	//};
	//SDL_FreeSurface(awacsTextSurface);
	//SDL_RenderCopy(renderer_, awacsTextTexture, NULL, &awacsDestRect);
	//SDL_DestroyTexture(awacsTextTexture);

	//std::string callText = "Birdseye 1-1, Hostile group bulls 230 for 20, Angles 20, tracking South West";
	//SDL_Surface* callTextSurface = TTF_RenderText_Blended(font_, callText.c_str(), kMfdBlueColour);
	//SDL_Texture* callTextTexture = SDL_CreateTextureFromSurface(renderer_, callTextSurface);
	//TTF_SizeText(font_, callText.c_str(), &textWidth2, &textHeight2);
	//SDL_Rect callDestRect2 = {
	//	(kWindowWidth / 2) - (textWidth2 / 2),
	//	kMfdPaddingTop - 100,
	//	callTextSurface->w,
	//	callTextSurface->h
	//};
	//SDL_FreeSurface(callTextSurface);
	//SDL_RenderCopy(renderer_, callTextTexture, NULL, &callDestRect2);
	//SDL_DestroyTexture(callTextTexture);

	return true;
}


bool SA_Trainer::SetupOptionsScreen() {
	// Allocate on the heap not the stack or when the function ends the object is destroyed and it looses it's link to the texture even though the object is copied into the vector the texture is lost.
	ImageObject* mfdFrame = new ImageObject(renderer_, kMfdSetupFileName, kMfdPaddingLeft, kMfdPaddingTop);
	options_screen_image_list_.push_back(mfdFrame);

	if (gameDifficulty == Difficulty::kAce) {
		SDL_Surface* description = IMG_Load(kAceLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer_, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			kAceImageWidth,
			kAceImageHeight
		};
		SDL_RenderCopy(renderer_, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::kCadet) {
		SDL_Surface* description = IMG_Load(kCadetLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer_, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			kCadetImageWidth,
			kCadetImageHeight
		};
		SDL_RenderCopy(renderer_, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::kRecruit) {
		SDL_Surface* description = IMG_Load(kRecruitLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer_, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			kRecruitImageWidth,
			kRecruitImageHeight
		};
		SDL_RenderCopy(renderer_, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::kRookie) {
		SDL_Surface* description = IMG_Load(kRookieLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer_, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			kRookieImageWidth,
			kRookieImageHeight
		};
		SDL_RenderCopy(renderer_, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::kVeteran) {
		SDL_Surface* description = IMG_Load(kVeteranLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer_, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			kVeteranImageWidth,
			kVeteranImageHeight
		};
		SDL_RenderCopy(renderer_, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	return true;
}


void SA_Trainer::initialiseScreens() {
	if (!LoadAndSetUpSDL()) {
		std::cerr << "Error setting up SDL" << std::endl;
	}

	if (!SetupLoadingScreen()) {
		std::cerr << "Error creating Loading screen" << std::endl;
	}

	if (!SetupGameScreen()) {
		std::cerr << "Error creating Game screen" << std::endl;
	}

	if (!SetupOptionsScreen()) {
		std::cerr << "Error creating Options screen" << std::endl;
	}

}


void SA_Trainer::closeDown() {
	// delete bullseye;
	loading_screen_image_list_.clear();
	options_screen_image_list_.clear();
	delete hsd_distance_rings_;
	delete bearing_ring_;
	delete my_aircraft_;
	delete mfd_frame_;
	delete bullseye_;
	delete bogey[0];
	delete bogey[1];
	delete bogey[2];
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
	my_aircraft_->Draw(renderer_);
	mfd_frame_->Draw(renderer_);

	// This is here just for testing
	bullseye_->Draw(renderer_);
	
	SDL_RenderPresent(renderer_);


	//// ALL THIS BELOW NEED MOVING TO THE MOST APPROPRIATE FUNCTION
	//int textWidth, textHeight = 0;
	//int textWidth1, textHeight1 = 0;

	//// Description of what to do
	//std::string difficultyText1, difficultyText2;
	//if (gameDifficulty == Difficulty::ace) {
	//	difficultyText1 = "Difficulty: ACE";
	//	difficultyText2 = "Click on HSD close to all groups of bogey's";
	//} else if (gameDifficulty == Difficulty::cadet && gameState == GameState::playing) {
	//	difficultyText1 = "Difficulty: CADET";
	//	difficultyText2 = "Click on HSD close to the bullseye";
	//} else if (gameDifficulty == Difficulty::recruit && gameState == GameState::playing) {
	//	difficultyText1 = "Difficulty: RECRUIT";
	//	difficultyText2 = "Click on HSD in the direction of the bullseye";
	//} else if (gameDifficulty == Difficulty::rookie && gameState == GameState::playing) {
	//	difficultyText1 = "Difficulty: ROOKIE";
	//	difficultyText2 = "Click on HSD in the direction of the bogey from the bullseye";
	//} else if (gameDifficulty == Difficulty::veteran && gameState == GameState::playing) {
	//	difficultyText1 = "Difficulty: VETERAN";
	//	difficultyText2 = "Click on HSD close to the bogey's";
	//}
	//SDL_Surface* descriptionTextSurface1 = TTF_RenderText_Blended(font, difficultyText1.c_str(), mfdWhiteColour);
	//SDL_Texture* descriptionTextTexture1 = SDL_CreateTextureFromSurface(gRenderer, descriptionTextSurface1);
	//TTF_SizeText(font, difficultyText1.c_str(), &textWidth, &textHeight);
	//SDL_Rect descriptionDestRect1 = {
	//	(windowWidth / 2) - (textWidth / 2),
	//	mfdPaddingTop - 50,
	//	descriptionTextSurface1->w,
	//	descriptionTextSurface1->h
	//};
	//SDL_FreeSurface(descriptionTextSurface1);
	//SDL_RenderCopy(gRenderer, descriptionTextTexture1, NULL, &descriptionDestRect1);
	//SDL_DestroyTexture(descriptionTextTexture1);

	//SDL_Surface* descriptionTextSurface2 = TTF_RenderText_Blended(font, difficultyText2.c_str(), mfdWhiteColour);
	//SDL_Texture* descriptionTextTexture2 = SDL_CreateTextureFromSurface(gRenderer, descriptionTextSurface2);
	//TTF_SizeText(font, difficultyText2.c_str(), &textWidth1, &textHeight1);
	//SDL_Rect descriptionDestRect2 = {
	//	(windowWidth / 2) - (textWidth1 / 2),
	//	mfdPaddingTop - 30,
	//	descriptionTextSurface2->w,
	//	descriptionTextSurface2->h
	//};
	//SDL_FreeSurface(descriptionTextSurface2);
	//SDL_RenderCopy(gRenderer, descriptionTextTexture2, NULL, &descriptionDestRect2);
	//SDL_DestroyTexture(descriptionTextTexture2);
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

	for (std::size_t i = 0; i < options_screen_image_list_.size(); ++i) {
		options_screen_image_list_[i]->Draw(renderer_);
	}

	SDL_RenderPresent(renderer_);
}


void SA_Trainer::render() {
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

	// SDL_RenderPresent(renderer_);
}


void SA_Trainer::update() {

}


void SA_Trainer::processInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				is_game_running = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					is_game_running = false;
					break;
				}

			case SDL_MOUSEBUTTONUP:
				//Get mouse position
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				std::cout << "Mouse position is x = " << mouseX << " and y = " << mouseY << std::endl;

				// Handle Start button on main screen
				if (mouseX >= kStartButtonLeftEdge && mouseX <= kStartButtonRightEdge && mouseY >= kStartButtonTopEdge && mouseY <= kStartButtonBottomEdge) {
					if (gameState == GameState::kMenu) {
						gameState = GameState::kPlaying;
						break;
					}
				}

				// Handle Setup/Back button
				if (mouseX >= kSetupButtonLeftEdge && mouseX <= kSetupButtonRightEdge && mouseY >= kSetupButtonTopEdge && mouseY <= kSetupButtonBottomEdge) {
					if (gameState == GameState::kPlaying) {
						gameState = GameState::kSetup;
						break;
					}
					if (gameState == GameState::kSetup) {
						gameState = GameState::kPlaying;
						break;
					}
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
				}

				// Handle Ace selection in setup screen
				if (mouseX >= kAceButtonLeftEdge && mouseX <= kAceButtonRightEdge && mouseY >= kAceButtonTopEdge && mouseY <= kAceButtonBottomEdge && gameState == GameState::kSetup) {
					gameDifficulty = Difficulty::kAce;
					std::cout << "Difficulty changed to Ace" << std::endl;
				}

				if (mouseX >= kExitButtonLeftEdge && mouseX <= kExitButtonRightEdge && mouseY >= kExitButtonTopEdge && mouseY <= kExitButtonBottomEdge) {
					std::cout << "Mouse is inside the Exit button" << std::endl;
					is_game_running = false;
					break;
				}
				break;
			break;
		}
	}
}


void SA_Trainer::setupRound() {

std::cout << "Initial - My aircraft position " << my_aircraft_->position_.x << ", " << my_aircraft_->position_.y << " and heading " << my_aircraft_->current_heading_ << std::endl;

	// Set random bullseye position for this round
	bullseye_->SetRandomPosition();
	bullseye_->Draw(renderer_);


std::cout << "Info for bullseye " << bullseye_->position_.x << ", " << bullseye_->position_.y << std::endl;


	// Set random heading of my aircraft for this round and rotate HSD distance rings to match that heading
	my_aircraft_->SetRandomHeading();
	hsd_distance_rings_->RotateToFinalAngle(my_aircraft_->GetHeading());
	hsd_distance_rings_->Draw(renderer_);


std::cout << "My aircraft heading " << my_aircraft_->current_heading_ << std::endl;


	// Set the heading of the bearing ring to point to the bulls eye
	int heading_to_bullseye = bullseye_->CalculateBearingToBullseye(my_aircraft_->position_);
	bearing_ring_->RotateToFinalAngle(heading_to_bullseye);

	// Select a random HSD range from 5m to 160m, using ranges on HSD
	int HSD_Range = (rand() % 160);

	if (HSD_Range <= 8) { HSD_Range = 8; }
	else if (HSD_Range > 8 && HSD_Range <= 15) { HSD_Range = 15; }
	else if (HSD_Range > 15 && HSD_Range <= 30) { HSD_Range = 30; }
	else if (HSD_Range > 30 && HSD_Range <= 60) { HSD_Range = 60; }
	else if (HSD_Range > 60 && HSD_Range <= 120) { HSD_Range = 120; }
	else if (HSD_Range > 120 && HSD_Range <= 240) { HSD_Range = 240; }

	// Set a random position and heading for bogey's
	bogey[0]->SetRandomPosition();
	bogey[0]->SetRandomHeading();


}


void SA_Trainer::run() {
	// This function needs to manage each round, so it needs to initialise a round (set the bulls eye and display the AWACS call to the player)
	// needs a loop
	
	setupRound();
	// then loops through processInput, update and render until user clicks
	// 
	// checks if click and bullseye align, informs user and starts a new round

	while (is_game_running) {
		// Limit speed to consistent frame rate. Not really needed in this app, but good practice to include it anyway.
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), milliseconds_previous_frame_ + kmilliseconds_per_frame));

		// Store the current frame time
		milliseconds_previous_frame_ = SDL_GetTicks();

		processInput();
		update();
		render();
	}
}