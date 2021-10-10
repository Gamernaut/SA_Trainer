#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>
#include <SDL_ttf.h>

namespace cpv {

// Header file with set up info and constants for SQ Trainer

const int kFPS = 10;
const int kmilliseconds_per_frame = 1000 / kFPS;

typedef struct {
	int x;
	int y;
} Coordinates;

// Useful distances for positioning UI elements
const int kWindowWidth = 730;
const int kWindowHeight = 900;
const Coordinates windowCenter{ kWindowWidth / 2, kWindowHeight / 2 };

// MFD attributes, numbers are pixels in MFD image
inline const char* kMfdFileName = "./assets/images/MFD_Frame.png";
const int kMfdImageWidth = 727;
const int kMfdImageHeight = 720;
const int kMfdScreenHeight = 638 - 83;
const int kMfdScreenWidth = 631 - 83;
const int kMfdPaddingLeft = (kWindowWidth / 2) - (kMfdImageWidth / 2);
const int kMfdPaddingTop = (kWindowHeight - kMfdImageHeight);
const int kMfdScreenTopInsideEdge = kMfdPaddingTop + 83;
const int kMfdScreenLeftInsideEdge = kMfdPaddingLeft + 83;
const int kMfdScreenBottomInsideEdge = kMfdPaddingTop + 631;
const int kMfdScreenRightInsideEdge = kMfdPaddingLeft + 638;
inline const char* kGreenPieSlice = "./assets/images/green_pie_slice_165x684.png";
inline const char* kRedPieSlice = "./assets/images/red_pie_slice_165x684.png";
inline const char* kRedRectangle = "./assets/images/red_rectangle_64x64.png";
inline const char* kGreenRectangle = "./assets/images/green_rectangle_64x64.png";

const SDL_Color kMfdGreenColour{ 0, 175, 0 };
const SDL_Color kMfdWhiteColour{ 255, 255, 255 };
const SDL_Color kMfdBlueColour{ 0, 200, 200 };
const SDL_Color kMfdBackground{ 0, 0, 0 };
const Coordinates kMFDCenter{
			kMfdScreenLeftInsideEdge + (kMfdScreenWidth / 2),
			kMfdScreenTopInsideEdge + (kMfdScreenHeight / 2)
};

// MFD setup screen
inline const char* kMfdSetupFileName = "./assets/images/setup_screen_727x720.png";
inline const char* kAceLevelFileName = "./assets/images/ace_level_319x177.png";
const int kAceImageWidth = 319;
const int kAceImageHeight = 177;
inline const char* kCadetLevelFileName = "./assets/images/cadet_level324x149.png";
const int kCadetImageWidth = 324;
const int kCadetImageHeight = 149;
inline const char* kRecruitLevelFileName = "./assets/images/recruit_level317x123.png";
const int kRecruitImageWidth = 317;
const int kRecruitImageHeight = 123;
inline const char* kRookieLevelFileName = "./assets/images/rookie_level_330x150.png";
const int kRookieImageWidth = 330;
const int kRookieImageHeight = 150;
inline const char* kVeteranLevelFileName = "./assets/images/veteran_level_318x170.png";
const int kVeteranImageWidth = 318;
const int kVeteranImageHeight = 170;

// Game start menu screen
inline const char* kGameStartMenuFileName = "./assets/images/main_menu_727x720.png";
inline const char* kGameTitleFilename = "./assets/images/main_title_396x74.png";
const int kGameTitleWidth = 396;
const int kGameTitleHeight = 74;

// Distance rings attributes, needs to rotate so needs to have a center
inline const char* kDistRingsFileName = "./assets/images/distance_rings_646x646.png";
const int kDistRingsImageWidth = 646;
const int kDistRingsImageHeight = 646;
const int kDepOffset = 110;
const Coordinates distRingsCenter{
			kMfdScreenLeftInsideEdge + (kMfdScreenWidth / 2),
			kMfdScreenTopInsideEdge + (kMfdScreenHeight / 2)
};

// Aircraft  attributes
inline const char* kAircraftFileName = "./assets/images/Aircraft_datum_42x47.png";
const int kAircraftImageWidth = 42;
const int kAircraftImageHeight = 47;

// Bullseye attributes
inline const char* kBullsFileName = "./assets/images/bullseye_28x28.png";
const int kBullsImageWidth = 28;
const int kBullsImageHeight = 28;

// Blue bearing circle attribute, needs to rotate so needs to have a center
inline const char* kBearingCircle = "./assets/images/blue_bearing_ring_55x60.png";
const int kBearingCircleWidth = 55;
const int kBearingCircleHeight = 60;
inline const char* kBearingPointer = "./assets/images/bearing_pointer_53x65.png";
const Coordinates bearingCircleCenter{
			kBearingCircleWidth / 2,
			kBearingCircleHeight / 2
};

// Fonts used in game
inline const char* kFontName2 = "C:/Windows/Fonts/Arial.ttf";
inline const char* kFontName = "./assets/fonts/white-rabbit/whitrabt.ttf";
//inline const char* fontName1 = "./assets/fonts/digitgraphics/DigiGraphics.ttf";
//inline const char* fontName1 = "./assets/fonts/visitor-brk/visitor2.ttf";
const int kFontSize1 = 16;
const int kFontSize2 = 18;

// Start Button Text
const int kStartButtonLeftEdge = kMfdPaddingLeft + 339;
const int kStartButtonRightEdge = kMfdPaddingLeft + 391;
const int kStartButtonTopEdge = kMfdPaddingTop + 653;
const int kStartButtonBottomEdge = kMfdPaddingTop + 703;

// Setup Button Text
//inline const char* kSetupButtonText = "./assets/images/SETUP_Text_44x11.png";
inline const char* kSetupButtonText = "SETUP";
const int kSetupTextImageWidth = 44;
const int kSetupTextImageHeight = 11;
const int kSetupButtonLeftEdge = kMfdPaddingLeft + 253;
const int kSetupButtonRightEdge = kMfdPaddingLeft + 305;
const int kSetupButtonTopEdge = kMfdPaddingTop + 652;
const int kSetupButtonBottomEdge = kMfdPaddingTop + 704;

// Exit Button Text
//inline const char* kExitButtonText = "./assets/images/EXIT_Text_32x10.png";
inline const char* kExitButtonText = "EXIT";
const int kExitTextImageWidth = 32;
const int kExitTextImageHeight = 10;
const int kExitButtonLeftEdge = kMfdPaddingLeft + 424;
const int kExitButtonRightEdge = kMfdPaddingLeft + 471;
const int kExitButtonTopEdge = kMfdPaddingTop + 652;
const int kExitButtonBottomEdge = kMfdPaddingTop + 704;

// Recruit difficulty level Button
const int kRecruitButtonLeftEdge = kMfdPaddingLeft + 13;
const int kRecruitButtonRightEdge = kMfdPaddingLeft + 63;
const int kRecruitButtonTopEdge = kMfdPaddingTop + 181;
const int kRecruitButtonBottomEdge = kMfdPaddingTop + 230;

// Cadet difficulty level Button
const int kCadetButtonLeftEdge = kMfdPaddingLeft + 13;
const int kCadetButtonRightEdge = kMfdPaddingLeft + 63;
const int kCadetButtonTopEdge = kMfdPaddingTop + 256;
const int kCadetButtonBottomEdge = kMfdPaddingTop + 305;

// Rookie difficulty level Button
const int kRookieButtonLeftEdge = kMfdPaddingLeft + 13;
const int kRookieButtonRightEdge = kMfdPaddingLeft + 63;
const int kRookieButtonTopEdge = kMfdPaddingTop + 335;
const int kRookieButtonBottomEdge = kMfdPaddingTop + 383;

// Veteran difficulty level Button
const int kVeteranButtonLeftEdge = kMfdPaddingLeft + 13;
const int kVeteranButtonRightEdge = kMfdPaddingLeft + 63;
const int kVeteranButtonTopEdge = kMfdPaddingTop + 410;
const int kVeteranButtonBottomEdge = kMfdPaddingTop + 459;

// Ace difficulty level Button
const int kAceButtonLeftEdge = kMfdPaddingLeft + 13;
const int kAceButtonRightEdge = kMfdPaddingLeft + 63;
const int kAceButtonTopEdge = kMfdPaddingTop + 491;
const int kAceButtonBottomEdge = kMfdPaddingTop + 539;

// Distance to bullseye Text
inline const char* kDistanceText = "00";

// Bearing to bullseye Text
inline const char* kBearingText = "000";

}

#endif // CONFIG_H