#ifndef CONFIG_H
#define CONFIG_H

#include <SDL.h>
#include <SDL_ttf.h>


// Header file with set up info and constants for SQ Trainer

const int FPS = 30;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;


typedef struct {
	int x;
	int y;
} Coordinates;

// Useful distances for positioning UI elements
const int windowWidth = 730;
const int windowHeight = 900;
const Coordinates windowCenter{ windowWidth / 2, windowHeight / 2 };


// MFD attributes, numbers are pixels in MFD image
inline const char* mfdFileName = "./assets/images/playing_screen_727x720.png";
const int mfdImageWidth = 727;
const int mfdImageHeight = 720;
const int mfdScreenHeight = 638 - 83;
const int mfdScreenWidth = 631 - 83;
const int mfdPaddingLeft = (windowWidth / 2) - (mfdImageWidth / 2);
const int mfdPaddingTop = (windowHeight - mfdImageHeight) - 10;
const int mfdScreenTopInsideEdge = mfdPaddingTop + 83;
const int mfdScreenLeftInsideEdge = mfdPaddingLeft + 83;
const int mfdScreenBottomInsideEdge = mfdPaddingTop + 631;
const int mfdScreenRightInsideEdge = mfdPaddingLeft + 638;

const SDL_Color mfdGreenColour { 0, 175, 0 };
const SDL_Color mfdWhiteColour{ 255, 255, 255 };
const SDL_Color mfdBlueColour{ 0, 200, 200 };
const SDL_Color mfdBackground{ 0, 0, 0 };
const Coordinates mfdCenter{
			mfdScreenLeftInsideEdge + (mfdScreenWidth / 2),
			mfdScreenTopInsideEdge + (mfdScreenHeight / 2)
};


// MFD setup screen 
inline const char* mfdSetupFileName = "./assets/images/setup_screen_727x720.png";
inline const char* aceLevelFileName = "./assets/images/ace_level_319x177.png";
const int aceImageWidth = 319;
const int aceImageHeight = 177;
inline const char* cadetLevelFileName = "./assets/images/cadet_level324x149.png";
const int cadetImageWidth = 324;
const int cadetImageHeight = 149;
inline const char* recruitLevelFileName = "./assets/images/recruit_level317x123.png";
const int recruitImageWidth = 317;
const int recruitImageHeight = 123;
inline const char* rookieLevelFileName = "./assets/images/rookie_level_330x150.png";
const int rookieImageWidth = 330;
const int rookieImageHeight = 150;
inline const char* veteranLevelFileName = "./assets/images/veteran_level_318x170.png";
const int veteranImageWidth = 318;
const int veteranImageHeight = 170;


// Game start menu screen 
inline const char* gameStartMenuFileName = "./assets/images/main_menu_727x720.png";
inline const char* gameTitleFilename = "./assets/images/main_title_396x74.png";
const int gameTitleWidth = 396;
const int gameTitleHeight = 74;


// Distance rings attributes, needs to rotate so needs to have a center
inline const char* distRingsFileName = "./assets/images/distance_rings_496x512.png";
const int distRingsImageWidth = 496;
const int distRingsImageHeight = 512;
const int distRingsCenterOffset = distRingsImageWidth / 2;


// Aircraft  attributes
inline const char* aircraftFileName = "./assets/images/Aircraft_datum_42x47.png";
const int aircraftImageWidth = 42;
const int aircraftImageHeight = 47;


// Bullseye attributes
inline const char* bullsFileName = "./assets/images/bullseye_42x40.png";
const int bullsImageWidth = 42;
const int bullsImageHeight = 40;
const Coordinates bullsCenter{
			mfdScreenLeftInsideEdge + (bullsImageWidth / 2),
			mfdScreenBottomInsideEdge + (bullsImageHeight / 2)
};


// Blue bearing circle attribute, needs to rotate so needs to have a center
inline const char* bearingCircle = "./assets/images/blue_bearing_ring_82x87.png";
const int bearingCircleWidth = 82;
const int bearingCircleHeight = 87;
const Coordinates bearingCircleCenter{
			bearingCircleWidth / 2,
			bearingCircleHeight / 2
};


// Fonts used in game
inline const char* fontName2 = "C:/Windows/Fonts/Arial.ttf";
inline const char* fontName1 = "./assets/fonts/white-rabbit/whitrabt.ttf";
//inline const char* fontName1 = "./assets/fonts/digitgraphics/DigiGraphics.ttf";
//inline const char* fontName1 = "./assets/fonts/visitor-brk/visitor2.ttf";
const int fontSize1 = 16;
const int fontSize2 = 18;

// Start Button Text
const int startButtonLeftEdge = mfdPaddingLeft + 339;
const int startButtonRightEdge = mfdPaddingLeft + 391;
const int startButtonTopEdge = mfdPaddingTop + 653;
const int startButtonBottomEdge = mfdPaddingTop + 703;

// Setup Button Text
inline const char* setupButtonText = "./assets/images/SETUP_Text_44x11.png";
const int setupTextImageWidth = 44;
const int setupTextImageHeight = 11;
const int setupButtonLeftEdge = mfdPaddingLeft + 253;
const int setupButtonRightEdge = mfdPaddingLeft + 305;
const int setupButtonTopEdge = mfdPaddingTop + 652;
const int setupButtonBottomEdge = mfdPaddingTop + 704;

// Exit Button Text
inline const char* exitButtonText = "./assets/images/EXIT_Text_32x10.png";
const int exitTextImageWidth = 32;
const int exitTextImageHeight = 10;
const int exitButtonLeftEdge = mfdPaddingLeft + 424;
const int exitButtonRightEdge = mfdPaddingLeft + 471;
const int exitButtonTopEdge = mfdPaddingTop + 652;
const int exitButtonBottomEdge = mfdPaddingTop + 704;

// Recruit difficulty level Button
const int recruitButtonLeftEdge = mfdPaddingLeft + 13;
const int recruitButtonRightEdge = mfdPaddingLeft + 63;
const int recruitButtonTopEdge = mfdPaddingTop + 181;
const int recruitButtonBottomEdge = mfdPaddingTop + 230;

// Cadet difficulty level Button
const int cadetButtonLeftEdge = mfdPaddingLeft + 13;
const int cadetButtonRightEdge = mfdPaddingLeft + 63;
const int cadetButtonTopEdge = mfdPaddingTop + 256;
const int cadetButtonBottomEdge = mfdPaddingTop + 305;

// Rookie difficulty level Button
const int rookieButtonLeftEdge = mfdPaddingLeft + 13;
const int rookieButtonRightEdge = mfdPaddingLeft + 63;
const int rookieButtonTopEdge = mfdPaddingTop + 335;
const int rookieButtonBottomEdge = mfdPaddingTop + 383;

// Veteran difficulty level Button
const int veteranButtonLeftEdge = mfdPaddingLeft + 13;
const int veteranButtonRightEdge = mfdPaddingLeft + 63;
const int veteranButtonTopEdge = mfdPaddingTop + 410;
const int veteranButtonBottomEdge = mfdPaddingTop + 459;

// Ace difficulty level Button
const int aceButtonLeftEdge = mfdPaddingLeft + 13;
const int aceButtonRightEdge = mfdPaddingLeft + 63;
const int aceButtonTopEdge = mfdPaddingTop + 491;
const int aceButtonBottomEdge = mfdPaddingTop + 539;

// Distance to bullseye Text
inline const char* distanceText = "00";


// Bearing to bullseye Text
inline const char* bearingText = "000";




#endif // CONFIG_H