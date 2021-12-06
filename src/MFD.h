///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Abstraction of the Multi Function Display (MFD) which is surrounded by On-Screen Buttons (OSBs).
//              This class holds pointers to the buttons (as the MFD is used for both in-sim activities and sim set up activities). 
//				It is essentially an abstract class that can be used to create HSD, FCR etc. screens.
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_MFD_H_
#define CPV_MFD_H_

#include <SDL.h>
#include <plog/Log.h>
#include "main.h"
#include "on_screen_button.h"

// Base Class that represents the MFD, holds all the MFD settings
namespace cpv {

	class MFD {
	// Attributes
	protected:
		int range_level_ = 0;
		int mfd_top_edge_ = 0;
		int mfd_left_edge_ = 0;
		int mfd_height_ = 0;
		int mfd_width_ = 0;
		Coordinate center_point_{ 0 , 0 };
		SDL_Renderer* renderer_ = nullptr;

		// To hold the on screen buttons
		std::unique_ptr<OnSceenButton> osb1 = nullptr;
		std::unique_ptr<OnSceenButton> osb2 = nullptr;
		std::unique_ptr<OnSceenButton> osb3 = nullptr;
		std::unique_ptr<OnSceenButton> osb4 = nullptr;
		std::unique_ptr<OnSceenButton> osb5 = nullptr;
		std::unique_ptr<OnSceenButton> osb6 = nullptr;
		std::unique_ptr<OnSceenButton> osb7 = nullptr;
		std::unique_ptr<OnSceenButton> osb8 = nullptr;
		std::unique_ptr<OnSceenButton> osb9 = nullptr;
		std::unique_ptr<OnSceenButton> osb10 = nullptr;
		std::unique_ptr<OnSceenButton> osb11 = nullptr;
		std::unique_ptr<OnSceenButton> osb12 = nullptr;
		std::unique_ptr<OnSceenButton> osb13 = nullptr;
		std::unique_ptr<OnSceenButton> osb14 = nullptr;
		std::unique_ptr<OnSceenButton> osb15 = nullptr;
		std::unique_ptr<OnSceenButton> osb16 = nullptr;
		std::unique_ptr<OnSceenButton> osb17 = nullptr;
		std::unique_ptr<OnSceenButton> osb18 = nullptr;
		std::unique_ptr<OnSceenButton> osb19 = nullptr;
		std::unique_ptr<OnSceenButton> osb20 = nullptr;

	// Methods common to all MFDs
	public:
		MFD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~MFD();
		Coordinate GetCenterPoint(void);
		void Draw();
	};

} // namespace end

#endif  // CPV_MFD_H_
