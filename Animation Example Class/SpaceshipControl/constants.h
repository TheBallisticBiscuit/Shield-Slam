// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char JPO_IMAGE[]   = "pictures\\JPo Sheet.png"; //ship.png";   // spaceship

// window
const char CLASS_NAME[] = "Animation Example";
const char GAME_TITLE[] = "Animation Example";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels

const float GREEN_KNIGHT_ANIMATION_DELAY = 0.2f;    // time between frames of ship animation

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";

//Player 1 Cel
const int  GREEN_KNIGHT_COLS = 6;
const int  GREEN_KNIGHT_WIDTH = 384;
const int  GREEN_KNIGHT_HEIGHT = 256;
//Player 1 actions
const int GREEN_KNIGHT_LOOKING_RIGHT_START = 12;			//1st row
const int GREEN_KNIGHT_LOOKING_RIGHT_END = 12;
const int GREEN_KNIGHT_LOOKING_LEFT_START = 16;				//2nd row
const int GREEN_KNIGHT_LOOKING_LEFT_END = 16;
const int GREEN_KNIGHT_WALKING_RIGHT_START = 12;
const int GREEN_KNIGHT_WALKING_RIGHT_END = 16;
const int GREEN_KNIGHT_WALKING_LEFT_START = 18;
const int GREEN_KNIGHT_WALKING_LEFT_END = 22;
const int GREEN_KNIGHT_WALKING_UP_START = 6;
const int GREEN_KNIGHT_WALKING_UP_END = 11;
const int GREEN_KNIGHT_WALKING_DOWN_START = 0;
const int GREEN_KNIGHT_WALKING_DOWN_END = 5;

const float GREEN_KNIGHT_SPEED = 90.5f;

const int RED_KNIGHT_LOOKING_RIGHT_START = 12;			//1st row
const int RED_KNIGHT_LOOKING_RIGHT_END = 12;
const int RED_KNIGHT_LOOKING_LEFT_START = 16;				//2nd row
const int RED_KNIGHT_LOOKING_LEFT_END = 16;
const int RED_KNIGHT_WALKING_RIGHT_START = 12;
const int RED_KNIGHT_WALKING_RIGHT_END = 16;
const int RED_KNIGHT_WALKING_LEFT_START = 18;
const int RED_KNIGHT_WALKING_LEFT_END = 22;
const int RED_KNIGHT_WALKING_UP_START = 6;
const int RED_KNIGHT_WALKING_UP_END = 11;
const int RED_KNIGHT_WALKING_DOWN_START = 0;
const int RED_KNIGHT_WALKING_DOWN_END = 5;

const float RED_KNIGHT_SPEED = 90.5f;

const int  RED_KNIGHT_COLS = 6;
const int  RED_KNIGHT_WIDTH = 384;
const int  RED_KNIGHT_HEIGHT = 256;

const float RED_KNIGHT_ANIMATION_DELAY = 0.2f;

const float BULLET_SPEED = 200.0f;
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR GREEN_KNIGHT_LEFT_KEY    = VK_LEFT;     // left arrow
const UCHAR GREEN_KNIGHT_RIGHT_KEY   = VK_RIGHT;    // right arrow
const UCHAR GREEN_KNIGHT_UP_KEY      = VK_UP;       // up arrow
const UCHAR GREEN_KNIGHT_DOWN_KEY    = VK_DOWN;     // down arrow

const UCHAR RED_KNIGHT_LEFT_KEY = 0x41;
const UCHAR RED_KNIGHT_RIGHT_KEY = 0x44;
const UCHAR RED_KNIGHT_UP_KEY = 0x57;
const UCHAR RED_KNIGHT_DOWN_KEY = 0x53;
#endif