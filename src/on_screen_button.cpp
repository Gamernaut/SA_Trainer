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
#include "on_screen_button.h"

using namespace cpv;

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name)
{
    PLOG_INFO << "Button " << button_name_ << "created";

    button_x_pos_ = xPos;
    button_y_pos_ = yPos;
    button_x_pos_end_ = xPosEnd;
    button_y_pos_end_ = yPosEnd;
    is_button_toggelable_ = toggelable;
    button_name_ = button_name;
}

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text)
{
    PLOG_INFO << "Button " << button_name_ << "created with onscreen text";

    button_x_pos_ = xPos;
    button_y_pos_ = yPos;
    button_x_pos_end_ = xPosEnd;
    button_y_pos_end_ = yPosEnd;
    is_button_toggelable_ = toggelable;
    button_name_ = button_name;
    button_onscreen_text_ = onscreen_text;

}

 
OnSceenButton::~OnSceenButton()
{
}


void OnSceenButton::SetButtonName(std::string button_name_text)
{
    PLOG_VERBOSE << "Button " << button_name_ << " name changed to " << button_name_;

    button_name_ = button_name_text;
}


std::string OnSceenButton::GetButtonName()
{
    return button_name_;
}


void OnSceenButton::SetOnScreenText(std::string onscreen_text)
{
    PLOG_VERBOSE << "Button " << button_name_ << " On screen text changed to " << button_onscreen_text_;

    button_onscreen_text_ = onscreen_text;
}


std::string OnSceenButton::GetOnScreenText()
{
    return button_onscreen_text_;
}


void OnSceenButton::HighlightOnScreenText(bool flag)
{
    // Idea is to use this to reverse highlight the text on a button when it is clicked
    // not sure if that should be a flag that gets set here and then rendered somewhere else 
    // or if it should be added to the rendering queue here so it can be rendered later. Need to experiment

}


bool OnSceenButton::IsMousePointerOverButton(int mouse_x, int mouse_y)
{
    if (mouse_x >= button_x_pos_ && mouse_x <= button_x_pos_end_ &&
        mouse_y >= button_y_pos_ && mouse_y <= button_y_pos_end_) {
        // We might want to update the Button State to reflect that it's been clicked on
        // how do we handle the DEP button that is a toggle to center the display versus 
        // a single click to 
        PLOG_VERBOSE << "Button " << button_name_ << " mouse clicked inside button boundaries";
        return true;
    }
    else {
        PLOG_VERBOSE << "Button " << button_name_ << " mouse clicked outside button boundaries";
        return false;
    }
}


void OnSceenButton::ToggleButtonState()
{   
    if (is_button_toggelable_ && buttonState_ == ButtonState::kButtonActive) {
        buttonState_ = ButtonState::kButtonInactive;
        PLOG_VERBOSE << "Button " << button_name_ << " toggle button state set to Inactive";
    }
    else if (is_button_toggelable_ && buttonState_ == ButtonState::kButtonInactive) {
        buttonState_ = ButtonState::kButtonActive;
        PLOG_VERBOSE << "Button " << button_name_ << " toggle button state set to Active";
    }
    else {
        // log error to log file
        PLOG_WARNING << "Button name " << button_name_ << "is toggelable but couldn't be set to the opposite state";
    }
}


ButtonState OnSceenButton::GetButtonToggeledState()
{
    return buttonState_;
}


void OnSceenButton::DrawOutline(SDL_Renderer* renderer) {

    // Add the 4 draw calls to the render stack to outline the button
    SDL_Point points[5] = {
        {button_x_pos_ , button_y_pos_},
        {button_x_pos_end_ , button_y_pos_},
        {button_x_pos_end_ , button_y_pos_end_},
        {button_x_pos_, button_y_pos_end_},
        {button_x_pos_ , button_y_pos_}
    };

    // Don't call RenderClear or SDL_RenderPresent here
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(renderer, points, 5);

}