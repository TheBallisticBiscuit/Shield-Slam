// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#define BULLET_SCALE 0.5
#define BACKGROUND_SCALE 1.0

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bullet.h"
#include "player.h"
#include "obstacle.h"
#include "textDX.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
	Bullet bullets[16];
	Player player1;
	Player player2;
	TextureManager backgroundTexture;
	Image background;
	Obstacle lvl1Obstacle;
	Obstacle lvl2Obstacles[4];
	Obstacle obstacle;

	TextDX score;
	TextDX whoScored;
	TextDX endGame;
	TextDX playAgain;
	TextDX getReady;
	TextDX begin;

	enum LastDirection {left, right, up, down} greenLastDirection;
	LastDirection redLastDirection;
	bool keyDownLastFrame;
	bool keyDownThisFrame;
	float gameClock;
	bool hardMode;
	bool insanityMode;
	bool deathMode;
	int level;
	bool gamePaused;


public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void reset();
	void nextLevel();
};

#endif
