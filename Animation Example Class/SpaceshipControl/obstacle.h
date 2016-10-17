#pragma once
#include "constants.h"
#include "entity.h"

class Obstacle : public Entity{
public:
	Obstacle(void){}
	bool initialize(Graphics* graphics, float startingX, float startingY, Game* game);
	void onLostDevice(){obstacle.onLostDevice();}
	void onResetDevice(){obstacle.onResetDevice();}
private:
	TextureManager obstacle;
};