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

#include "image_object.h"

namespace cpv {

	class Bullseye : public ImageObject {
		public:
			SDL_Surface* bullseye_surface_ = nullptr;
			SDL_Texture* bullseye_texture_ = nullptr;
			const double PI_ = 3.14159265;
			BearingDistance bulls_relative_bd_ = { 0, 0 };

		public:
			Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~Bullseye();
			Coordinate GetPosition();
			void RandomiseBearingAndDistance();
			int GetDistance();
			int GetBearing();

			// delete after testing
			void SetPosition(BearingDistance start_position);
	};

}

#endif	// BULLSEYE_H
