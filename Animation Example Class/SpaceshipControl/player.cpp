#include "player.h"

Player::Player(void){}

bool Player::initialize(Graphics* graphics, const char* filepath, float startingX, float startingY,
		int rightKey, int leftKey, int downKey, int upKey,
		Game* game){
	if (!playerTexture.initialize(graphics, filepath))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1 texture"));

	/*if (!player.initialize(graphics, 256/4, 384/6, PLAYER_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1"));*/
	setX(startingX);                    // start above and left of planet
	setY(startingY);
	setFrames(PLAYER_LOOKING_RIGHT_START, PLAYER_LOOKING_RIGHT_END);   // animation frames
	setCurrentFrame(PLAYER_LOOKING_RIGHT_START);     // starting frame
	setFrameDelay(PLAYER_ANIMATION_DELAY);
	PLAYER_RIGHT_KEY = rightKey;
	PLAYER_LEFT_KEY = leftKey;
	PLAYER_DOWN_KEY = downKey;
	PLAYER_UP_KEY = upKey;
	lastXDirection = left;
	lastDirection = left;
	collisionType = entityNS::BOX;
	isDead = false;
	return Entity::initialize(game, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_COLS, &playerTexture);
}

void Player::update(float frameTime){
	velocity.x = 0;
	velocity.y = 0;
	if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
	{				
		velocity.x--;
		setFrames(PLAYER_WALKING_RIGHT_START, PLAYER_WALKING_RIGHT_END);
		if (getX()+PLAYER_WIDTH > GAME_WIDTH) {              // if off screen right
			setX((float)GAME_WIDTH-PLAYER_WIDTH);   // position off screen left
		}
		lastDirection = right;
		lastXDirection = right;
	}
	if(input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
	{
		velocity.x++;
		setFrames(PLAYER_WALKING_LEFT_START, PLAYER_WALKING_LEFT_END);
		if (getX() < 0){       // if off screen left
			setX(0);           // position off screen right
		}
		lastDirection = left;
		lastXDirection = left;
	}
	if(input->isKeyDown(PLAYER_DOWN_KEY)){
		velocity.y--;
		setFrames(PLAYER_WALKING_DOWN_START, PLAYER_WALKING_DOWN_END);
		if(getY()+PLAYER_HEIGHT > GAME_HEIGHT){
			setY((float)GAME_HEIGHT-PLAYER_HEIGHT);
		}
		lastDirection = down;
	}
	if(input->isKeyDown(PLAYER_UP_KEY)){
		velocity.y++;
		setFrames(PLAYER_WALKING_UP_START, PLAYER_WALKING_UP_END);
		if(getY() < 0){
			setY(0);
		}
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
	D3DXVec2Normalize(&velocity, &velocity);
	setX(getX() - frameTime * PLAYER_SPEED * velocity.x);
	setY(getY() - frameTime * PLAYER_SPEED * velocity.y);
	Entity::update(frameTime);
}

void Player::onLostDevice(){
	playerTexture.onLostDevice();
}

void Player::onResetDevice(){
	playerTexture.onResetDevice();
}