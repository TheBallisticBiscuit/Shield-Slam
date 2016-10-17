#include "obstacle.h"

bool Obstacle::initialize(Graphics* graphics, float startingX, float startingY, Game* game){
	setX(startingX);                    // start above and left of planet
	setY(startingY);
	setFrames(0, 10);
	setCurrentFrame(0);
	setFrameDelay(OBSTACLE_ANIMATION_DELAY); 
	mass = 1000000;
	collisionType = entityNS::BOX;
	edge.top = -OBSTACLE_HEIGHT/2;
	edge.bottom = OBSTACLE_HEIGHT/2;
	edge.left = -OBSTACLE_WIDTH/2+20;
	edge.right = OBSTACLE_WIDTH/2-20;
	if(!obstacle.initialize(graphics, "pictures\\animatedWall.png")){
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing obstacle texture"));
	}
	setScale(OBSTACLE_SCALE);
	return Entity::initialize(game, 0, OBSTACLE_HEIGHT, 1, &obstacle);
}