///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:	
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include "ImageObject.h"

ImageObject::ImageObject(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) {
	// Store parameters in object
	position_.x = xPosition;
	position_.y = yPosition;
	name_ = filename;

	std::cout << "Trying to open image file: " << filename << std::endl;
	image_surface_ = IMG_Load(filename.c_str());
	if (!image_surface_) {
		std::cout << "Couldn't load image " << filename << std::endl;
	}
	image_texture_ = SDL_CreateTextureFromSurface(renderer, image_surface_);
	if (!image_texture_) {
		std::cout << "Couldn't create texture for " << filename << std::endl;
	}

	image_center_.x = image_surface_->w / 2;
	image_center_.y = image_surface_->h / 2;
}


ImageObject::~ImageObject() {
	SDL_FreeSurface(image_surface_);
	SDL_DestroyTexture(image_texture_);
}




void ImageObject::DrawAt(SDL_Renderer* renderer, int xPosition, int yPosition) {
	SDL_Rect imageDestinationRectangle = {xPosition, yPosition, image_surface_->w, image_surface_->h};

	//SDL_RenderCopy(renderer, imageTexture, NULL, &imageDestinationRectangle);
	int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
	if (renderSuccess != 0) {
		std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::drawAt()" << std::endl;
	}
}


void ImageObject::Draw(SDL_Renderer* renderer) {
	SDL_Rect imageDestinationRectangle = { position_.x, position_.y, image_surface_->w, image_surface_->h};

	// int renderSuccess = SDL_RenderCopy(renderer, imageTexture, NULL, &imageDestinationRectangle);
	int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
	if (renderSuccess != 0) {
		std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::draw()" << std::endl;
	}
}

//Coordinates ImageObject::RandomPosition() {
//	Coordinates newPosition;
//
//	srand((unsigned)time(0));
//
//	// Generate random x, y positions that are inside the HSD distance rings
//	// Formula is (x - center_x)^2 + (y - center_y)^2 < radius^2 where 
//
//	do {
//		newPosition.x = (rand() % kDistRingsImageWidth);
//		newPosition.y = (rand() % kDistRingsImageHeight);
//	} while (!ValidPosition(newPosition.x, newPosition.y));
//
//	// Add top and left side offsets to convert from window coordinates to MFD screen
//	newPosition.x += kDistRingsImageWidth / 2 ;
//	newPosition.y += kMfdScreenTopInsideEdge;
//
//	return newPosition;
//}


inline bool ImageObject::ValidPosition(int x, int y) {
	bool result = false;
	int square_dist = 0;

	if (x >= kMfdScreenLeftInsideEdge && x <= kMfdScreenRightInsideEdge && y >= kMfdScreenTopInsideEdge && y <= kMfdScreenBottomInsideEdge) {
		square_dist = (mfdCenter.x - x) ^ 2 + (mfdCenter.y - y) ^ 2;
		result = square_dist <= kDistRingsImageWidth / 2;
	}
	return result;
}

void ImageObject::SetRandomPosition() {
	Coordinates newPosition;

	srand((unsigned)time(0));

	// Generate random x, y positions that are inside the HSD distance rings
	// Formula is (x - center_x)^2 + (y - center_y)^2 < radius^2 where 

	do {
		newPosition.x = (rand() % kWindowWidth);
		newPosition.y = (rand() % kWindowHeight);
	} while (!ValidPosition(newPosition.x, newPosition.y));

	// Add top and left side offsets to convert from window coordinates to MFD screen
	position_.x = newPosition.x;
	position_.y = newPosition.y;
}


Coordinates ImageObject::GetPosition() {
	return position_;
}

void ImageObject::RotateToFinalAngle(double angleInDegrees) {
	rotation_angle_ = angleInDegrees;
}


std::string ImageObject::GetObjectName() {
	return name_;
}

