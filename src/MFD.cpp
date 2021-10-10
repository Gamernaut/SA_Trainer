#include "Main.h"
#include "MFD.h"

using namespace cpv;

MFD::MFD() {

}

MFD::~MFD() {

}

Coordinates MFD::GetCenterPoint(void) {
	Coordinates CenterPoint{
		kMfdScreenLeftInsideEdge + (kMfdScreenWidth / 2),
		kMfdScreenTopInsideEdge + (kMfdScreenHeight / 2)
	};

	return CenterPoint;
}

int MFD::Bearing_FromPoint1ToPoint2(Coordinates point1, Coordinates point2) {
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

