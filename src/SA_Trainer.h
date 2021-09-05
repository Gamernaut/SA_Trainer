#ifndef SA_TRAINER_H
#define SA_TRAINER_H

#include <SDL_ttf.h>

class SA_Trainer {
// Properties
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool isRunning = false;
	TTF_Font* font = nullptr;
	// Enum to hold state for rendering etc.
	enum class GameState {
		menu,
		setup,
		playing
	};
	GameState gameState{ GameState::menu };
	SDL_Point mPosition;
	enum class Difficulty {
		recruit,
		cadet,
		rookie,
		veteran,
		ace
	};
	Difficulty gameDifficulty{ Difficulty::rookie };
	int millisecondsPreviousFrame = 0;

public:

// Methods
private:
	void renderMenuScreen();
	void renderSetupSceen();
	void renderGameScreen();

public:
	SA_Trainer();
	~SA_Trainer();
	void initialise();
	void closeDown();
	void render();
	void update();
	void processInput();
	void run();
	void setupRound();
};

#endif // SA_TRAINER_H