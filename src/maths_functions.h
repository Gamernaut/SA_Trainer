#ifndef CPV_MATHS_FUNCTIONS_H
#define CPV_MATHS_FUNCTIONS_H

#include "main.h"

namespace cpv {

	// Use inlined functions so each translation unit doesn't include a copy in the obj or we get symbol redefinition error during the linking

	// Use Pythagoras' therom to calculate the number of pixels between the 2 points
	inline int pixels_between_point_a_and_b(Coordinate start_point, Coordinate end_point) {
		int xdist = start_point.x - end_point.x;
		int ydist = start_point.y - end_point.y;
		double distance = sqrt((xdist * xdist) + (ydist * ydist));
		return static_cast<int>(distance);
    }


    inline int angle_between_point_a_and_b(Coordinate point1, Coordinate point2) {
		// We'll be using the difference in x1,y1 and x2,y2 coordinates
		// we can use the atan2(y,x) function where y = y2 - y1 and x = x2 - x1 where x1,y1 is the starting point
		// However, this function can return a negative value when x < 0 so need to adapt formula to give a result between 0 and 359 deg

		const double kTwoPi = 6.2831853071795865;
		const double kRad2Deg = 57.2957795130823209;

		double x1 = static_cast<double>(point1.x);
		double y1 = static_cast<double>(point1.y);
		double x2 = static_cast<double>(point2.x);
		double y2 = static_cast<double>(point2.y);
		double theta = 0.0;

		theta = atan2(x2 - x1, y1 - y2);
		if (theta < 0.0)
			theta += kTwoPi;
		return static_cast<int>(kRad2Deg * theta);
    }


	inline int MilesBetweenPoint1AndPoint2(Coordinate point_1, Coordinate point_2, double miles_per_pixel) {

		int pixel_distance = pixels_between_point_a_and_b(point_1, point_2);
		
		return static_cast<int>(pixel_distance * miles_per_pixel);
	}


	inline Coordinate endpoint_given_start_and_bearing(Coordinate start_point, int bogey_current_heading, int my_aircraft_current_heading, int distance_in_miles, double miles_per_pixel) {
	//inline int endpoint_given_start_and_bearing(Coordinate start_point, int bogey_current_heading, int my_aircraft_current_heading, int line_length = 20) {
		// Bit of trigonometry to work out the end co-ordinates based on the relative headings.
		// The basic equation is to add the sin of the angle multiplied by the line length to get the new X position.
		// For the new y position you use the cosine function. However, as the y position increases in value as you go down the screen we have to use
		// the -cosine to get the y position. So the formula are:
		// 
		//		new x = old x + ( length of line * sine (bogey heading in radians)
		//		new y = old y + ( length of line * -cosine (bogey heading in radians)
		//
		// However, these formula assume that the F16 is heading north, but that will most likely not be the case so these formula also need to take 
		// account of the F16s heading otherwise the line will always be drawn as if straight up is north. Basically we need the difference in angle
		// between the F16 heading and the bogey heading and use that to calculate the new x,y position for the end of the line. Lets take the 
		// example of the F16 on a heading of 315 (NW) and a bogey heading 90 (East). If we calculate the end of line on the bogeys 90 heading it 
		// actually looks like it's heading SE once you mentally rotate the F16s heading from NW to N. A really easy way to get the difference
		// is to add the 2 headings together and take the modulo with 360 as that effectively divides by 1 "circle" of the compass leaving as
		// a remainder the difference in degrees between the headings. Note Modulo only works on integers so cast to int. The formula would be 
		//
		//		difference in heading = (heading of F16 + Heading of bogey) % 360
		//
		// For the example above that would be (315 + 90) % 360 = 45 
		// now use the formulas above to calculate the new ending positions with an angle of 45 deg (in radians).

		double deg_to_rads = M_PI / 180;
		int new_X = 0, new_Y = 0;
		int difference_in_angle = 0;

		double scaled_dist = distance_in_miles / miles_per_pixel;

		difference_in_angle = (static_cast<int>(bogey_current_heading) + static_cast<int>(my_aircraft_current_heading)) % 360;
		new_X = static_cast<int>(start_point.x + (scaled_dist * sin(difference_in_angle * deg_to_rads)));
		new_Y = static_cast<int>(start_point.y + (scaled_dist * -cos(difference_in_angle * deg_to_rads)));

		return Coordinate{ new_X , new_Y };		// original to use when not using googletest suit
	}
}

#endif // CPV_MATHS_FUNCTIONS_H