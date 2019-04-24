/*#pragma once
#include "model.h"

enum Collision {
	PLAYER,
	ENEMY,
	WALL
};

class Ball
{
public:
	Model *ballModel;
	float speed;
	glm::vec3 position;
	glm::vec3 launchDirection;

	Ball(Model *newModel);
	~Ball();

	void update();
	void launchBall(glm::vec3 direction);

private:
	Collision collision(glm::vec3 destination);
};

*/