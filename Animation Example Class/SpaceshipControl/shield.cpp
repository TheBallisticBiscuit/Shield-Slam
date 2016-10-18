#include "shield.h"

bool Shield::initialize(Graphics* graphics, float startingX, float startingY, LastDirection startingDirection, Game* game){
	if (!shieldTexture.initialize(graphics,"pictures\\shield.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	setX(startingX);
	setY(startingY);

	active = false;

	collisionType = entityNS::ROTATED_BOX;
	edge.left = -(SHIELD_WIDTH)/2;
	edge.right = (SHIELD_WIDTH)/2;
	edge.bottom = (SHIELD_HEIGHT)/2;
	edge.top = -(SHIELD_HEIGHT)/2;
	velocity.x = 0;
	velocity.y = 0;
	mass = 2000;
	shieldDirection = startingDirection;
	setDegrees(90);
	setX(getX() + 15);
	setY(getY() + 20);
	setScale(SHIELD_SCALE);
	return Entity::initialize(game, 0, 0, 0, &shieldTexture);
}

void Shield::update(float frameTime, float playerX, float playerY){
	if(shieldDirection == left){
		setDegrees(270);
		setX(playerX-10);
		setY(playerY+25);
	}
	else if(shieldDirection == right){
		setDegrees(90);
		setX(playerX+12);
		setY(playerY+25);
	}
	else if(shieldDirection == up){
		setDegrees(0);
		setX(playerX+1);
		setY(playerY-5);
	}
	else if(shieldDirection == down){
		setDegrees(180);
		setX(playerX+1);
		setY(playerY+PLAYER_HEIGHT-15);
	}
}

void Shield::setDirection(LastDirection newDirection){
	shieldDirection = newDirection;
}

int Shield::getDirection() {
	int direction = shieldDirection;
	return direction;
}
