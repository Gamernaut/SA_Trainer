///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BULLSEYE_H
#define BULLSEYE_H

#include "ImageObject.h"

class Bullseye : public ImageObject {
public:
	SDL_Surface* bullseye_surface_ = nullptr;
	SDL_Texture* bullseye_texture_ = nullptr;
	const double PI_ = 3.14159265;

public:
	Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
	~Bullseye();
	void SetPosition(Coordinates);
	Coordinates GetPosition();
	int Bearing_FromPoint1ToPoint2(Coordinates point1, Coordinates point2);
	int Distance_BetweenPoint1AndPoint2(Coordinates start_point, Coordinates end_point);
};

#endif	// BULLSEYE_H
