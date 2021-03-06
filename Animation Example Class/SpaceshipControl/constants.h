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
//<<<<<<< HEAD
//=======
const char BACKGROUND_IMAGE[] = "pictures\\Background1.png";
//>>>>>>> origin/Audio_&_Background

// window
const char CLASS_NAME[] = "Shield Slam";
const char GAME_TITLE[] = "Shield Slam";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1000;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels

const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames of ship animation

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\WavesExample1.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\SoundsExample1.xsb";

const char BACKGROUND_MUSIC[] = "BackgroundMusic2";
const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";
const char BOUNCE_SOUND[] = "BounceSound";
const char LASER_SOUND[] = "LaserSound";
const char WALL_HIT[] = "WallHit2";
const char DEATH[] = "Death";

//Player 1 Cel
const int  PLAYER_COLS = 6;
const int  PLAYER_WIDTH = 384/6;
const int  PLAYER_HEIGHT = 256/4;
//Player 1 actions
const int PLAYER_LOOKING_RIGHT_START = 12;			//1st row
const int PLAYER_LOOKING_RIGHT_END = 12;
const int PLAYER_LOOKING_LEFT_START = 16;				//2nd row
const int PLAYER_LOOKING_LEFT_END = 16;
const int PLAYER_WALKING_RIGHT_START = 12;
const int PLAYER_WALKING_RIGHT_END = 16;
const int PLAYER_WALKING_LEFT_START = 18;
const int PLAYER_WALKING_LEFT_END = 22;
const int PLAYER_WALKING_UP_START = 6;
const int PLAYER_WALKING_UP_END = 11;
const int PLAYER_WALKING_DOWN_START = 0;
const int PLAYER_WALKING_DOWN_END = 5;

//Shield 
const int SHIELD_WIDTH = 256;
const int SHIELD_HEIGHT = 76;

const float PLAYER_SPEED = 120.5f;

//Bullet
const float BULLET_SPEED = 400.0f;
const float BULLET_SCALING = 0.6f;

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
const UCHAR PLAYER2_LEFT_KEY    = VK_LEFT;     // left arrow
const UCHAR PLAYER2_RIGHT_KEY   = VK_RIGHT;    // right arrow
const UCHAR PLAYER2_UP_KEY      = VK_UP;       // up arrow
const UCHAR PLAYER2_DOWN_KEY    = VK_DOWN;     // down arrow
const UCHAR PLAYER2_LOCK_KEY	= 0x11;

const UCHAR PLAYER1_LEFT_KEY = 0x41;
const UCHAR PLAYER1_RIGHT_KEY = 0x44;
const UCHAR PLAYER1_UP_KEY = 0x57;
const UCHAR PLAYER1_DOWN_KEY = 0x53;
const UCHAR PLAYER1_LOCK_KEY = 0x10;

const float SHIELD_SCALE = 0.24;

const float OBSTACLE_SCALE = 1.0f;
const float OBSTACLE_HEIGHT = 649/11;
const float OBSTACLE_WIDTH = 236;
const float OBSTACLE_ANIMATION_DELAY = 0.1f;

//Spawn points:
const float BULLET_SPAWN_1_X = 1;
const float BULLET_SPAWN_1_Y = 1;
const float BULLET_SPAWN_2_X = GAME_WIDTH - 75;
const float BULLET_SPAWN_2_Y = GAME_HEIGHT - 75;
const float BULLET_SPAWN_3_X = GAME_WIDTH-75;
const float BULLET_SPAWN_3_Y = 1;
const float BULLET_SPAWN_4_X = 1;
const float BULLET_SPAWN_4_Y = GAME_HEIGHT-75;
const int NUM_BULLETS = 16;
//player spawns
const float PLAYER1_SPAWN_X = 100;
const float PLAYER2_SPAWN_X = GAME_WIDTH-100;
#endif