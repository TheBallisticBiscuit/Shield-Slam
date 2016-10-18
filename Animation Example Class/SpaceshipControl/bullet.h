#pragma once
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "constants.h"
#include "entity.h"
#include "player.h"



class Bullet : public Entity{
public:
	Bullet(void);
	bool initialize(Graphics* graphics, float startingX, float startingY, float startingXVelocity, float startingYVelocity,
		Game* game);
	void update(float frameTime);
	void draw(){
		Entity::draw();
	}
	void gameOver(); //Remove if game.paused is sufficient
	void onLostDevice(){

		bulletTexture.onLostDevice();
	}
	void onResetDevice(){
		bulletTexture.onResetDevice();
	}
	void reflect(int shieldDirection, Entity& ent);
private:
	TextureManager bulletTexture;
};