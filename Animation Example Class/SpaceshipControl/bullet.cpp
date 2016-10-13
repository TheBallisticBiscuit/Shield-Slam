#include "bullet.h"

Bullet::Bullet(void){};

bool Bullet::initialize(Graphics* graphics, float startingX, float startingY, float startingXVelocity, float startingYVelocity, 
						Game* game, int width, int height, int ncols){
	if (!bulletTexture.initialize(graphics,"pictures\\bullet.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	if (!bullet.initialize(graphics, 0, 0, 0, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	bullet.setX(startingX);
	bullet.setY(startingY);
	bullet.setScale(0.6);
	velocity.x = startingXVelocity;
	velocity.y = startingYVelocity;
	return Entity::initialize(game, width, height, ncols, &bulletTexture);
}

void Bullet::update(float frameTime){
	float testX = bullet.getX() + (BULLET_SPEED * velocity.x * frameTime);
	float testY = bullet.getY() + (BULLET_SPEED * velocity.y * frameTime);
	bullet.setX(testX);
	bullet.setY(testY);
	bullet.update(frameTime);
}