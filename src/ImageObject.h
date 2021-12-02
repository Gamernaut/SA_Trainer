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
//#include <SDL.h>
//#include <SDL_Image.h>
#include "Main.h"

namespace cpv {

	class ImageObject {
		// Attributes
		protected:
			std::string name_;
			SDL_Surface* image_surface_ = nullptr;
			SDL_Texture* image_texture_ = nullptr;
			double rotation_angle_ = 0.0;
			int image_width_ = 0;
			int image_height_ = 0;
			// Actually holds the scale setting from 0 to 6 which when used with the right  array gives the current HSD range
			int hsd_range_to_aircraft = 0;

		public:
			Coordinates position_{ 0,0 };
			Coordinates image_center_{ 0, 0 };

		// Methods

		public:
			ImageObject(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~ImageObject();
			virtual void Draw(SDL_Renderer* renderer);
			void DrawCenteredAt(SDL_Renderer* renderer, Coordinates center_point);
			void DrawArc(SDL_Renderer* renderer, int user_bearing_guess);
			void SetRandomPosition();
			Coordinates GetPosition();
			void RotateToFinalAngle(double angleInDegrees);
			std::string GetObjectName();
			bool ValidPosition(int x, int y);
			int GetWidth();
			int GetHeight();
	};

}
#endif		// SCREENOBJECT_H
