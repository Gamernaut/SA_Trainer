#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SA_Trainer.h"
#include "config.h"
#include "Bullseye.h"

SA_Trainer::SA_Trainer() {

}


SA_Trainer::~SA_Trainer() {

}



void SA_Trainer::initialise() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL library" << std::endl;
		return;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Error initializing TTF library" << std::endl;
		return;
	}

	// Fake full screen as it's just a window that is the same size of the screen
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	window = SDL_CreateWindow(
		"SA Trainer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		NULL
	);

	if (!window) {
		std::cerr << "Error creating SDL window" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		std::cerr << "Error creating SDL Renderer" << std::endl;
		return;
	}

	font = TTF_OpenFont(fontName1, fontSize1);
	if (!font) {
		std::cerr << "Error opening font Renderer" << std::endl;
		return;
	}

	isRunning = true;
}

void SA_Trainer::closeDown() {
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}



void SA_Trainer::renderGameScreen() {
	int textWidth{ 0 }, textHeight{ 0 };
	int textWidth1{ 0 }, textHeight1{ 0 };
	int textWidth2{ 0 }, textHeight2{ 0 };

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//// Load MFD image
	SDL_Surface* MFD = IMG_Load(mfdFileName);
	SDL_Texture* MFDtexture = SDL_CreateTextureFromSurface(renderer, MFD);
	SDL_FreeSurface(MFD);
	SDL_Rect MFDdestRect = {
		mfdPaddingLeft,
		mfdPaddingTop,
		mfdImageWidth,
		mfdImageHeight
	};
	SDL_RenderCopy(renderer, MFDtexture, NULL, &MFDdestRect);
	SDL_DestroyTexture(MFDtexture);

	// Load Bearing ring image
	SDL_Surface* ring = IMG_Load(bearingCircle);
	SDL_Texture* ringtexture = SDL_CreateTextureFromSurface(renderer, ring);
	SDL_FreeSurface(ring);
	SDL_Rect ringDestRect = {
		mfdScreenLeftInsideEdge + 20,
		mfdScreenBottomInsideEdge - 120,
		bearingCircleWidth,
		bearingCircleHeight
	};
	SDL_RenderCopy(renderer, ringtexture, NULL, &ringDestRect);
	SDL_DestroyTexture(ringtexture);

	// Load distance rings image
	SDL_Surface* distRings = IMG_Load(distRingsFileName);
	SDL_Texture* distRingstexture = SDL_CreateTextureFromSurface(renderer, distRings);
	SDL_FreeSurface(distRings);
	SDL_Rect destRingsDestRect = {
		mfdCenter.x - (distRingsImageWidth / 2),
		mfdCenter.y - (distRingsImageHeight / 2),
		distRingsImageWidth,
		distRingsImageHeight
	};
	SDL_RenderCopy(renderer, distRingstexture, NULL, &destRingsDestRect);
	SDL_DestroyTexture(distRingstexture);

	// Load aircraft image
	SDL_Surface* aircraft = IMG_Load(aircraftFileName);
	SDL_Texture* aircraftTexture = SDL_CreateTextureFromSurface(renderer, aircraft);
	SDL_FreeSurface(aircraft);
	SDL_Rect aircraftDestRect = {
		mfdCenter.x - (aircraftImageWidth / 2),
		mfdCenter.y - 5,
		aircraftImageWidth,
		aircraftImageHeight
	};
	SDL_RenderCopy(renderer, aircraftTexture, NULL, &aircraftDestRect);
	SDL_DestroyTexture(aircraftTexture);

	// Load bullseye image
	SDL_Surface* bullseye = IMG_Load(bullsFileName);
	SDL_Texture* bullseyeTexture = SDL_CreateTextureFromSurface(renderer, bullseye);
	SDL_FreeSurface(bullseye);
	SDL_Rect bullseyeDestRect = {
		bullsCenter.x - (bullsImageWidth / 2),
		bullsCenter.y - (bullsImageHeight / 2),
		bullsImageWidth,
		bullsImageHeight
	};
	SDL_RenderCopy(renderer, bullseyeTexture, NULL, &bullseyeDestRect);
	SDL_DestroyTexture(bullseyeTexture);

	//////////////////////////////////////////////////////////
	// Font based text for text that changes (numbers etc.)
	//////////////////////////////////////////////////////////

	// Distance to bullseye
	SDL_Surface* distTextSurface = TTF_RenderText_Blended(font, distanceText, mfdBlueColour);
	SDL_Texture* distTextTexture = SDL_CreateTextureFromSurface(renderer, distTextSurface);
	TTF_SizeText(font, distanceText, &textWidth, &textHeight);
	SDL_Rect distDestRect = {
		mfdScreenLeftInsideEdge + 50,
		mfdScreenBottomInsideEdge - 77,
		textWidth,
		textHeight
	};
	SDL_FreeSurface(distTextSurface);
	SDL_RenderCopy(renderer, distTextTexture, NULL, &distDestRect);
	SDL_DestroyTexture(distTextTexture);


	// Bearing to bullseye
	SDL_Surface* bearingTextSurface = TTF_RenderText_Blended(font, bearingText, mfdBlueColour);
	SDL_Texture* bearingTextTexture = SDL_CreateTextureFromSurface(renderer, bearingTextSurface);
	TTF_SizeText(font, bearingText, &textWidth, &textHeight);
	SDL_Rect bearingDestRect = {
		mfdScreenLeftInsideEdge + 47,
		mfdScreenBottomInsideEdge - 20,
		textWidth,
		textHeight
	};
	SDL_FreeSurface(bearingTextSurface);
	SDL_RenderCopy(renderer, bearingTextTexture, NULL, &bearingDestRect);
	SDL_DestroyTexture(bearingTextTexture);

	// AWACS call text
	SDL_Surface* awacsTextSurface = TTF_RenderText_Blended(font, "AWACS Call:", mfdWhiteColour);
	SDL_Texture* awacsTextTexture = SDL_CreateTextureFromSurface(renderer, awacsTextSurface);
	TTF_SizeText(font, "AWACS Call:", &textWidth1, &textHeight1);
	SDL_Rect awacsDestRect = {
		(windowWidth / 2) - (textWidth1 / 2),
		mfdPaddingTop - 150,
		awacsTextSurface->w,
		awacsTextSurface->h
	};
	SDL_FreeSurface(awacsTextSurface);
	SDL_RenderCopy(renderer, awacsTextTexture, NULL, &awacsDestRect);
	SDL_DestroyTexture(awacsTextTexture);

	std::string callText = "Birdseye 1-1, Hostile group bulls 230 for 20, Angles 20, tracking South West";
	SDL_Surface* callTextSurface = TTF_RenderText_Blended(font, callText.c_str(), mfdBlueColour);
	SDL_Texture* callTextTexture = SDL_CreateTextureFromSurface(renderer, callTextSurface);
	TTF_SizeText(font, callText.c_str(), &textWidth2, &textHeight2);
	SDL_Rect callDestRect2 = {
		(windowWidth / 2) - (textWidth2 / 2),
		mfdPaddingTop - 100,
		callTextSurface->w,
		callTextSurface->h
	};
	SDL_FreeSurface(callTextSurface);
	SDL_RenderCopy(renderer, callTextTexture, NULL, &callDestRect2);
	SDL_DestroyTexture(callTextTexture);

	// Description of what to do
	std::string difficultyText1, difficultyText2;
	if (gameDifficulty == Difficulty::ace) {
		difficultyText1 = "Difficulty: ACE";
		difficultyText2 = "Click on HSD close to all groups of bogey's";
	} else if (gameDifficulty == Difficulty::cadet && gameState == GameState::playing) {
		difficultyText1 = "Difficulty: CADET";
		difficultyText2 = "Click on HSD close to the bullseye";
	} else if (gameDifficulty == Difficulty::recruit && gameState == GameState::playing) {
		difficultyText1 = "Difficulty: RECRUIT";
		difficultyText2 = "Click on HSD in the direction of the bullseye";
	} else if (gameDifficulty == Difficulty::rookie && gameState == GameState::playing) {
		difficultyText1 = "Difficulty: ROOKIE";
		difficultyText2 = "Click on HSD in the direction of the bogey from the bullseye";
	} else if (gameDifficulty == Difficulty::veteran && gameState == GameState::playing) {
		difficultyText1 = "Difficulty: VETERAN";
		difficultyText2 = "Click on HSD close to the bogey's";
	}
	SDL_Surface* descriptionTextSurface1 = TTF_RenderText_Blended(font, difficultyText1.c_str(), mfdWhiteColour);
	SDL_Texture* descriptionTextTexture1 = SDL_CreateTextureFromSurface(renderer, descriptionTextSurface1);
	TTF_SizeText(font, difficultyText1.c_str(), &textWidth1, &textHeight1);
	SDL_Rect descriptionDestRect1 = {
		(windowWidth / 2) - (textWidth1 / 2),
		mfdPaddingTop - 50,
		descriptionTextSurface1->w,
		descriptionTextSurface1->h
	};
	SDL_FreeSurface(descriptionTextSurface1);
	SDL_RenderCopy(renderer, descriptionTextTexture1, NULL, &descriptionDestRect1);
	SDL_DestroyTexture(descriptionTextTexture1);

	SDL_Surface* descriptionTextSurface2 = TTF_RenderText_Blended(font, difficultyText2.c_str(), mfdWhiteColour);
	SDL_Texture* descriptionTextTexture2 = SDL_CreateTextureFromSurface(renderer, descriptionTextSurface2);
	TTF_SizeText(font, difficultyText2.c_str(), &textWidth2, &textHeight2);
	SDL_Rect descriptionDestRect2 = {
		(windowWidth / 2) - (textWidth2 / 2),
		mfdPaddingTop - 30,
		descriptionTextSurface2->w,
		descriptionTextSurface2->h
	};
	SDL_FreeSurface(descriptionTextSurface2);
	SDL_RenderCopy(renderer, descriptionTextTexture2, NULL, &descriptionDestRect2);
	SDL_DestroyTexture(descriptionTextTexture2);
}

void SA_Trainer::renderMenuScreen() {
	// Title text
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* titleTextSurface = IMG_Load(gameTitleFilename);
	SDL_Texture* titleTextTexture = SDL_CreateTextureFromSurface(renderer, titleTextSurface);
	SDL_FreeSurface(titleTextSurface);
	SDL_Rect titleTextDestRect = {
		(windowWidth / 2) - (gameTitleWidth / 2),
		(mfdPaddingTop / 2) - (gameTitleHeight / 2),
		gameTitleWidth,
		gameTitleHeight
	};
	SDL_RenderCopy(renderer, titleTextTexture, NULL, &titleTextDestRect);
	SDL_DestroyTexture(titleTextTexture);


	// MFD and image
	SDL_Surface* startSurface = IMG_Load(gameStartMenuFileName);
	SDL_Texture* starttexture = SDL_CreateTextureFromSurface(renderer, startSurface);
	SDL_FreeSurface(startSurface);
	SDL_Rect startDestRect = {
		mfdPaddingLeft,
		mfdPaddingTop,
		mfdImageWidth,
		mfdImageHeight
	};
	SDL_RenderCopy(renderer, starttexture, NULL, &startDestRect);
	SDL_DestroyTexture(starttexture);

}

void SA_Trainer::renderSetupSceen() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Surface* MFD = IMG_Load(mfdSetupFileName);
	SDL_Texture* MFDtexture = SDL_CreateTextureFromSurface(renderer, MFD);
	SDL_FreeSurface(MFD);
	SDL_Rect MFDdestRect = {
		mfdPaddingLeft,
		mfdPaddingTop,
		mfdImageWidth,
		mfdImageHeight
	};
	SDL_RenderCopy(renderer, MFDtexture, NULL, &MFDdestRect);
	SDL_DestroyTexture(MFDtexture);

	if (gameDifficulty == Difficulty::ace) {
		SDL_Surface* description = IMG_Load(aceLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			aceImageWidth,
			aceImageHeight
		};
		SDL_RenderCopy(renderer, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::cadet) {
		SDL_Surface* description = IMG_Load(cadetLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			cadetImageWidth,
			cadetImageHeight
		};
		SDL_RenderCopy(renderer, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::recruit) {
		SDL_Surface* description = IMG_Load(recruitLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			recruitImageWidth,
			recruitImageHeight
		};
		SDL_RenderCopy(renderer, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::rookie) {
		SDL_Surface* description = IMG_Load(rookieLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			rookieImageWidth,
			rookieImageHeight
		};
		SDL_RenderCopy(renderer, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}
	else if (gameDifficulty == Difficulty::veteran) {
		SDL_Surface* description = IMG_Load(veteranLevelFileName);
		SDL_Texture* descptionTexture = SDL_CreateTextureFromSurface(renderer, description);
		SDL_FreeSurface(description);
		SDL_Rect destRect = {
			mfdCenter.x - 150,
			mfdCenter.y - 100,
			veteranImageWidth,
			veteranImageHeight
		};
		SDL_RenderCopy(renderer, descptionTexture, NULL, &destRect);
		SDL_DestroyTexture(descptionTexture);
	}

}

void SA_Trainer::render() {
	// basically check the game state and then render the appropriate view
	switch (gameState) {
		case GameState::menu:
			renderMenuScreen();
			break;
		case GameState::setup:
			renderSetupSceen();
			break;
		case GameState::playing:
			renderGameScreen();
			break;
	}

	SDL_RenderPresent(renderer);
}

void SA_Trainer::update() {

}

void SA_Trainer::processInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
					break;
				}

			case SDL_MOUSEBUTTONUP:
				//Get mouse position
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				std::cout << "Mouse position is x = " << mouseX << " and y = " << mouseY << std::endl;

				// Handle Start button on main screen
				if (mouseX >= startButtonLeftEdge && mouseX <= startButtonRightEdge && mouseY >= startButtonTopEdge && mouseY <= startButtonBottomEdge) {
					if (gameState == GameState::menu) {
						gameState = GameState::playing;
						break;
					}
				}

				// Handle Setup/Back button
				if (mouseX >= setupButtonLeftEdge && mouseX <= setupButtonRightEdge && mouseY >= setupButtonTopEdge && mouseY <= setupButtonBottomEdge) {
					if (gameState == GameState::playing) {
						gameState = GameState::setup;
						break;
					}
					if (gameState == GameState::setup) {
						gameState = GameState::playing;
						break;
					}
				}
				// Handle Recruit difficulty selection in setup screen
				if (mouseX >= recruitButtonLeftEdge && mouseX <= recruitButtonRightEdge && mouseY >= recruitButtonTopEdge && mouseY <= recruitButtonBottomEdge && gameState == GameState::setup) {
					gameDifficulty = Difficulty::recruit;
					std::cout << "Difficulty changed to Recruit" << std::endl;
					break;
				}

				// Handle Cadet selection in setup screen
				if (mouseX >= cadetButtonLeftEdge && mouseX <= cadetButtonRightEdge && mouseY >= cadetButtonTopEdge && mouseY <= cadetButtonBottomEdge && gameState == GameState::setup) {
					gameDifficulty = Difficulty::cadet;
					std::cout << "Difficulty changed to Cadet" << std::endl;
					break;
				}

				// Handle Rookie selection in setup screen
				if (mouseX >= rookieButtonLeftEdge && mouseX <= rookieButtonRightEdge && mouseY >= rookieButtonTopEdge && mouseY <= rookieButtonBottomEdge && gameState == GameState::setup) {
					gameDifficulty = Difficulty::rookie;
					std::cout << "Difficulty changed to Rookie" << std::endl;
					break;
				}

				// Handle Veteran selection in setup screen
				if (mouseX >= veteranButtonLeftEdge && mouseX <= veteranButtonRightEdge && mouseY >= veteranButtonTopEdge && mouseY <= veteranButtonBottomEdge && gameState == GameState::setup) {
					gameDifficulty = Difficulty::veteran;
					std::cout << "Difficulty changed to Veteran" << std::endl;
				}

				// Handle Ace selection in setup screen
				if (mouseX >= aceButtonLeftEdge && mouseX <= aceButtonRightEdge && mouseY >= aceButtonTopEdge && mouseY <= aceButtonBottomEdge && gameState == GameState::setup) {
					gameDifficulty = Difficulty::ace;
					std::cout << "Difficulty changed to Ace" << std::endl;
				}

				if (mouseX >= exitButtonLeftEdge && mouseX <= exitButtonRightEdge && mouseY >= exitButtonTopEdge && mouseY <= exitButtonBottomEdge) {
					std::cout << "Mouse is inside the Exit button" << std::endl;
					isRunning = false;
					break;
				}
				break;

			case SDL_MOUSEMOTION:
				if (mouseX >= exitButtonLeftEdge && mouseX <= exitButtonRightEdge && mouseY >= exitButtonTopEdge && mouseY <= exitButtonBottomEdge) {
					std::cout << "Mouse is hovering over the Exit button" << std::endl;
					break;
				}
			break;
		}
	}
}

void SA_Trainer::setupRound() {
	// create bullseye object
	Bullseye bullseye;
}

void SA_Trainer::run() {
	// This function needs to manage each round, so it needs to initialise a round (set the bulls eye and display the AWACS call to the player
	// needs a loop
	// 
	// calls setup round
	setupRound();
	// then loops through processInput, update and render until user clicks
	// 
	// checks if click and bullseye align, informs user and starts a new round

	while (isRunning) {
		// Limit speed to consistent frame rate. Not really needed in this app, but good practice to include it anyway.
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), millisecondsPreviousFrame + MILLISECONDS_PER_FRAME));

		// Store the current frame time
		millisecondsPreviousFrame = SDL_GetTicks();

		processInput();
		update();
		render();
	}
}