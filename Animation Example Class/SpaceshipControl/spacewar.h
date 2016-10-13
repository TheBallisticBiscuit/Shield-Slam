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

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
	Bullet bullet1;
	Bullet bullet2;
	Bullet bullet3;
	Bullet bullet4;
//<<<<<<< HEAD
	Player player1;
	Player player2;
//=======
    TextureManager greenKnightTexture;     // ship texture
    Image   greenKnight;  // ship image
	TextureManager redKnightTexture;
	Image redKnight;
	TextureManager backgroundTexture;
	Image background;
	enum LastDirection {left, right, up, down} greenLastDirection;
	LastDirection redLastDirection;
//>>>>>>> origin/Audio_&_Background
	bool keyDownLastFrame;
	bool keyDownThisFrame;


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
};

#endif
