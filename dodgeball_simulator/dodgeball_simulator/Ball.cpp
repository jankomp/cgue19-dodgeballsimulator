#include "Ball.h"


Ball::Ball(vec3 newPosition)
{
	position = newPosition;
}

void Ball::drawBall(Shader* shader) {
}

void Ball::flyBall() {
	shot = true;
}

bool Ball::isShot() {
	bool returnValue = shot;
	shot = false;
	return returnValue;
}
