#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>
#include <SDL_ttf.h>

namespace cpv {

// Header file with set up info and constants

inline const char* log_path = "D:\\Development\\Projects\\C++\\SDL_Examples\\SA_Builder HSD Refactor\\logs\\log.txt";

const int kFPS = 10;
const int kmilliseconds_per_frame = 1000 / kFPS;

typedef struct {
	int x;
	int y;
} Coordinate;

// Useful distances for positioning UI elements
const int kWindowWidth = 730;
const int kWindowHeight = 900;
const Coordinate windowCenter{ kWindowWidth / 2, kWindowHeight / 2 };

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
const SDL_Color kMfdBlack{ 0, 0, 0 };
const Coordinate kMFDCenter{
			kMfdScreenLeftInsideEdge + (kMfdScreenWidth / 2),
			kMfdScreenTopInsideEdge + (kMfdScreenHeight / 2)
};

//const Coordinate kMFDCenter{ 360, 686 };
const Coordinate kRingsAndAircraftNonCentered{ 360, 695};

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
inline const char* kSATrainerStartScreenImage = "./assets/images/main_menu_727x720.png";
inline const char* kSATrainerStartScreenText = "./assets/images/main_title_396x74.png";
const int kGameTitleWidth = 396;
const int kGameTitleHeight = 74;

// HSD Distance rings attributes, needs to rotate so needs to have a center
inline const char* kHSD_DistRingsFileName = "./assets/images/distance_rings_646x646.png";
const int kHSDDistRingsImageWidth_ = 646;
const int kHSDDistRingsImageHeight_ = 646;
const int kDepOffset = 110;
const Coordinate distRingsCenter{
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
const Coordinate bearingCircleCenter{
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

// On Screen Buttons approach
const int kButtonWidth = 52;
const int kButtonHeight = 52;


const int kOSB1LeftEdge = kMfdPaddingLeft + 165;
const int kOSB1RightEdge = kOSB1LeftEdge + kButtonWidth;
const int kOSB1TopEdge = kMfdPaddingTop + 15;
const int kOSB1BottomEdge = kOSB1TopEdge + kButtonHeight;

const int kOSB7LeftEdge = kMfdPaddingLeft + 661;
const int kOSB7RightEdge = kOSB7LeftEdge + kButtonWidth;
const int kOSB7TopEdge = kMfdPaddingTop + 257;
const int kOSB7BottomEdge = kOSB7TopEdge + kButtonHeight;

const int kOSB8LeftEdge = kMfdPaddingLeft + 661;
const int kOSB8RightEdge = kOSB8LeftEdge + kButtonWidth;
const int kOSB8TopEdge = kMfdPaddingTop + 335;
const int kOSB8BottomEdge = kOSB8TopEdge + kButtonHeight;

const int kOSB9LeftEdge = kMfdPaddingLeft + 661;
const int kOSB9RightEdge = kOSB9LeftEdge + kButtonWidth;
const int kOSB9TopEdge = kMfdPaddingTop + 411;
const int kOSB9BottomEdge = kOSB9TopEdge + kButtonHeight;

const int kOSB12LeftEdge = kMfdPaddingLeft + 424;
const int kOSB12RightEdge = kOSB12LeftEdge + kButtonWidth;
const int kOSB12TopEdge = kMfdPaddingTop + 652;
const int kOSB12BottomEdge = kOSB12TopEdge + kButtonHeight;

const int kOSB13LeftEdge = kMfdPaddingLeft + 337;
const int kOSB13RightEdge = kOSB13LeftEdge + kButtonWidth;
const int kOSB13TopEdge = kMfdPaddingTop + 653;
const int kOSB13BottomEdge = kOSB13TopEdge + kButtonHeight;

const int kOSB14LeftEdge = kMfdPaddingLeft + 253;
const int kOSB14RightEdge = kOSB14LeftEdge + kButtonWidth;
const int kOSB14TopEdge = kMfdPaddingTop + 652;
const int kOSB14BottomEdge = kOSB14TopEdge + kButtonHeight;

const int kOSB16LeftEdge = kMfdPaddingLeft + 13;
const int kOSB16RightEdge = kOSB16LeftEdge + kButtonWidth;
const int kOSB16TopEdge = kMfdPaddingTop + 487;
const int kOSB16BottomEdge = kOSB16TopEdge + kButtonHeight;

const int kOSB17LeftEdge = kMfdPaddingLeft + 13;
const int kOSB17RightEdge = kOSB17LeftEdge + kButtonWidth;
const int kOSB17TopEdge = kMfdPaddingTop + 410;
const int kOSB17BottomEdge = kOSB17TopEdge + kButtonHeight;

const int kOSB18LeftEdge = kMfdPaddingLeft + 13;
const int kOSB18RightEdge = kOSB18LeftEdge + kButtonWidth;
const int kOSB18TopEdge = kMfdPaddingTop + 335;
const int kOSB18BottomEdge = kOSB18TopEdge + kButtonHeight;

const int kOSB19LeftEdge = kMfdPaddingLeft + 13;
const int kOSB19RightEdge = kOSB19LeftEdge + kButtonWidth;
const int kOSB19TopEdge = kMfdPaddingTop + 252;
const int kOSB19BottomEdge = kOSB19TopEdge + kButtonHeight;

const int kOSB20LeftEdge = kMfdPaddingLeft + 13;
const int kOSB20RightEdge = kOSB20LeftEdge + kButtonWidth;
const int kOSB20TopEdge = kMfdPaddingTop + 181;
const int kOSB20BottomEdge = kOSB20TopEdge + kButtonHeight;

// Button Text
inline const char* kSetupButtonText = "SETUP";
inline const char* kExitButtonText = "EXIT";
inline const char* kDepButtonText = "DEP";

// Distance to bullseye Text
inline const char* kDistanceText = "00";

// Bearing to bullseye Text
inline const char* kBearingText = "000";

}

#endif // CONFIG_H