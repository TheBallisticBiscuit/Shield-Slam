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
	for(int i = 0; i < NUM_BULLETS; i++){
		if(i % 4 == 0){
			bullets[i].initialize(graphics,BULLET_SPAWN_1_X, BULLET_SPAWN_1_Y, 1, 1, this);
		}
		else if(i % 4 == 3){
			bullets[i].initialize(graphics, BULLET_SPAWN_2_X, BULLET_SPAWN_2_Y, -1, -1, this);
		}
		else if(i % 4 == 2){
			bullets[i].initialize(graphics, BULLET_SPAWN_3_X, BULLET_SPAWN_3_Y, -1, 1, this);
		}
		else if (i % 4 == 1){
			bullets[i].initialize(graphics, BULLET_SPAWN_4_X, BULLET_SPAWN_4_Y, 1, -1, this);
		}
		if(i >= 4){
			bullets[i].setActive(false);
			bullets[i].setVisible(false);
		}
	}
	player1.initialize(graphics, "pictures\\redsoldiersheetupdate.png", PLAYER1_SPAWN_X, GAME_HEIGHT/2, 
		PLAYER1_RIGHT_KEY, PLAYER1_LEFT_KEY, PLAYER1_DOWN_KEY, PLAYER1_UP_KEY, PLAYER1_LOCK_KEY,
		this);
	player2.initialize(graphics, "pictures\\greensoldiersheetupdate.png", PLAYER2_SPAWN_X, GAME_HEIGHT/2, 
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
	gameClock = 0;
	hardMode = false;
	insanityMode = false;
	deathMode = false;
	player1.setActive(false);
	player2.setActive(false);
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
	if(input->isKeyDown(VK_SPACE)){
		reset();
	}
#pragma region Hard mode
	if(gameClock >= 10 && !hardMode){
		VECTOR2 bullet1Start(1, 1);
		VECTOR2 bullet2Start(-1, -1);
		VECTOR2 bullet3Start(-1, 1);
		VECTOR2 bullet4Start(1, -1);
		for(int i = 4; i < 8; i++){		
			if(i % 4 == 0){
				bullets[i].setX(BULLET_SPAWN_1_X);
				bullets[i].setY(BULLET_SPAWN_1_Y);
				bullets[i].setVelocity(bullet1Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 1){
				bullets[i].setX(BULLET_SPAWN_2_X);
				bullets[i].setY(BULLET_SPAWN_2_Y);
				bullets[i].setVelocity(bullet2Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 2){
				bullets[i].setX(BULLET_SPAWN_3_X);
				bullets[i].setY(BULLET_SPAWN_3_Y);
				bullets[i].setVelocity(bullet3Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 3){
				bullets[i].setX(BULLET_SPAWN_4_X);
				bullets[i].setY(BULLET_SPAWN_4_Y);
				bullets[i].setVelocity(bullet4Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
		}
		hardMode++;
	}
#pragma endregion

#pragma region Insanity mode
		if(gameClock >= 20 && !insanityMode){
		VECTOR2 bullet1Start(1, 1);
		VECTOR2 bullet2Start(-1, -1);
		VECTOR2 bullet3Start(-1, 1);
		VECTOR2 bullet4Start(1, -1);
		for(int i = 8; i < 12; i++){		
			if(i % 4 == 0){
				bullets[i].setX(BULLET_SPAWN_1_X);
				bullets[i].setY(BULLET_SPAWN_1_Y);
				bullets[i].setVelocity(bullet1Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 1){
				bullets[i].setX(BULLET_SPAWN_2_X);
				bullets[i].setY(BULLET_SPAWN_2_Y);
				bullets[i].setVelocity(bullet2Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 2){
				bullets[i].setX(BULLET_SPAWN_3_X);
				bullets[i].setY(BULLET_SPAWN_3_Y);
				bullets[i].setVelocity(bullet3Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 3){
				bullets[i].setX(BULLET_SPAWN_4_X);
				bullets[i].setY(BULLET_SPAWN_4_Y);
				bullets[i].setVelocity(bullet4Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
		}
		insanityMode++;
	}
#pragma endregion

#pragma region Death mode
		if(gameClock >= 30 && !deathMode){
		VECTOR2 bullet1Start(1, 1);
		VECTOR2 bullet2Start(-1, -1);
		VECTOR2 bullet3Start(-1, 1);
		VECTOR2 bullet4Start(1, -1);
		for(int i = 12; i < 16; i++){		
			if(i % 4 == 0){
				bullets[i].setX(BULLET_SPAWN_1_X);
				bullets[i].setY(BULLET_SPAWN_1_Y);
				bullets[i].setVelocity(bullet1Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 1){
				bullets[i].setX(BULLET_SPAWN_2_X);
				bullets[i].setY(BULLET_SPAWN_2_Y);
				bullets[i].setVelocity(bullet2Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 2){
				bullets[i].setX(BULLET_SPAWN_3_X);
				bullets[i].setY(BULLET_SPAWN_3_Y);
				bullets[i].setVelocity(bullet3Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
			else if(i % 4 == 3){
				bullets[i].setX(BULLET_SPAWN_4_X);
				bullets[i].setY(BULLET_SPAWN_4_Y);
				bullets[i].setVelocity(bullet4Start);
				bullets[i].activate();
				bullets[i].setVisible(true);
			}
		}
		deathMode++;
	}
#pragma endregion
	player1.update(frameTime);
	player2.update(frameTime);
	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].update(frameTime);
	}
	obstacle.update(frameTime);
	gameClock += frameTime;
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
	for(int i = 0; i < NUM_BULLETS; i++){
		if(bullets[i].collidesWith(player1, collisionVector)){
			if (player1.itHitShield(collisionVector)){
				bullets[i].bounce(collisionVector, player1);
				if(!player1.isPlayerDead()){
					audio->playCue(LASER_SOUND);
				}
			}
			else{
				player1.wasted();
				gameOver();
			}
		}
	}
#pragma endregion

#pragma region Player2 Collisions
	for(int i = 0; i < NUM_BULLETS; i++){
		if(bullets[i].collidesWith(player2, collisionVector)){
			if (player2.itHitShield(collisionVector)){
				bullets[i].bounce(collisionVector, player2);
				if(!player2.isPlayerDead()){
					audio->playCue(LASER_SOUND);
				}
			}
			else{
				player2.wasted();
				gameOver();
			}
		}
	}
#pragma endregion

#pragma region Obstacle Collision
	for(int i = 0; i < NUM_BULLETS; i++){
		if(bullets[i].collidesWith(obstacle, collisionVector)){
			bullets[i].bounce(collisionVector, obstacle);
			audio->playCue(LASER_SOUND);
		}
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
	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].draw();
	}
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

	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].onLostDevice();
	}
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

	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].onResetDevice();
	}
	Game::resetAll();
	return;
}

void Spacewar::reset(){
	VECTOR2 bullet1Start(1, 1);
	VECTOR2 bullet2Start(-1, -1);
	VECTOR2 bullet3Start(-1, 1);
	VECTOR2 bullet4Start(1, -1);
	for(int i = 0; i < NUM_BULLETS; i++){
		if(i % 4 == 0){
			bullets[i].setX(BULLET_SPAWN_1_X);
			bullets[i].setY(BULLET_SPAWN_1_Y);
			bullets[i].setVelocity(bullet1Start);
		}
		else if(i % 4 == 1){
			bullets[i].setX(BULLET_SPAWN_2_X);
			bullets[i].setY(BULLET_SPAWN_2_Y);
			bullets[i].setVelocity(bullet2Start);
		}
		else if(i % 4 == 2){
			bullets[i].setX(BULLET_SPAWN_3_X);
			bullets[i].setY(BULLET_SPAWN_3_Y);
			bullets[i].setVelocity(bullet3Start);
		}
		else if(i % 4 == 3){
			bullets[i].setX(BULLET_SPAWN_3_X);
			bullets[i].setY(BULLET_SPAWN_3_Y);
			bullets[i].setVelocity(bullet3Start);
		}
		if(i >= 4){
			bullets[i].setActive(false);
			bullets[i].setVisible(false);
		}
	}
	gameClock = 0;
	hardMode = false;
	insanityMode = false;
	deathMode = false;

	//Player resets
	player1.respawn(PLAYER1_SPAWN_X);
	player2.respawn(PLAYER2_SPAWN_X);
}

void Spacewar::gameOver(){
	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].gameOver();
	}
}
