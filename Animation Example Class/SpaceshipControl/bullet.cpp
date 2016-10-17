#include "bullet.h"

Bullet::Bullet(void){};

bool Bullet::initialize(Graphics* graphics, float startingX, float startingY, float startingXVelocity, float startingYVelocity, 
						Game* game){
		if (!bulletTexture.initialize(graphics,"pictures\\bullet.png")){
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
		}
		setX(startingX);
		setY(startingY);
		setScale(BULLET_SCALING);
		mass = 1;
		velocity.x = startingXVelocity;
		velocity.y = startingYVelocity;
		collisionType = entityNS::CIRCLE;
		radius = 15;
		return Entity::initialize(game, 0, 0, 0, &bulletTexture);
}

void Bullet::update(float frameTime){
	D3DXVec2Normalize(&velocity, &velocity);
	float testX = getX() + (BULLET_SPEED * velocity.x * frameTime);
	float testY = getY() + (BULLET_SPEED * velocity.y * frameTime);


#pragma region ScreenEdge
	if (testX + getWidth()*BULLET_SCALING > GAME_WIDTH+20) {              // if off screen right
		setX((float)GAME_WIDTH-getWidth()*BULLET_SCALING);   // position off screen left
		if(velocity.x > 0){
			velocity.x *= -1;
		}
	}
	if (testX < 0-20){       // if off screen left
		setX(0);           // position off screen right
		if(velocity.x < 0){
			velocity.x *= -1;
		}
	}
	if(testY + getHeight()*BULLET_SCALING > GAME_HEIGHT+20){ //If off screen bottom
		setY((float)GAME_HEIGHT-getHeight()*BULLET_SCALING);
		if(velocity.y > 0){
			velocity.y *= -1;
		}
	}
	if(testY < 0-20){ //If off screen top
		setY(0);
		if(velocity.y < 0){
			velocity.y *= -1;
		}
	}
#pragma endregion

#pragma region BulletAngle
	if (velocity.x > 0 && velocity.y < 0) {
		setDegrees(45);
	}
	if (velocity.x > 0 && velocity.y > 0) {
		setDegrees(135);
	}
	if (velocity.x < 0 && velocity.y > 0) {
		setDegrees(225);
	}
	if (velocity.x < 0 && velocity.y < 0) {
		setDegrees(315);
	}
#pragma endregion

	setX(testX);
	setY(testY);

	Entity::update(frameTime);
}

void Bullet::gameOver() {
	velocity.x = 0;
	velocity.y = 0;
}
