#include "player.h"

Player::Player(void){}

bool Player::initialize(Graphics* graphics, const char* filepath, float startingX, float startingY,
	int rightKey, int leftKey, int downKey, int upKey, int lockKey, Game* game){
	if (!playerTexture.initialize(graphics, filepath)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1 texture"));
	}
	setX(startingX);                   
	setY(startingY);
	setFrames(PLAYER_LOOKING_RIGHT_START, PLAYER_LOOKING_RIGHT_END);   // animation frames
	setCurrentFrame(PLAYER_LOOKING_RIGHT_START);     // starting frame
	setFrameDelay(PLAYER_ANIMATION_DELAY);
	PLAYER_RIGHT_KEY = rightKey;
	PLAYER_LEFT_KEY = leftKey;
	PLAYER_DOWN_KEY = downKey;
	PLAYER_UP_KEY = upKey;

	PLAYER_LOCK_KEY = lockKey;
	lastXDirection = left;
	lastDirection = left;
	collisionType = entityNS::BOX;
	edge.top = -PLAYER_HEIGHT/2+10;
	edge.bottom = PLAYER_HEIGHT/2-10;
	edge.left = -PLAYER_WIDTH/2+20;
	edge.right = PLAYER_WIDTH/2-20;
	mass = 6000;
	score = 0;
	isDead = false;
	if(!playerShield.initialize(graphics, startingX, startingY, Shield::left, game)){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player 1 shield"));
	}
	return Entity::initialize(game, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_COLS, &playerTexture);
}

void Player::update(float frameTime){
	velocity.x = 0;
	velocity.y = 0;
	shieldLock = false;
	if(input->isKeyDown(PLAYER_LOCK_KEY) && isDead == false){
		shieldLock = true;
	}
	if(input->isKeyDown(PLAYER_RIGHT_KEY) && isDead == false)            // if move right
	{				
		velocity.x--;
		setFrames(PLAYER_WALKING_RIGHT_START, PLAYER_WALKING_RIGHT_END);
		if (getX()+PLAYER_WIDTH > GAME_WIDTH) {              // if off screen right
			setX((float)GAME_WIDTH-PLAYER_WIDTH);   // position off screen left
		}
		lastDirection = right;
		lastXDirection = right;
		if(!shieldLock){
			playerShield.setDirection(Shield::right);
		}
	}
	if(input->isKeyDown(PLAYER_LEFT_KEY) && isDead == false)             // if move left
	{
		velocity.x++;
		setFrames(PLAYER_WALKING_LEFT_START, PLAYER_WALKING_LEFT_END);
		if (getX() < 0){       // if off screen left
			setX(0);           // position off screen right
		}
		lastDirection = left;
		lastXDirection = left;
		if(!shieldLock){
			playerShield.setDirection(Shield::left);
		}
	}
	if(input->isKeyDown(PLAYER_DOWN_KEY) && isDead == false){
		velocity.y--;
		setFrames(PLAYER_WALKING_DOWN_START, PLAYER_WALKING_DOWN_END);
		if(getY()+PLAYER_HEIGHT > GAME_HEIGHT){
			setY((float)GAME_HEIGHT-PLAYER_HEIGHT);
		}
		lastDirection = down;
		if(!shieldLock){
			playerShield.setDirection(Shield::down);
		}
	}
	if(input->isKeyDown(PLAYER_UP_KEY) && isDead == false){
		velocity.y++;
		setFrames(PLAYER_WALKING_UP_START, PLAYER_WALKING_UP_END);
		if(getY() < 0){
			setY(0);
		}
		lastDirection = up;
		if(!shieldLock){
			playerShield.setDirection(Shield::up);
		}
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
	playerShield.update(frameTime, getX(), getY());
	Entity::update(frameTime);
}

bool Player::itHitShield(VECTOR2 collisionVec) { //Returns true if the bullet hit the shield, false otherwise				
	if(playerShield.getDirection() == 1){ //Right
		if(collisionVec.x < 0){
			return true;
		}
	}
	else if (playerShield.getDirection() == 0){ //Left
		if(collisionVec.x > 0){
			return true;
		}
	}
	else if(playerShield.getDirection() == 2){ //Up
		if(collisionVec.y > 0){
			return true;
		}
	}
	else if(playerShield.getDirection() == 3){ //Down
		if(collisionVec.y < 0){
			return true;
		}
	}
	return false;
}


void Player::wasted() {
	if (isDead == false) {
	audio->playCue(DEATH);
	}

	isDead = true;
}

void Player::respawn(float spawnX){
	isDead = false;
	setX(spawnX);
	setY(GAME_HEIGHT/2);
}

void Player::onLostDevice(){
	playerTexture.onLostDevice();
	playerShield.onLostDevice();
}

void Player::onResetDevice(){
	playerTexture.onResetDevice();
	playerShield.onResetDevice();
}

void Player::draw(){
	playerShield.draw();
	Entity::draw();
}

bool Player::isPlayerDead(){
	return isDead;
}

int Player::getShieldDirection(){
	return playerShield.getDirection();
}

int Player::getScore() {
	return score;
}

void Player::addScore() {
	score++;
}

void Player::resetScore(){
	score = 0;
}
