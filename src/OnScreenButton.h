///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Abstraction of the On-Screen Button, the small push buttons around the edge of the MFD (Multi Function Display).
//              This class contains the position and size of the button, it knows when the mouse pointer is clicked inside a 
//              button and it knows what to display on screen in the unclicked, clicked or toggled state.
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OSB_H
#define OSB_H

#include <iostream>
#include "Main.h"

namespace cpv {
    enum class ButtonState {
        kButtonActive,
        kButtonInactive,
    };

    class OnSceenButton {
    // Attributes
    protected:
        int button_x_pos_ = 0;
        int button_y_pos_ = 0;
        int button_x_pos_end_ = 0;
        int button_y_pos_end_ = 0;
        std::string button_text_;
        ButtonState buttonState_{ ButtonState::kButtonInactive };

    private:
        bool is_button_toggelable_;
    
    // Methods
    protected: 

    public:
        OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable);
        ~OnSceenButton();
        bool IsMousePointerOverButton(Coordinates mousePosition);
        void SetButtonState(ButtonState);
        ButtonState GetButtonState();
        void SetButtonText(std::string buttonText);
        std::string GetButtonText();
        void HighlightText(bool flag);
    };
}

#endif // OSB_H