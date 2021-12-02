///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Abstraction of the Horizontal Situation Display. This is a type of MFD (Multi Function Display) and is surrounded 
//				by OSBs (On-Screen Buttons).
//              This class holds the overall state of the HSD, it knows settings such as the range, in the app world, and where the 
//				various objects are on the HSD. It uses the maths functions and returns the in app distance and angles between various
//				objects. It also knows about the buttons around the edge and updates the state based on their settings.
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_HSD_H_
#define CPV_HSD_H_

#include <vector>
#include <memory>
#include <plog/Log.h>
#include "Main.h"
#include "MFD.h"
#include "OnScreenButton.h"

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

		std::unique_ptr<OnSceenButton> osb1 = nullptr;
		std::unique_ptr<OnSceenButton> osb19 = nullptr;
		std::unique_ptr<OnSceenButton> osb20 = nullptr;


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
		int Distance_BetweenPoint1AndPoint2(Coordinate point1, Coordinate point2);
	};
}



#endif // CPV_HSD_H_