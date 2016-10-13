#pragma once
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "constants.h"
#include "entity.h"



class Bullet : public Entity{
public:
	Bullet(void);
	bool initialize(Graphics* graphics, float startingX, float startingY, float startingXVelocity, float startingYVelocity,
		Game* game, int width, int height, int ncols);
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
};