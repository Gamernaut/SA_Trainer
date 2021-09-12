///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:	
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include "Main.h"

class ImageObject {
// Attributes
protected:
	std::string name_;
	SDL_Surface* image_surface_ = nullptr;
	SDL_Texture* image_texture_ = nullptr;
	double rotation_angle_ = 0.0;
	Coordinates image_center_{ 0, 0 };

public:
	Coordinates position_{ 0,0 };

// Methods

public:
	ImageObject(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
	~ImageObject();
	void DrawAt(SDL_Renderer* renderer, int xPos, int yPos);
	void Draw(SDL_Renderer* renderer);
	Coordinates RandomPosition();
	void SetRandomPosition();
	Coordinates GetPosition();
	void RotateToFinalAngle(double angleInDegrees);
	void RotateByNumberOfDegrees(SDL_Renderer* renderer, double angleInDegrees);
	void Update();
	std::string GetObjectName();
	bool ValidPosition(int x, int y);
};


#endif		// SCREENOBJECT_H
