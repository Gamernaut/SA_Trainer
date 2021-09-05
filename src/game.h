#pragma once

#include <SDL.h>

class Game {

// Properties
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	int windowHeight;
	int windowWidth;


// Methods
private:



public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void Cleanup();
	void ProcessInput();
	void Update();
	void Render();
	void Setup();
};