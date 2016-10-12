#pragma once
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "constants.h"



class Bullet{
public:
	Bullet(void);
	void initialize( Graphics* graphics, float startingX, float startingY, float startingXVel, float startingYVel);
	void update(float frameTime);
	void draw(){
		bullet.draw();
	}
	void onLostDevice(){
		bulletTexture.onLostDevice();
	}
	void onResetDevice(){
		bulletTexture.onResetDevice();
	}
private:
	TextureManager bulletTexture;
	Image bullet;
	VECTOR2 velocity;
	int directionX;
	int directionY;
};