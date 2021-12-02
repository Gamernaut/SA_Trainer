#ifndef CPV_MFD_H_
#define CPV_MFD_H_

#include "Main.h"

// Base Class that represents the MFD, holds all the MFD settings
namespace cpv {

	class MFD {
	// Attributes
	protected:
		int range_level_ = 0;

	// Methods common to all MFDs
	public:
		MFD();
		~MFD();
		Coordinate GetCenterPoint(void);
		int Bearing_FromPoint1ToPoint2(Coordinate point1, Coordinate point2);
	};

} // namespace end

#endif  // CPV_MFD_H_
