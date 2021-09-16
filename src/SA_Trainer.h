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

class RoundManager;	// Add forward declaration

class SA_Trainer {
	// Properties
protected:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	TTF_Font* font_ = nullptr;

	// Collections to hold screen layout that doesn't change
	std::vector<ImageObject*> loading_screen_image_list_;
	std::vector<ImageObject*> options_screen_image_list_;
	std::vector<TextObject*> game_screen_text_list_;

	int milliseconds_previous_frame_ = 0;
	int my_aircraft_heading = 0;
	int bogey_heading[3] = { 0, 0, 0 };
	bool is_game_running = false;
	bool round_is_running = false;
	int user_bearing_guess = 0;
	int actual_bearing = 0;
	int bulls_range = 0;
	bool user_guessed = false;
	int user_guess_count = 0;
	RoundManager* round_manager_{ nullptr };

	// Pointers for game screen objects
	ImageObject* hsd_distance_rings_ = nullptr;
	ImageObject* bearing_ring_ = nullptr;
	Aircraft* my_aircraft_ = nullptr;
	ImageObject* mfd_frame_ = nullptr;
	Aircraft* bogeys[3] = { nullptr, nullptr, nullptr }; // remove from here
	Bullseye* bullseye_ = nullptr;
	ImageObject* correct_guess_arc_ = nullptr;
	ImageObject* wrong_guess_arc_ = nullptr;
	ImageObject* correct_guess_rect_ = nullptr;
	ImageObject* wrong_guess_rect_ = nullptr;
	ImageObject* bearing_pointer_ = nullptr;
	

	// Font pointers
	TextObject* font_26_;
	TextObject* font_24_;
	TextObject* font_22_;
	TextObject* font_20_;
	TextObject* font_18_;
	TextObject* font_16_;
	TextObject* font_14_;

	Coordinates mouse_click_position{ 0, 0 };	// remove this it's just for testing purposes

public:
	// Enum to hold state for rendering etc.
	enum class GameState {
		kMenu,
		kSetup,
		kPlaying
	};
	GameState gameState{ GameState::kMenu };

	// Needs to be public so the RoundManager can access it as it's NOT a child of SA_Trainer
	enum class Difficulty {
		kRecruit,
		kCadet,
		kRookie,
		kVeteran,
		kAce
	};
	Difficulty gameDifficulty{ Difficulty::kCadet };
	Difficulty tempDiff{ gameDifficulty };		// holds the difficulty setting when the user is in the setup screen.

	// Enum to hold state of current guess in current round
	enum class RoundState {
		kRoundStarting,
		kWon,
		kFail,
		kPlaying,
		kEnded
	};
	RoundState roundstate{ RoundState::kRoundStarting };
	RoundState temproundstate{ roundstate };

	// Methods
private:
	void RenderLoadingScreen();
	void RenderOptionsSceen();
	void RenderGameScreen();
	bool LoadAndSetUpSDL();
	bool SetupLoadingScreen();
	bool SetupGameScreen();
	bool SetupOptionsScreen();
	void WasUsersGuessRight(Coordinates mouse_click_position);

public:
	SA_Trainer();
	~SA_Trainer();
	void initialiseScreens();
	void closeDown();
	void Render();
	void ProcessInput();
	void run();
	void SetupRound();
};

#endif // SA_TRAINER_H