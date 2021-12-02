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

#include <plog/Log.h>
#include "OnScreenButton.h"

using namespace cpv;

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string screen_text_) {
    button_x_pos_ = xPos;
    button_y_pos_ = yPos;
    button_x_pos_end_ = xPosEnd;
    button_y_pos_end_ = yPosEnd;
    is_button_toggelable_ = toggelable;
    button_name_ = button_name;
    button_screen_text_ = screen_text_;

    PLOG_INFO << "Button " << button_name_ << "created";
}
 
OnSceenButton::~OnSceenButton()
{
}

bool OnSceenButton::IsMousePointerOverButton(Coordinate mousePosition)
{
    if (mousePosition.x >= button_x_pos_ && mousePosition.x <= button_x_pos_end_ &&
        mousePosition.y >= button_y_pos_ && mousePosition.y <= button_y_pos_end_) {
        // We might want to update the Button State to reflect that it's been clicked on
        // how do we handle the DEP button that is a toggle to center the display versus 
        // a single click to 
        return true;
    }
    else {
        return false;
    }
}

void OnSceenButton::ToggleButtonState()
{   
    if (is_button_toggelable_ && buttonState_ == ButtonState::kButtonActive) {
        buttonState_ = ButtonState::kButtonInactive;
    }
    else if (is_button_toggelable_ && buttonState_ == ButtonState::kButtonInactive) {
        buttonState_ = ButtonState::kButtonActive;
    }
    else {
        // log error to log file
        PLOG_WARNING << "Button name " << button_name_ << "is toggelable but couldn't be set to the opposite state";
    }
}

ButtonState OnSceenButton::GetButtonState()
{
    return buttonState_;
}

void OnSceenButton::SetButtonText(std::string buttonText)
{
    button_screen_text_ = buttonText;
}

std::string OnSceenButton::GetButtonText()
{
    return button_screen_text_;
}

void OnSceenButton::HighlightText(bool flag)
{
    // Idea is to use this to reverse highlight the text on a button when it is clicked
    // not sure if that should be a flag that gets set here and then rendered somewhere else 
    // or if it should be added to the rendering queue here so it can be rendered later. Need to experiment

}
