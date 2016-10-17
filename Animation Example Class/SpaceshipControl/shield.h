#pragma once
#include "entity.h"
#include "constants.h"

class Shield : public Entity{
public:
	enum LastDirection {left, right, up, down};
	Shield(void){};
	bool initialize(Graphics* graphics, float startingX, float startingY, LastDirection startingDirection, Game* game);
	void update(float frameTime, float playerX, float playerY);
	void onLostDevice(){
		shieldTexture.onLostDevice();
	}
	void onResetDevice(){
		shieldTexture.onResetDevice();
	}
	void setDirection(LastDirection newDirection);
private:
	TextureManager shieldTexture;
	LastDirection shieldDirection;
};