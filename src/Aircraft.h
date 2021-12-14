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

#include <cmath>
#include <memory>
#include "image_object.h"

namespace cpv {

	class Aircraft : public ImageObject {
		public:
			double	current_heading_ = 0.0;

		protected:
			Coordinate Bearing_to_xy_position(int bearing);


		public:
			Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~Aircraft();
			void SetRandomHeading();
			int GetHeading();
			void DrawBogey(SDL_Renderer* renderer, std::unique_ptr<Aircraft> &my_aircraft_, int hsd_range_level_);
			BearingDistance RandomiseBearingAndDistance();
	};

}
#endif // AIRCRAFT_H