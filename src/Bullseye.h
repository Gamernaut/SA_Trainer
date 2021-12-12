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

		public:
			Bullseye(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~Bullseye();
			void SetPosition(Coordinate);
			Coordinate GetPosition();
	};

}

#endif	// BULLSEYE_H
