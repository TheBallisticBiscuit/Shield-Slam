#include "bullet.h"

Bullet::Bullet(void){};

void Bullet::initialize(Graphics* graphics, float startingX, float startingY, float startingDirectionX, float startingDirectionY){
	if (!bulletTexture.initialize(graphics,"pictures\\bullet.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	if (!bullet.initialize(graphics, 0, 0, 0, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	bullet.setX(startingX);
	bullet.setY(startingY);
	bullet.setScale(0.6);
	directionX = startingDirectionX;
	directionY = startingDirectionY;
}

void Bullet::update(float frameTime){
	float testX = bullet.getX() + (BULLET_SPEED * directionX * frameTime);
	float testY = bullet.getY() + (BULLET_SPEED * directionY * frameTime);
	if(testX < 0 || testX + bullet.getWidth() * bullet.getScale() > GAME_WIDTH){
		directionX *= -1;
	}
	bullet.setX(testX);
	if(testY < 0 || testY + bullet.getHeight() * bullet.getScale() > GAME_HEIGHT){
		directionY *= -1;
	}
	bullet.setY(testY);
	if(directionX > 0){
		if(directionY > 0){
			bullet.setDegrees(135);
		}
		else{
			bullet.setDegrees(45);
		}
	}
	else{
		if(directionY > 0){
			bullet.setDegrees(225);
		}
		else{
			bullet.setDegrees(315);
		}
	}

}