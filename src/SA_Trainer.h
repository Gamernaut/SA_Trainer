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

//#include <vector>
#include <memory>
//#include <array>
#include <SDL_ttf.h>
#include "image_object.h"
#include "bullseye.h"
#include "aircraft.h"
#include "hsd.h"
#include "options_screen.h"
#include "start_screen.h"

namespace cpv {
	
	// Forward declarations
	//class RoundManager;	

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
		std::string bogey_call_text = "Needs updating to match the data generated in the RoundManger.StartRound() method";

		// Pointers for the main SDL objects (can these be converted to smart pointers due to the SDL API return values)
		SDL_Window* window_ = nullptr;
		SDL_Renderer* renderer_ = nullptr;
		TTF_Font* font_ = nullptr;

		// Pointers to screens
		std::unique_ptr<StartScreen> start_screen_ = nullptr;
		std::unique_ptr<OptionsScreen> options_screen_ = nullptr;
		std::unique_ptr<HSD> hsd_screen_ = nullptr;
		// std::unique_ptr<FCR> fcr_screen_ = nullptr;			// Future addition

		// Various objects on the HSD
		std::unique_ptr<ImageObject> correct_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_arc_ = nullptr;
		std::unique_ptr<ImageObject> correct_guess_rect_ = nullptr;
		std::unique_ptr<ImageObject> wrong_guess_rect_ = nullptr;
		
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
		// Transitions are 
		//		Start Screen -> New Round -> Options or RoundPlaying
		//		Options -> RoundStarting or Exit
		//		RoundPlaying -> RoundWon, RoundFail or Exit
		//		RoundWon or RoundFail -> New Round
		//		Exit at any point except Options screen

		enum class GameState {
			// The starting state and shows the start screen
			kStartScreen,
			// Shows the options screen
			kOptionsScreen,
			// This is after the user moves from the start or options screen to the "Game" screen but before the first guess
			kNewRound,
			// User has clicked on the MFD and made a guess but after roundStarting state but has not used all their guesses yet
			kRoundPlaying,
			// User guessed correctly
			kRoundWon,
			// User failed to guess the correct location after the predefined number of attempts
			kRoundFail,
			// Used to signal that the user wants to quit the game
			kGameEnded
		};
		GameState game_state{ GameState::kStartScreen };
		GameState temp_game_state{ game_state };

		// Needs to be public so other classes can access it as it's NOT a child of SA_Trainer
		enum class Difficulty {
			kRecruit,
			kCadet,
			kRookie,
			kVeteran,
			kAce
		};
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
		void SetupRound();
	};

}

#endif // SA_TRAINER_H