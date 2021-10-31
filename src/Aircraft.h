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

#include "ImageObject.h"

namespace cpv {

	class Aircraft : public ImageObject {
		public:
			double	current_heading_ = 0.0;

		protected:
			Coordinates Bearing_to_xy_position(int bearing);

		public:
			Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~Aircraft();
			void SetRandomHeading();
			int GetHeading();
			//void Draw(SDL_Renderer* renderer);
	};

}
#endif // AIRCRAFT_H