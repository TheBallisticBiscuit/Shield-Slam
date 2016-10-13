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
	if (!backgroundTexture.initialize(graphics, BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background texture"));
	if (!background.initialize(graphics, 640,480,0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Background image"));
	background.setScale(BACKGROUND_SCALE);

	audio->playCue(BACKGROUND_MUSIC);

	bullet1.initialize(graphics, 0, 0, 1, 1);
	bullet2.initialize(graphics, GAME_WIDTH - 75, GAME_HEIGHT - 75, -1, -2);
	bullet3.initialize(graphics, GAME_WIDTH - 75, 0, -2, 1);
	bullet4.initialize(graphics, 0, GAME_HEIGHT - 75, 1, -3);
	if (!greenKnightTexture.initialize(graphics,"pictures\\greensoldiersheetupdate.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1 texture"));

	if (!greenKnight.initialize(graphics, 256/4, 384/6, GREEN_KNIGHT_COLS, &greenKnightTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1"));
	greenKnight.setX(GAME_WIDTH/4);                    // start above and left of planet
	greenKnight.setY(GAME_HEIGHT/2);
	greenKnight.setFrames(GREEN_KNIGHT_LOOKING_RIGHT_START, GREEN_KNIGHT_LOOKING_RIGHT_END);   // animation frames
	greenKnight.setCurrentFrame(GREEN_KNIGHT_LOOKING_RIGHT_START);     // starting frame
	greenKnight.setFrameDelay(GREEN_KNIGHT_ANIMATION_DELAY);

	if (!redKnightTexture.initialize(graphics,"pictures\\redsoldiersheetupdate.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 2 texture"));

	if (!redKnight.initialize(graphics, 256/4, 384/6, RED_KNIGHT_COLS, &redKnightTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 2"));
	redKnight.setX(GAME_WIDTH/2);                    // start above and left of planet
	redKnight.setY(GAME_HEIGHT/2);
	redKnight.setFrames(RED_KNIGHT_LOOKING_LEFT_START, RED_KNIGHT_LOOKING_LEFT_END);   // animation frames
	redKnight.setCurrentFrame(RED_KNIGHT_LOOKING_LEFT_START);     // starting frame
	redKnight.setFrameDelay(RED_KNIGHT_ANIMATION_DELAY);

	redLastDirection = left;
	greenLastDirection = right;
	keyDownLastFrame = false;
	keyDownThisFrame = false;
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	int greenDirectionx = 0;
	int greenDirectiony = 0;
	int redDirectionx = 0;
	int redDirectiony = 0;
	if(input->isKeyDown(VK_ESCAPE)){
		exit(0);
	}
	if(input->isKeyDown(GREEN_KNIGHT_RIGHT_KEY))            // if move right
	{				
		greenDirectionx--;
		greenKnight.setFrames(GREEN_KNIGHT_WALKING_RIGHT_START, GREEN_KNIGHT_WALKING_RIGHT_END);
		if (greenKnight.getX() > GAME_WIDTH)               // if off screen right
			greenKnight.setX((float)-greenKnight.getWidth());   // position off screen left
		greenLastDirection = right;
	}
	if(input->isKeyDown(GREEN_KNIGHT_LEFT_KEY))             // if move left
	{
		greenDirectionx++;
		greenKnight.setFrames(GREEN_KNIGHT_WALKING_LEFT_START, GREEN_KNIGHT_WALKING_LEFT_END);
		if (greenKnight.getX() < -greenKnight.getWidth())         // if off screen left
			greenKnight.setX((float)GAME_WIDTH);           // position off screen right
		greenLastDirection = left;
	}
	if(input->isKeyDown(GREEN_KNIGHT_DOWN_KEY)){
		greenDirectiony--;
		greenKnight.setFrames(GREEN_KNIGHT_WALKING_DOWN_START, GREEN_KNIGHT_WALKING_DOWN_END);
		if(greenKnight.getY() < -greenKnight.getHeight())
			greenKnight.setY((float)GAME_HEIGHT);
		greenLastDirection = down;
	}
	if(input->isKeyDown(GREEN_KNIGHT_UP_KEY)){
		greenDirectiony++;
		greenKnight.setFrames(GREEN_KNIGHT_WALKING_UP_START, GREEN_KNIGHT_WALKING_UP_END);
		if(greenKnight.getY() < -greenKnight.getHeight())
			greenKnight.setY((float)GAME_HEIGHT);
		greenLastDirection = up;
	}
	if(greenDirectionx == 0 && greenDirectiony == 0){
		if(greenLastDirection == left){
			greenKnight.setFrames(GREEN_KNIGHT_LOOKING_LEFT_START, GREEN_KNIGHT_LOOKING_LEFT_END);
		}
		if(greenLastDirection == right){
			greenKnight.setFrames(GREEN_KNIGHT_LOOKING_RIGHT_START, GREEN_KNIGHT_LOOKING_RIGHT_END);
		}
	}
	//Player 2 controls
	if(input->isKeyDown(RED_KNIGHT_RIGHT_KEY))            // if move right
	{				
		redDirectionx--;
		redKnight.setFrames(RED_KNIGHT_WALKING_RIGHT_START, RED_KNIGHT_WALKING_RIGHT_END);
		if (redKnight.getX() > GAME_WIDTH)               // if off screen right
			redKnight.setX((float)-redKnight.getWidth());   // position off screen left
		redLastDirection = right;
	}
	if(input->isKeyDown(RED_KNIGHT_LEFT_KEY))             // if move left
	{
		redDirectionx++;
		redKnight.setFrames(RED_KNIGHT_WALKING_LEFT_START, RED_KNIGHT_WALKING_LEFT_END);
		if (redKnight.getX() < -redKnight.getWidth())         // if off screen left
			redKnight.setX((float)GAME_WIDTH);           // position off screen right
		redLastDirection = left;
	}
	if(input->isKeyDown(RED_KNIGHT_DOWN_KEY)){
		redDirectiony--;
		redKnight.setFrames(RED_KNIGHT_WALKING_DOWN_START, RED_KNIGHT_WALKING_DOWN_END);
		if(redKnight.getY() < -redKnight.getHeight())
			redKnight.setY((float)GAME_HEIGHT);
		redLastDirection = down;
	}
	if(input->isKeyDown(RED_KNIGHT_UP_KEY)){
		redDirectiony++;
		redKnight.setFrames(RED_KNIGHT_WALKING_UP_START, RED_KNIGHT_WALKING_UP_END);
		if(redKnight.getY() < -redKnight.getHeight())
			redKnight.setY((float)GAME_HEIGHT);
		redLastDirection = up;
	}
	if(redDirectionx == 0 && redDirectiony == 0){
		if(redLastDirection == left){
			redKnight.setFrames(RED_KNIGHT_LOOKING_LEFT_START, RED_KNIGHT_LOOKING_LEFT_END);
		}
		if(redLastDirection == right){
			redKnight.setFrames(RED_KNIGHT_LOOKING_RIGHT_START, RED_KNIGHT_LOOKING_RIGHT_END);
		}
	}
	redKnight.setX(redKnight.getX() - frameTime * RED_KNIGHT_SPEED * redDirectionx);
	greenKnight.setX(greenKnight.getX() - frameTime * GREEN_KNIGHT_SPEED * greenDirectionx);
	redKnight.setY(redKnight.getY() - frameTime * RED_KNIGHT_SPEED * redDirectiony);
	greenKnight.setY(greenKnight.getY() - frameTime * GREEN_KNIGHT_SPEED * greenDirectiony);
	


	greenKnight.update(frameTime);
	redKnight.update(frameTime);
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
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites
	background.draw();
	greenKnight.draw();                            // add the spacejpo to the scene
	redKnight.draw();
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
	backgroundTexture.onLostDevice();
	greenKnightTexture.onLostDevice();
	redKnightTexture.onLostDevice();
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
	backgroundTexture.onResetDevice();
	greenKnightTexture.onResetDevice();
	redKnightTexture.onResetDevice();
	bullet1.onResetDevice();
	bullet2.onResetDevice();
	bullet3.onResetDevice();
	bullet4.onResetDevice();
	Game::resetAll();
	return;
}
