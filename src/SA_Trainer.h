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

#include <vector>
#include <memory>
#include <array>
#include <SDL_ttf.h>
#include "ImageObject.h"
#include "TextObject.h"
#include "Bullseye.h"
#include "Aircraft.h"
#include "HSD.h"

namespace cpv {

	class RoundManager;	// Add forward declaration

	class SA_Trainer {
	// Properties
	protected:
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

		// Used to hold distances of HSD
		// When the display is centered the HSD rings represent different ranges from when not centered
		int hsd_range_centered_[6] = { 5, 10, 20, 40, 80, 160 };	

		// None centered ranges
		int hsd_range_[6] = { 8, 15, 30, 60, 120, 240 };
		int fcr_range_[6] = { 5, 10, 20, 40, 80, 160 };
		int hsd_range_level_ = 0;

		// Pointers for the main SDL objects (needs converting to smart pointers)
		SDL_Window* window_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		TTF_Font* font_ = nullptr;

		// Various objects on the HSD
		std::unique_ptr<ImageObject> hsd_distance_rings_ = nullptr;
		std::unique_ptr<ImageObject> bearing_ring_ = nullptr;
		std::unique_ptr<Aircraft> my_aircraft_ = nullptr;
		Aircraft* bogeys[3] = { nullptr, nullptr, nullptr };
		//std::unique_ptr<Aircraft> bogeys[3] = { nullptr, nullptr, nullptr };
		//std::vector <std::unique_ptr<Aircraft>> bogey_list_;
		//std::array<std::unique_ptr<Aircraft>, 3> bogeys = { nullptr, nullptr, nullptr };
		std::unique_ptr<Bullseye> bullseye_ = nullptr;
		std::unique_ptr<ImageObject> mfd_frame_ = nullptr;
		std::unique_ptr<ImageObject> correct_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> correct_guess_rect_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_rect_ = nullptr;
		std::unique_ptr<ImageObject> bearing_pointer_ = nullptr;

		// Collections to hold screen layout that doesn't change
		std::vector<ImageObject*> loading_screen_image_list_;
		// std::vector<ImageObject*> options_screen_image_list_;
		// std::vector<std::unique_ptr<ImageObject>> loading_screen_image_list_;
		std::vector<std::unique_ptr<ImageObject>> options_screen_image_list_;
		//std::vector<std::unique_ptr<ImageObject>> game_screen_text_list_;

		// Fonts to be used in the game
		std::unique_ptr<TextObject> font_26_;
		std::unique_ptr<TextObject> font_24_;
		std::unique_ptr<TextObject> font_22_;
		std::unique_ptr<TextObject> font_20_;
		std::unique_ptr<TextObject> font_18_;
		std::unique_ptr<TextObject> font_16_;
		std::unique_ptr<TextObject> font_14_;

		std::unique_ptr<RoundManager> round_manager_ = nullptr;

		Coordinates mouse_click_position{ 0, 0 };

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
		void Initialise();
		void CloseDown();
		void Render();
		void ProcessInput();
		void Run();
		void SetupRound();
	};

}

#endif // SA_TRAINER_H