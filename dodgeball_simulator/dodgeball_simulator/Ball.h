#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>

using namespace glm;

//class that contains the information if the ball is being shot right now
class Ball
{
public:
	bool caught;
	bool shot;
	vec3 position;
	vec3 direction;

	void flyBall();
	bool isShot();

	Ball(vec3 newPosition);

private:
};

#endif