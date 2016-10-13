#include "player.h"

Player::Player(void){}

void Player::update(float frameTime){
	velocity.x = 0;
	velocity.y = 0;
	if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
	{				
		velocity.x++;
		setFrames(PLAYER_WALKING_RIGHT_START, PLAYER_WALKING_RIGHT_END);
		if (getX() > GAME_WIDTH)               // if off screen right
			setX((float)-getWidth());   // position off screen left
		lastDirection = right;
		lastXDirection = right;
	}
	if(input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
	{
		velocity.x++;
		setFrames(PLAYER_WALKING_LEFT_START, PLAYER_WALKING_LEFT_END);
		if (getX() < -getWidth())         // if off screen left
			setX((float)GAME_WIDTH);           // position off screen right
		lastDirection = left;
		lastXDirection = left;
	}
	if(input->isKeyDown(PLAYER_DOWN_KEY)){
		velocity.y--;
		setFrames(PLAYER_WALKING_DOWN_START, PLAYER_WALKING_DOWN_END);
		if(getY() < -getHeight())
			setY((float)GAME_HEIGHT);
		lastDirection = down;
	}
	if(input->isKeyDown(PLAYER_UP_KEY)){
		velocity.y++;
		setFrames(PLAYER_WALKING_UP_START, PLAYER_WALKING_UP_END);
		if(getY() < -player.getHeight())
			player.setY((float)GAME_HEIGHT);
		lastDirection = up;
	}
	if(velocity.x == 0 && velocity.y == 0){
		if(lastXDirection == left){
			setFrames(PLAYER_LOOKING_LEFT_START, PLAYER_LOOKING_LEFT_END);
		}
		if(lastXDirection == right){
			setFrames(PLAYER_LOOKING_RIGHT_START, PLAYER_LOOKING_RIGHT_END);
		}
	}
	setX(player.getX() - frameTime * PLAYER_SPEED * velocity.x);
	setY(player.getY() - frameTime * PLAYER_SPEED * velocity.y);
	player.update(frameTime);
}

bool Player::initialize(Graphics* graphics, const char* filepath, float startingX, float startingY,
		int rightKey, int leftKey, int downKey, int upKey,
		Game* game){
	if (!playerTexture.initialize(graphics, filepath))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1 texture"));

	if (!player.initialize(graphics, 256/4, 384/6, PLAYER_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1"));
	player.setX(GAME_WIDTH/4);                    // start above and left of planet
	player.setY(GAME_HEIGHT/2);
	player.setFrames(PLAYER_LOOKING_RIGHT_START, PLAYER_LOOKING_RIGHT_END);   // animation frames
	player.setCurrentFrame(PLAYER_LOOKING_RIGHT_START);     // starting frame
	player.setFrameDelay(PLAYER_ANIMATION_DELAY);

	lastDirection = left;
	return Entity::initialize(game, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_COLS, &playerTexture);
}

void Player::onLostDevice(){
	playerTexture.onLostDevice();
}

void Player::onResetDevice(){
	playerTexture.onResetDevice();
}