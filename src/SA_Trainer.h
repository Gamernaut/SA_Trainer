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
#include "image_object.h"
#include "bullseye.h"
#include "aircraft.h"
#include "hsd.h"
#include "options_screen.h"
#include "start_screen.h"

namespace cpv {

//	class RoundManager;	// Add forward declaration

	class SA_Trainer {
	// Properties
	protected:
		int milliseconds_previous_frame_ = 0;
		int my_aircraft_heading = 0;
		int bogey_heading[3] = { 0, 0, 0 };
		bool is_game_running = false;
		bool round_is_running = false;
		int user_bearing_guess = 0;
		int bogey_bearing_from_bulleye = 0;
		int actual_bearing = 0;
		int bulls_range = 0;
		bool user_guessed = false;
		int user_guess_count = 0;

		// This is the line that gets displayed above the MFD to the user that tells them the info they need to locate the bogey
		std::string bogey_call_text = "Needs updating to match the data generated in the RoundManger.StartRound() method";

		// Pointers for the main SDL objects (needs converting to smart pointers)
		SDL_Window* window_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		TTF_Font* font_ = nullptr;

		// Pointers to MFDs
		std::unique_ptr<StartScreen> start_screen_ = nullptr;
		std::unique_ptr<HSD> hsd_screen_ = nullptr;
		// std::unique_ptr<OptionsScreen> options_screen_ = nullptr;
		// std::unique_ptr<FCR> fcr_screen_ = nullptr;

		// Various objects on the HSD


		std::unique_ptr<ImageObject> correct_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> correct_guess_rect_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_rect_ = nullptr;
		

		// Collections to hold screen layout that doesn't change
		std::vector<ImageObject*> loading_screen_image_list_;
		// std::vector<ImageObject*> options_screen_image_list_;
		// std::vector<std::unique_ptr<ImageObject>> loading_screen_image_list_;
		std::vector<std::unique_ptr<ImageObject>> options_screen_image_list_;
		//std::vector<std::unique_ptr<ImageObject>> game_screen_text_list_;

		// Fonts to be used in the game
		/*std::unique_ptr<TextObject> font_26_;
		std::unique_ptr<TextObject> font_24_;
		std::unique_ptr<TextObject> font_22_;
		std::unique_ptr<TextObject> font_20_;
		std::unique_ptr<TextObject> font_18_;
		std::unique_ptr<TextObject> font_16_;
		std::unique_ptr<TextObject> font_14_;*/

//		std::unique_ptr<RoundManager> round_manager_ = nullptr;

		Coordinate mouse_click_position{ 0, 0 };

	public:
		// Enum to hold state
		enum class GameState {
			kStartScreen,
			kOptionsScreen,
			kRoundStarting,
			kRoundWon,
			kRoundFail,
			kRoundPlaying,
			kRoundEnded
		};
		GameState game_state{ GameState::kStartScreen };
		GameState temp_game_state{ game_state };

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

	// Methods
	private:
		void RenderLoadingScreen();
		void RenderOptionsSceen();
		void RenderGameScreen();
		bool LoadAndSetUpSDL();
		bool SetupLoadingScreen();
		bool SetupGameScreen();
		bool SetupOptionsScreen();
		void WasUsersGuessRight(Coordinate mouse_click_position);

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