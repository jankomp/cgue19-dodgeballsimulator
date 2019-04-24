/*#include "Ball.h"

Ball::Ball(Model *newModel) : speed(20.0f)
{
	ballModel = newModel;
}


void Ball::launchBall(glm::vec3 direction) {
	launchDirection = glm::normalize(direction);
}

void Ball::update() {
	glm::vec3 aPosition = position + (launchDirection * speed);

	Collision collision = collision(aPosition);

	if (collision == WALL) {
	
	}
	else if (collision == ENEMY) {
	
	}
	else if (collision == PLAYER) {
	
	}
	else {
		position = aPosition;
	}

}

Collision Ball::collision(glm::vec3 destination) {
	return WALL;
}*/