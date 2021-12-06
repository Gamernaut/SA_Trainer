///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <iostream>
//#include <SDL.h>
#include <SDL_image.h>
#include <plog/Log.h>
#include "image_object.h"

using namespace cpv;

ImageObject::ImageObject(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition) {
	// Store parameters in object
	position_.x = xPosition;
	position_.y = yPosition;
	name_ = filename;

	image_surface_ = IMG_Load(filename.c_str());
	if (!image_surface_) {
		PLOG_ERROR << "Couldn't load image " << filename;
		return;
	}
	image_texture_ = SDL_CreateTextureFromSurface(renderer, image_surface_);
	if (!image_texture_) {
		PLOG_ERROR << "Couldn't create texture for " << filename << "SDL returned error " << SDL_GetError();
		std::cout << "Couldn't create texture for " << filename << "SDL returned error " << SDL_GetError() << std::endl;
		return;
	}

	image_width_ = image_surface_->w;
	image_height_ = image_surface_->h;

	image_center_.x = position_.x + image_width_ / 2;
	image_center_.y = position_.y + image_height_ / 2;
}

ImageObject::~ImageObject() {
	SDL_FreeSurface(image_surface_);
	SDL_DestroyTexture(image_texture_);
}

void ImageObject::Draw(SDL_Renderer* renderer) {
	SDL_Rect imageDestinationRectangle = { position_.x, position_.y, image_width_, image_height_ };

	int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
	if (renderSuccess != 0) {
		PLOG_ERROR << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::Draw()";
		std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::Draw()" << std::endl;
	}
}

void ImageObject::DrawCenteredAt(SDL_Renderer* renderer, Coordinate center_point) {
	SDL_Rect imageDestinationRectangle = { center_point.x - (image_width_/ 2), center_point.y - (image_height_ / 2), image_width_, image_height_ };

	int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
	if (renderSuccess != 0) {
		PLOG_ERROR << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::DrawCenteredAt()";
		std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::DrawCenteredAt()" << std::endl;
	}
}

void ImageObject::DrawArc(SDL_Renderer* renderer, int user_bearing_guess) {
	// Need to center the middle of the bottom of the image in the center of the aircraft.
	// then rotate the image to match the bearing the user selected with the center of the
	// pie slice aligning with the point the user clicked on.

	// Non matrix maths for rotating around an arbitary point https://academo.org/demos/rotation-about-point/

	int top_left_corner_x = 359 - (image_width_ / 2);
	int top_left_corner_y = 667 - (image_height_ / 2);

	SDL_Rect imageDestinationRectangle = { top_left_corner_x, top_left_corner_y, image_width_, image_height_ };

	RotateToFinalAngle(user_bearing_guess);

	int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
	if (renderSuccess != 0) {
		std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::Draw()" << std::endl;
	}
}

inline bool ImageObject::ValidPosition(int x, int y) {
	bool result = false;
	int square_dist = 0;

	if (x >= kMfdScreenLeftInsideEdge && x <= kMfdScreenRightInsideEdge && y >= kMfdScreenTopInsideEdge && y <= kMfdScreenBottomInsideEdge) {
		square_dist = (kMFDCenter.x - x) ^ 2 + (kMFDCenter.y - y) ^ 2;
		result = square_dist <= kHSDDistRingsImageWidth_ / 2;
	}
	return result;
}

void ImageObject::SetRandomPosition() {
	Coordinate newPosition;

	do {
		newPosition.x = (rand() % kWindowWidth);
		newPosition.y = (rand() % kWindowHeight);
	} while (!ValidPosition(newPosition.x, newPosition.y));

	// Add top and left side offsets to convert from window coordinates to MFD screen
	image_center_.x = newPosition.x + (image_width_ / 2);
	image_center_.y = newPosition.y + (image_height_ / 2);
	position_.x = newPosition.x;
	position_.y = newPosition.y;
	hsd_range_to_aircraft = 0;	// Set HSD range to maximum (0th element in the HSD range array)
}

Coordinate ImageObject::GetPosition() {
	return image_center_;
}

void ImageObject::RotateToFinalAngle(double angleInDegrees) {
	rotation_angle_ = angleInDegrees;
}

int ImageObject::GetWidth(){
	return image_width_;
}

int ImageObject::GetHeight() {
	return image_height_;
}

std::string ImageObject::GetObjectName() {
	return name_;
}