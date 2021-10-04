#ifndef _HSD_H_
#define _HSD_H_

#include <vector>
#include "Main.h"

// Class that represents the HSD, holds all the HSD settings and knows about all the objects displayed on the HSD

class HSD {
// Attributes
protected:
	bool centered_ = false;
	std::vector<int> HSD_centered_ranges = { 5, 10, 20, 40, 80, 160 };
	std::vector<int> HSD_ranges = { 8, 15, 30, 60, 120, 240 };
	int range_level_ = 0;

public:



// Methods
protected:


public:
	void SetCenteredState(bool new_state);
	bool GetCenteredState(void);
	void IncreaseRange(void);
	void DecreaseRange(void);
	int GetCurrentRange(void);
	double GetMilesPerPixel(void);
	int Bearing_FromPoint1ToPoint2(Coordinates point1, Coordinates point2);
	int Distance_BetweenPoint1AndPoint2(Coordinates point1, Coordinates point2);
};


#endif // _HSD_H_