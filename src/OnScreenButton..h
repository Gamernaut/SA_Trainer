#ifndef _CPV_ONSCREEN_BUTTON_H
#define _CPV_ONSCREEN_BUTTON_H


#include "Main.h"

namespace cpv {

	// On Screen Buttons (OSB) are the gray push buttons around the MFD. The F16 has 20 buttons on the MFD (5 on each side)

	class OSB {
		// attributes
		protected:
			int OSB_Top_Left_Corner_ = 0;
			int OSB_Top_Right_Corner_ = 0;
			int OSB_Bottom_Left_Corner_ = 0;
			int OSB_Bottom_Right_Corner_ = 0;
			int OSB_width_ = OSB_Top_Right_Corner_ - OSB_Top_Left_Corner_;
			int OSB_height_ = OSB_Top_Right_Corner_ - OSB_Bottom_Right_Corner_;
			Coordinates OSB_Center_ = { OSB_Top_Left_Corner_ + (OSB_width_ / 2), OSB_Top_Left_Corner_ + (OSB_height_ / 2) };

	};


}

#endif	// end of _CPV_ONSCREEN_BUTTON_H
