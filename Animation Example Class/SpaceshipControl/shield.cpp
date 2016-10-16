#include "shield.h"

bool Shield::initialize(Graphics* graphics, float startingX, float startingY, LastDirection startingDirection, Game* game){
	if (!shieldTexture.initialize(graphics,"pictures\\shield.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	setX(startingX);
	setY(startingY);
	collisionType = entityNS::BOX;
	edge.left = -getWidth();
	edge.right = getWidth();
	edge.bottom = getHeight();
	edge.top = -getWidth();
	mass = 2000;
	shieldDirection = startingDirection;
	setDegrees(90);
	setX(getX()+15);
	setY(getY() + 20);
	setScale(SHIELD_SCALE);
	return Entity::initialize(game, 0, 0, 0, &shieldTexture);
}

void Shield::update(float frameTime, float playerX, float playerY){
	if(shieldDirection == left){
		setDegrees(90);
		setX(playerX+15);
		setY(playerY+20);
	}
	else if(shieldDirection == right){
		setDegrees(270);
		setX(playerX-30);
		setY(playerY+20);
	}
	else if(shieldDirection == up){
		setDegrees(0);
		setX(playerX-7);
		setY(playerY-15);
	}
	else if(shieldDirection == down){
		setDegrees(180);
		setX(playerX-7);
		setY(playerY+PLAYER_HEIGHT-10);
	}
}

void Shield::setDirection(LastDirection newDirection){
	shieldDirection = newDirection;
}