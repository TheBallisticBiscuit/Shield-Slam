// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Move spacejpo with arrow keys.
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError
	bullet1.initialize(graphics, 0, 0, 1, 1, this);
	bullet2.initialize(graphics, GAME_WIDTH - 75, GAME_HEIGHT - 75, -1, -1, this);
	bullet3.initialize(graphics, GAME_WIDTH - 75, 0, -1, 1, this);
	bullet4.initialize(graphics, 0, GAME_HEIGHT - 75, 1, -1, this);
	player1.initialize(graphics, "pictures\\redsoldiersheetupdate.png", GAME_WIDTH/4, GAME_HEIGHT/2, 
		PLAYER1_RIGHT_KEY, PLAYER1_LEFT_KEY, PLAYER1_DOWN_KEY, PLAYER1_UP_KEY,
		this);
	player2.initialize(graphics, "pictures\\greensoldiersheetupdate.png", GAME_WIDTH/4+100, GAME_HEIGHT/2, 
		PLAYER2_RIGHT_KEY, PLAYER2_LEFT_KEY, PLAYER2_DOWN_KEY, PLAYER2_UP_KEY,
		this);

	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background texture"));
	if (!background.initialize(graphics, 800,480,0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background image"));
	background.setScale(BACKGROUND_SCALE);

	audio->playCue(BACKGROUND_MUSIC);
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{

	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}


	player1.update(frameTime);
	player2.update(frameTime);
	bullet1.update(frameTime);
	bullet2.update(frameTime);
	bullet3.update(frameTime);
	bullet4.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
	VECTOR2 collisionVector;

#pragma region Player1Collisions
	if (bullet1.collidesWith(player1, collisionVector))	{
		player1.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();
	}	
	if (bullet2.collidesWith(player1, collisionVector))	{
		player1.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();

	}
	if (bullet3.collidesWith(player1, collisionVector))	{
		player1.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();

	}
	if (bullet4.collidesWith(player1, collisionVector))	{
		player1.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();
	}
#pragma endregion

#pragma region Player2 Collisions
	if (bullet1.collidesWith(player2, collisionVector))	{
		player2.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();
	}	
	if (bullet2.collidesWith(player2, collisionVector))	{
		player2.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();

	}
	if (bullet3.collidesWith(player2, collisionVector))	{
		player2.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();

	}
	if (bullet4.collidesWith(player2, collisionVector))	{
		player2.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();
	}

	//if (bullet1.collidesWith(player2, collisionVector))	{
	//	paused = true;
	//}	
	//if (bullet2.collidesWith(player2, collisionVector))	{
	//	paused = true;
	//}
	//if (bullet3.collidesWith(player2, collisionVector))	{
	//	paused = true;
	//}
	//if (bullet4.collidesWith(player2, collisionVector))	{
	//	paused = true;
	//}
#pragma endregion

}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites
//<<<<<<< HEAD
	background.draw();
	player1.draw();                            // add the spacejpo to the scene
	player2.draw();
//=======
//>>>>>>> origin/Audio_&_Background
	bullet1.draw();
	bullet2.draw();
	bullet3.draw();
	bullet4.draw();
	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	Game::releaseAll();
//<<<<<<< HEAD
	player1.onLostDevice();
	player2.onLostDevice();
//=======
	backgroundTexture.onLostDevice();
//>>>>>>> origin/Audio_&_Background
	bullet1.onLostDevice();
	bullet2.onLostDevice();
	bullet3.onLostDevice();
	bullet4.onLostDevice();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
//<<<<<<< HEAD
	player1.onResetDevice();
	player2.onResetDevice();
//=======
	backgroundTexture.onResetDevice();
	greenKnightTexture.onResetDevice();
	redKnightTexture.onResetDevice();
//>>>>>>> origin/Audio_&_Background
	bullet1.onResetDevice();
	bullet2.onResetDevice();
	bullet3.onResetDevice();
	bullet4.onResetDevice();
	Game::resetAll();
	return;
}
