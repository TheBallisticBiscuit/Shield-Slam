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
#pragma region Bullet Initialize
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
#pragma endregion
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
	if (!lvl1Obstacle.initialize(graphics, ((GAME_WIDTH/2) - (OBSTACLE_WIDTH/2)), GAME_HEIGHT/2, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
#pragma region Initializing level 2
	if (!lvl2Obstacles[0].initialize(graphics, ((GAME_WIDTH/4) - (OBSTACLE_WIDTH/2)), GAME_HEIGHT/4, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	lvl2Obstacles[0].setActive(false);
	lvl2Obstacles[0].setVisible(false);
	if (!lvl2Obstacles[1].initialize(graphics, ((GAME_WIDTH/4) - (OBSTACLE_WIDTH/2)), (GAME_HEIGHT-(GAME_HEIGHT/4)), this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	lvl2Obstacles[1].setActive(false);
	lvl2Obstacles[1].setVisible(false);
	if (!lvl2Obstacles[2].initialize(graphics, ((GAME_WIDTH-GAME_WIDTH/4) - (OBSTACLE_WIDTH/2)), (GAME_HEIGHT-(GAME_HEIGHT/4)), this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	lvl2Obstacles[2].setActive(false);
	lvl2Obstacles[2].setVisible(false);
	if (!lvl2Obstacles[3].initialize(graphics, ((GAME_WIDTH-GAME_WIDTH/4) - (OBSTACLE_WIDTH/2)), GAME_HEIGHT/4, this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	lvl2Obstacles[3].setActive(false);
	lvl2Obstacles[3].setVisible(false);
#pragma endregion

	if (!score.initialize(graphics, 40, 1, 0, "OCR A Extended")) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Score Text"));
	if (!whoScored.initialize(graphics, 80, 1, 0, "Bauhaus 93"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DeathText"));
	if (!endGame.initialize(graphics, 70, 1, 0, "Bauhaus 93"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing EndGame Text"));
	if (!playAgain.initialize(graphics, 50, 0, 0, "OCR A Extended"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing PlayAgain Text"));

	audio->playCue(BACKGROUND_MUSIC);
	gameClock = 0;
	hardMode = false;
	insanityMode = false;
	deathMode = false;
	level = 0;
	gamePaused = false;
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
	if(gamePaused){
		if(input->isKeyDown(VK_SPACE)){
			gamePaused = false;
		}
		else{
			return;
		}
	}
	if(input->isKeyDown(VK_SPACE)){
		reset();
		player1.resetScore();
		player2.resetScore();
		level = 0;
	}
#pragma region Hard mode
	if(gameClock >= 7 && !hardMode){
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
	if(gameClock >= 15 && !insanityMode){
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
	if(gameClock >= 20 && !deathMode){
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
	lvl1Obstacle.update(frameTime);
	for(int i = 0; i < 4; i++){
		lvl2Obstacles[i].update(frameTime);
	}
	gameClock += frameTime;
	if(player1.isPlayerDead() || player2.isPlayerDead()){
		if(level == 2){
			gamePaused = true;
		}
		else{
			Sleep(3000);
			nextLevel();
		}
	}
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
				bullets[i].reflect(player1.getShieldDirection(), player1);
				if(!player1.isPlayerDead()){
					audio->playCue(LASER_SOUND);
				}
			}
			else{
				if (!player1.isPlayerDead()) {
					player2.addScore();
				}
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
				bullets[i].reflect(player2.getShieldDirection(), player2);
				if(!player2.isPlayerDead()){
					audio->playCue(LASER_SOUND);
				}
			}
			else{
				if (!player2.isPlayerDead()){
					player1.addScore();
				}
				player2.wasted();
				gameOver();
			}
		}
	}
#pragma endregion

#pragma region Obstacle Collision
	for(int i = 0; i < NUM_BULLETS; i++){
		if(bullets[i].collidesWith(lvl1Obstacle, collisionVector)){
			bullets[i].bounce(collisionVector, lvl1Obstacle);
			audio->playCue(LASER_SOUND);
		}
			for(int j = 0; j < 4; j++){
				if(bullets[i].collidesWith(lvl2Obstacles[j], collisionVector)){
					bullets[i].bounce(collisionVector, lvl2Obstacles[j]);
					audio->playCue(LASER_SOUND);
			}
		}
	}
	for(int j = 0; j < 4; j++){
		if(player1.collidesWith(lvl2Obstacles[j], collisionVector)){
			player1.bounce(collisionVector, lvl2Obstacles[j]);
		}
		if(player2.collidesWith(lvl2Obstacles[j], collisionVector)){
			player2.bounce(collisionVector, lvl2Obstacles[j]);
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
	lvl1Obstacle.draw();
	player1.draw();                            // add the spacejpo to the scene
	player2.draw();
	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].draw();
	}
	for(int i = 0; i < 4; i++){
		lvl2Obstacles[i].draw();
	}
#pragma region Screen Text
	score.setFontColor(graphicsNS::RED);
	score.print("Score: " + std::to_string(player1.getScore()), 40, 525);
	score.setFontColor(graphicsNS::B_GREEN);
	score.print("Score: " + std::to_string(player2.getScore()), 775, 525);


	if (level == 2) {
		if (player1.isPlayerDead() || player2.isPlayerDead()) {
			playAgain.setFontColor(graphicsNS::WHITE);
			if (player1.getScore() > 1) {
				endGame.setFontColor(graphicsNS::RED);
				endGame.print("RED PLAYER WINS!", 220, 225);
				playAgain.print("PRESS SPACE FOR A NEW GAME", 120, 375);
			}
			else if (player2.getScore() > 1) {
				endGame.setFontColor(graphicsNS::B_GREEN);
				endGame.print("GREEN PLAYER WINS!", 220, 225);
				playAgain.print("PRESS SPACE FOR A NEW GAME", 120, 375);
			}
		}
	}
	else {
		if (player1.isPlayerDead()){
			whoScored.setFontColor(graphicsNS::B_GREEN);
			whoScored.print("Green Player Score!", 200, 80);
		}
		if (player2.isPlayerDead()) {
			whoScored.setFontColor(graphicsNS::RED);
			whoScored.print("Red Player Score!", 230, 80);
		}
	}
#pragma endregion

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
	lvl1Obstacle.onLostDevice();

	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].onLostDevice();
	}
	for(int i = 0; i < 4; i++){
		lvl2Obstacles[i].onLostDevice();
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
	lvl1Obstacle.onResetDevice();

	for(int i = 0; i < NUM_BULLETS; i++){
		bullets[i].onResetDevice();
	}
	for(int i = 0; i < 4; i++){
		lvl2Obstacles[i].onResetDevice();
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
			bullets[i].setX(BULLET_SPAWN_4_X);
			bullets[i].setY(BULLET_SPAWN_4_Y);
			bullets[i].setVelocity(bullet4Start);
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

void Spacewar::nextLevel(){
	level++;
	if(level % 3 == 0){ //level 1
		lvl1Obstacle.activate();
		lvl1Obstacle.setVisible(true);
		for(int i = 0; i < 4; i++){
			lvl2Obstacles[i].setActive(false);
			lvl2Obstacles[i].setVisible(false);
		}
		reset();
	}
	else if(level % 3 == 1){ //level 2
		for(int i = 0; i < 4; i++){
			lvl2Obstacles[i].activate();
			lvl2Obstacles[i].setVisible(true);
		}
		lvl1Obstacle.setActive(false);
		lvl1Obstacle.setVisible(false);
		reset();
	}
	else if(level % 3 == 2){ //level 3
		lvl1Obstacle.activate();
		lvl1Obstacle.setVisible(true);
		for(int i = 0; i < 4; i++){
			lvl2Obstacles[i].activate();
			lvl2Obstacles[i].setVisible(true);
		}
		reset();
	}
}