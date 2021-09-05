#ifndef BULLSEYE_H
#define BULLSEYE_H

#include <SDL.h>
#include <SDL_image.h>
#include "config.h"


class Bullseye {
private:
	Coordinates currentBullseye{ 0,0 };
	SDL_Surface* bullseye;
	SDL_Texture* bullseyeTexture;

public:
	const double PI = 3.14159265;

private:

public:
	Bullseye();
	~Bullseye();
	Coordinates generatePosition();
	int calculateBearingToBullseye(Coordinates);
	int calculateBearingToBogey(Coordinates);
	Coordinates getCoordinates();
	int calculateDistanceTo(Coordinates);
};

#endif	// BULLSEYE_H