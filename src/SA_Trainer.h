///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:	
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SA_TRAINER_H
#define SA_TRAINER_H

#include<vector>
#include <SDL_ttf.h>
#include "ImageObject.h"
#include "TextObject.h"
#include "Bullseye.h"
#include "Aircraft.h"

class SA_Trainer {
// Properties
protected:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	TTF_Font* font_ = nullptr;

	std::vector<ImageObject*> loading_screen_image_list_;
	std::vector<ImageObject*> options_screen_image_list_;
	ImageObject* game_screen_image_list_[5];
	std::vector<TextObject> font16;

	int milliseconds_previous_frame_ = 0;
	int my_aircraft_heading = 0;
	int bogey_heading[3] = { 0, 0, 0 };
	bool is_game_running = false;
	bool is_round_running = false;

	// Pointers for game screen objects
	ImageObject* hsd_distance_rings_ = nullptr;
	ImageObject* bearing_ring_ = nullptr;
	Aircraft* my_aircraft_ = nullptr;
	ImageObject* mfd_frame_ = nullptr;
	Aircraft* bogey[3] = { nullptr, nullptr, nullptr };
	Bullseye* bullseye_ = nullptr;

	// Enum to hold state for rendering etc.
	enum class GameState {
		kMenu,
		kSetup,
		kPlaying
	};
	GameState gameState{ GameState::kMenu };

	enum class Difficulty {
		kRecruit,
		kCadet,
		kRookie,
		kVeteran,
		kAce
	};
	Difficulty gameDifficulty{ Difficulty::kRookie };

public:

// Methods
private:
	void RenderLoadingScreen();
	void RenderOptionsSceen();
	void RenderGameScreen();
	bool LoadAndSetUpSDL();
	bool SetupLoadingScreen();
	bool SetupGameScreen();
	bool SetupOptionsScreen();


public:
	SA_Trainer();
	~SA_Trainer();
	void initialiseScreens();
	void closeDown();
	void render();
	void update();
	void processInput();
	void run();
	void setupRound();
};

#endif // SA_TRAINER_H