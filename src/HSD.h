///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Abstraction of the Horizontal Situation Display (HSD). This is a type of MFD (Multi Function Display) and is surrounded 
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
#include "main.h"
#include "maths_functions.h"
#include "mfd.h"
#include "on_screen_button.h"
#include "image_object.h"
#include "aircraft.h"
#include "bullseye.h"
#include "text_object.h"

namespace cpv {

	class HSD : public MFD {
	// Attributes
	private:

	protected:
		bool centered_ = false;
		std::vector<int> HSD_centered_ranges = { 5, 10, 20, 40, 80, 160 };
		std::vector<int> HSD_ranges = { 8, 15, 30, 60, 120, 240 };

		// Various objects on the HSD
		std::unique_ptr<ImageObject> hsd_distance_rings_ = nullptr;
		std::unique_ptr<ImageObject> bearing_ring_ = nullptr;
		std::unique_ptr<ImageObject> bearing_pointer_ = nullptr;
		std::unique_ptr<Aircraft> my_aircraft_ = nullptr;
		std::unique_ptr<Bullseye> bullseye_ = nullptr;
//		Aircraft* bogeys[3] = { nullptr, nullptr, nullptr };
		//std::unique_ptr<Aircraft> bogeys[3] = { nullptr, nullptr, nullptr };
		//std::vector <std::unique_ptr<Aircraft>> bogey_list_;
		//std::array<std::unique_ptr<Aircraft>, 3> bogeys = { nullptr, nullptr, nullptr };

		// On Screen Buttons used on HSD
		std::unique_ptr<OnSceenButton> setup_button = nullptr;
		std::unique_ptr<OnSceenButton> exit_button = nullptr;
		std::unique_ptr<OnSceenButton> inc_rng_button = nullptr;
		std::unique_ptr<OnSceenButton> dec_rng_button = nullptr;
		std::unique_ptr<OnSceenButton> dep_rng_button = nullptr;

		// // Fonts for drawing text on screen
		std::unique_ptr<TextObject> font_26_ = nullptr;
		std::unique_ptr<TextObject> font_24_ = nullptr;
		std::unique_ptr<TextObject> font_22_ = nullptr;
		std::unique_ptr<TextObject> font_20_ = nullptr;
		std::unique_ptr<TextObject> font_18_ = nullptr;
		std::unique_ptr<TextObject> font_16_ = nullptr;
		std::unique_ptr<TextObject> font_14_ = nullptr;

	public:

		


	// Methods
	protected:


	public:
		HSD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~HSD();
		void SetCenteredState(bool new_state);
		bool GetCenteredState(void);
		void IncreaseRange(void);
		void DecreaseRange(void);
		int GetHSDCurrentRange(void);
		double GetMilesPerPixel(void);
		std::unique_ptr<OnSceenButton> AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text);
		std::unique_ptr<OnSceenButton> AddOsbButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name);
		void Draw();
		void DisplayAwacsMessage(std::string awacs_call);
	};
}



#endif // CPV_HSD_H_