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

#include "OnScreenButton.h"

using namespace cpv;

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable) {
    button_x_pos_ = xPos;
    button_y_pos_ = yPos;
    button_x_pos_end_ = xPosEnd;
    button_y_pos_end_ = yPosEnd;
    is_button_toggelable_ = toggelable;
}
 
OnSceenButton::~OnSceenButton()
{
}

bool OnSceenButton::IsMousePointerOverButton(Coordinates mousePosition)
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

void OnSceenButton::SetButtonState(ButtonState state)
{
    return;
}

ButtonState OnSceenButton::GetButtonState()
{
    return buttonState_;
}

void OnSceenButton::SetButtonText(std::string buttonText)
{
    button_text_ = buttonText;
}

std::string OnSceenButton::GetButtonText()
{
    return button_text_;
}

void OnSceenButton::HighlightText(bool flag)
{
    // Idea is to use this to reverse highlight the text on a button when it is clicked
    // not sure if that should be a flag that gets set here and then rendered somewhere else 
    // or if it should be added to the rendering queue here so it can be rendered later. Need to experiment

}
