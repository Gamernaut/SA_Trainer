// Implementation of HSD class

#include "HSD.h"

void HSD::SetCenteredState(bool new_state) {
	centered_ = new_state;
}

bool HSD::GetCenteredState(void) {
	return centered_;
}

void HSD::IncreaseRange(void) {
	int range_size = HSD_ranges.size();

	if (range_level_ <= range_size) {
		range_level_ += 1;
	}
	else {
		range_level_ = 0;
	}
}

void HSD::DecreaseRange(void) {
	if (range_level_ >= 0) {
		range_level_ -= 1;
	}
	else {
		range_level_ = 0;
	}
}

int HSD::GetCurrentRange() {
	if (GetCenteredState()) {
		return HSD_centered_ranges[range_level_];
	}
	else {
		return HSD_ranges[range_level_];
	}
}

double HSD::GetMilesPerPixel(void) {
	// Take the number of pixels between the center and the outer ring, about 320px, and divide by range in miles to get miles per miles
	return static_cast<double>(320) / static_cast<double>(GetCurrentRange());
}

int HSD::Bearing_FromPoint1ToPoint2(Coordinates point1, Coordinates point2) {
	// We'll be using the difference in x1,y1 and x2,y2 coordinates
	// we can use the atan2(y,x) function where y = y2 - y1 and x = x2 - x1 where x1,y1 is the starting point
	// However, this function can return a negative value when x < 0 so need to check for a negative number and add 2 PI to get an angle between 0 and 360

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

int HSD::Distance_BetweenPoint1AndPoint2(Coordinates point1, Coordinates point2) {
	// Use Pythagoras' therom to calculate the number of pixels between the 2 points
	double xdist = static_cast<double>(point1.x) - static_cast<double>(point2.x);
	double ydist = static_cast<double>(point1.y) - static_cast<double>(point2.y);

	// convert pixels to a distance based on the range setting then calculate the actual distance between the points
	xdist = xdist * GetMilesPerPixel();
	ydist = ydist * GetMilesPerPixel();

	double distance = sqrt((xdist * xdist) + (ydist * ydist));
	return static_cast<int>(distance);
}