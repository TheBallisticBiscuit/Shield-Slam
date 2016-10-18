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
	player1.initialize(graphics, "pictures\\redsoldiersheetupdate.png", 100, GAME_HEIGHT/2, 
		PLAYER1_RIGHT_KEY, PLAYER1_LEFT_KEY, PLAYER1_DOWN_KEY, PLAYER1_UP_KEY, PLAYER1_LOCK_KEY,
		this);
	player2.initialize(graphics, "pictures\\greensoldiersheetupdate.png", GAME_WIDTH-100, GAME_HEIGHT/2, 
		PLAYER2_RIGHT_KEY, PLAYER2_LEFT_KEY, PLAYER2_DOWN_KEY, PLAYER2_UP_KEY, PLAYER2_LOCK_KEY,
		this);

	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background texture"));
	if (!background.initialize(graphics, GAME_WIDTH, GAME_HEIGHT,0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background image"));
	background.setScale(BACKGROUND_SCALE);
	if (!obstacle.initialize(graphics, ((GAME_WIDTH/2) - (OBSTACLE_WIDTH/2)), GAME_HEIGHT/2, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	audio->playCue(BACKGROUND_MUSIC);
	//player1.setActive(false);
	//player2.setActive(false);
	//obstacle.setActive(false); 
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
	obstacle.update(frameTime);
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
		if (player1.itHitShield(collisionVector))
			bullet1.bounce(collisionVector, player1);
		else{
			player1.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();			
		}
	}	
	if (bullet2.collidesWith(player1, collisionVector))	{
		if (player1.itHitShield(collisionVector))
			bullet2.bounce(collisionVector, player1);
		else{
			player1.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();	
		}

	}
	if (bullet3.collidesWith(player1, collisionVector))	{
		if (player1.itHitShield(collisionVector))
			bullet3.bounce(collisionVector, player1);
		else{
			player1.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();	
		}
	}
	if (bullet4.collidesWith(player1, collisionVector))	{
		if(player1.itHitShield(collisionVector)){
			bullet4.bounce(collisionVector, player1);
		}
		else{
			player1.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();
		}
	}
#pragma endregion

#pragma region Player2 Collisions
	if (bullet1.collidesWith(player2, collisionVector))	{
		if (player2.itHitShield(collisionVector))
			bullet1.bounce(collisionVector, player2);
		else{
			player2.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();			
		}
	}	
	if (bullet2.collidesWith(player2, collisionVector))	{
		if (player2.itHitShield(collisionVector))
			bullet2.bounce(collisionVector, player2);
		else{
			player2.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();	
		}


	}
	if (bullet3.collidesWith(player2, collisionVector))	{
		if (player2.itHitShield(collisionVector))
			bullet3.bounce(collisionVector, player2);
		else{
			player2.wasted();
			bullet1.gameOver();
			bullet2.gameOver();
			bullet3.gameOver();
			bullet4.gameOver();	
		}
	}
	if (bullet4.collidesWith(player2, collisionVector))	{
		if(player2.itHitShield(collisionVector)){
			bullet4.bounce(collisionVector, player2);
		}
		else{
		player2.wasted();
		bullet1.gameOver();
		bullet2.gameOver();
		bullet3.gameOver();
		bullet4.gameOver();
		}
	}

#pragma endregion

#pragma region Obstacle Collision
	if(bullet1.collidesWith(obstacle, collisionVector)){
		bullet1.bounce(collisionVector, obstacle);
		audio->playCue(BOUNCE_SOUND);
	}
	if(bullet2.collidesWith(obstacle, collisionVector)){
		bullet2.bounce(collisionVector, obstacle);
		audio->playCue(BOUNCE_SOUND);
	}
	if(bullet3.collidesWith(obstacle, collisionVector)){
		bullet3.bounce(collisionVector, obstacle);
		audio->playCue(BOUNCE_SOUND);
	}
	if(bullet4.collidesWith(obstacle, collisionVector)){
		bullet4.bounce(collisionVector, obstacle);
		audio->playCue(BOUNCE_SOUND);
	}
	if(player1.collidesWith(obstacle, collisionVector)){
		player1.bounce(collisionVector, obstacle);
	}
	if(player2.collidesWith(obstacle, collisionVector)){
		player2.bounce(collisionVector, obstacle);
	}
#pragma endregion
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites
	background.draw();
	obstacle.draw();
	player1.draw();                            // add the spacejpo to the scene
	player2.draw();
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

	player1.onLostDevice();
	player2.onLostDevice();

	backgroundTexture.onLostDevice();
	obstacle.onLostDevice();

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

	player1.onResetDevice();
	player2.onResetDevice();

	backgroundTexture.onResetDevice();
	obstacle.onResetDevice();

	bullet1.onResetDevice();
	bullet2.onResetDevice();
	bullet3.onResetDevice();
	bullet4.onResetDevice();
	Game::resetAll();
	return;
}
