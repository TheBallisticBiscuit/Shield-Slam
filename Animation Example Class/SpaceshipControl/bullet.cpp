#include "bullet.h"

Bullet::Bullet(void){};

bool Bullet::initialize(Graphics* graphics, float startingX, float startingY, float startingXVelocity, float startingYVelocity, 
						Game* game){
	if (!bulletTexture.initialize(graphics,"pictures\\bullet.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	setX(startingX);
	setY(startingY);
	setScale(0.6);
	velocity.x = startingXVelocity;
	velocity.y = startingYVelocity;
	return Entity::initialize(game, 0, 0, 0, &bulletTexture);
}

void Bullet::update(float frameTime){
	float testX = getX() + (BULLET_SPEED * velocity.x * frameTime);
	float testY = getY() + (BULLET_SPEED * velocity.y * frameTime);
	setX(testX);
	setY(testY);
	if (getX()+getWidth() > GAME_WIDTH) {              // if off screen right
		setX((float)GAME_WIDTH-getWidth());   // position off screen left
		velocity.x *= -1;
	}
	if (getX() < 0){       // if off screen left
		setX(0);           // position off screen right
		velocity.x *= -1;
	}
	if(getY()+getHeight() > GAME_HEIGHT){
		setY((float)GAME_HEIGHT-getHeight());
		velocity.y *= -1;
	}
	if(getY() < 0){
		setY(0);
		velocity.y *= -1;
	}
	Entity::update(frameTime);
}