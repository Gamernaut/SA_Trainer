///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:	
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SDL.h>
#include <SDL_image.h>
#include "Main.h"
#include "ImageObject.h"


class Aircraft : public ImageObject {

public:
	double	current_heading_ = 0.0;

public:
	Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
	~Aircraft();
	void SetRandomHeading();
	int GetHeading();
};

#endif // AIRCRAFT_H