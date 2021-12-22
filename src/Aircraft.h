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

#include "Bullseye.h"


namespace cpv {

	class Aircraft : public ImageObject {
		public:
			double	current_heading_ = 0.0;
			BearingRangeAltitude aircraft_relative_bra_ = { 0, 0, 0 };

		protected:
			Coordinate Bearing_to_xy_position(int bearing);
			std::string awacs_call_string = "";



		public:
			Aircraft(SDL_Renderer* renderer, std::string filename, int xPosition, int yPosition);
			~Aircraft();
			void SetRandomHeading();
			int GetHeading();
			void DrawBogey(SDL_Renderer* renderer, std::unique_ptr<Aircraft>& my_aircraft, Coordinate bulls_pos,/*std::unique_ptr<Bullseye>& bullseye*/ double miles_per_pixel);
			void SetRandomBearingAndDistanceFromBullseye();
			int GetDistanceFromBullseye();
			int GetBearingFromBullseye();
			int GetAltitude();
			void SetAwacsString(std::string awacs_call);
			std::string GetAwacsString();

			// For debugging
			void SetPosition(BearingRangeAltitude start_position);
	};

}
#endif // AIRCRAFT_H