#ifndef CPV_HSD_H_
#define CPV_HSD_H_

#include <vector>
#include <memory>
#include "Main.h"
#include "MFD.h"

// Class that represents the HSD, holds all the HSD settings and knows about all the objects displayed on the HSD
namespace cpv {

	class HSD : public MFD {
		// Constants
	private:
		// Distance rings attributes, needs to rotate so needs to have a center
		const char* kDistRingsFileName = "./assets/images/distance_rings_646x646.png";
		const int kHSDDistRingsImageWidth_ = 646;
		const int kHSDDistRingsImageHeight_ = 646;
		const int kHSDCenterOffset_ = 110;

		// Attributes
	protected:
		bool centered_ = false;
		std::vector<int> HSD_centered_ranges = { 5, 10, 20, 40, 80, 160 };
		std::vector<int> HSD_ranges = { 8, 15, 30, 60, 120, 240 };
//		int range_level_ = 0;


	public:
		// std::unique_ptr<int> myInt(new int(47));


		// Methods
	protected:


	public:
		HSD();
		~HSD();
		void SetCenteredState(bool new_state);
		bool GetCenteredState(void);
		void IncreaseRange(void);
		void DecreaseRange(void);
		int GetCurrentRange(void);
		double GetMilesPerPixel(void);
		int Distance_BetweenPoint1AndPoint2(Coordinates point1, Coordinates point2);
	};
}



#endif // CPV_HSD_H_