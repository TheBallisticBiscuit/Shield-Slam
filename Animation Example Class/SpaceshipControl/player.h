#pragma once
#include "game.h"
#include "graphics.h"
#include "textureManager.h"
#include "image.h"
#include "constants.h"
#include "entity.h"
#include "shield.h"

class Player : public Entity{
public:
	Player(void);
	void update(float frameTime);
	bool initialize(Graphics* graphics, const char* texture, float startingX, float startingY,
		int rightKey, int leftKey, int downKey, int upKey, int lockKey,
		Game* game);

	bool itHitShield(VECTOR2 collisionVec);
	void wasted(); //When player gets hit, stops his movement

	void onLostDevice();
	void onResetDevice();
	void draw();

	Shield playerShield;
private:
	enum LastDirection {left, right, up, down} lastDirection;
	LastDirection lastXDirection; //~~~ DELETE? Not being used.
	int PLAYER_RIGHT_KEY;
	int PLAYER_LEFT_KEY;
	int PLAYER_UP_KEY;
	int PLAYER_DOWN_KEY;
	int PLAYER_LOCK_KEY;
	TextureManager playerTexture;
	bool isDead;
	bool shieldLock;
};