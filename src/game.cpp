#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include "Game.h"

Game::Game() {
	isRunning = false;
	std::cout << "Game constructor called" << std::endl;
}


Game::~Game() {
	std::cout << "Game destructor called" << std::endl;
}


void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL library" << std::endl;
		return;
	}

	// Fake full screen as it's just a window that is the same size of the screen
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowHeight = 1920; // Set the width and height to the same for everyone (will end up with black borders)
	windowWidth = 1080; 

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
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

	// Set video mode to real full screen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}


glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
	// Setup game objects
	playerPosition = glm::vec2(100.0, 200.0);
	playerVelocity = glm::vec2(0.1, 0.0);
}


void Game::Cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Game::ProcessInput() {
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
		}
	}
}


void Game::Update() {
	// TODO -> Update game objects
	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
}


void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	// Draw PNG texture
	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Define the destination rectangle as the same size as the source
	SDL_Rect destRect = { 
		static_cast<int>(playerPosition.x), 
		static_cast<int>(playerPosition.y),
		32,
		32 };

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
	SDL_DestroyTexture(texture);

	// TODO -> render all game objects

	SDL_RenderPresent(renderer);
}


void Game::Run() {
	Setup();

	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}