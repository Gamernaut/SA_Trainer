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
#include "image_object.h"
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

		// Watch for a clash with the definition here as well as in sa_trainer.h
		SDL_Renderer* renderer_ = nullptr;
		std::unique_ptr<ImageObject> mfd_frame_ = nullptr;

	public:

	// Methods common to all MFDs
	public:
		MFD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~MFD();
		Coordinate GetCenterPoint(void);
		void Draw();
	};

} // namespace end

#endif  // CPV_MFD_H_
