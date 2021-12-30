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

#include "game_enums.h"
#include "hsd.h"
#include "options_screen.h"
#include "start_screen.h"
#include "round_manager.h"

namespace cpv {

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
		int logging_level = 2;

		// This is the line that gets displayed above the MFD to the user that tells them the info they need to locate the bogey
		std::string bogey_call_text = "Needs updating to match the data generated in the RoundManger.SetupRound() method";

		// Pointers for the main SDL objects (can these be converted to smart pointers due to the SDL API return values)
		SDL_Window* window_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		TTF_Font* font_ = nullptr;

		// Pointers to screens
		std::unique_ptr<StartScreen> start_screen_ = nullptr;
		std::unique_ptr<OptionsScreen> options_screen_ = nullptr;

		// Various objects on the HSD
		std::unique_ptr<ImageObject> correct_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> correct_guess_rect_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_rect_ = nullptr;
		
		std::unique_ptr<RoundManager> round_manager_ = nullptr;

		Coordinate mouse_click_position{ 0, 0 };

	public:
		GameState game_state{ GameState::kStartScreen };
		GameState temp_game_state{ game_state };

		Difficulty gameDifficulty{ Difficulty::kRecruit };
		Difficulty tempDiff{ gameDifficulty };		// holds the difficulty setting when the user is in the setup screen.

	// Methods
	private:
		void RenderStartScreen();
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
	};

}

#endif // SA_TRAINER_H