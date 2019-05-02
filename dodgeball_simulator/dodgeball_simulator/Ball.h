#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>

using namespace glm;

class Shader;
class Model;

class Ball
{
public:
	bool caught;
	vec3 position;
	vec3 direction;

	void updatePosition(vec3 newPosition);
	void drawBall(Shader* shader);
	void flyBall();

	Ball();

private:
};

#endif