#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ball.h"
//#include <PxPhysicsAPI.h>


enum Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class PlayerCharacter
{
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	float speed;
	bool running;
	bool hasBall;

public:
	PlayerCharacter(glm::vec3 startPos, Ball* newBall);

	glm::vec3 getPosition();
	glm::mat4 getModelMat();

	Ball* ball;

	void rotate(float rotation, float deltaTime);
	void move(bool running,  Movement direction, float deltaTime);
	void updatePlayerCharacter(glm::vec3 newPos);
	void shootBall(glm::vec3 direction);
	bool shootingBall();
	int collision();

private:
	bool shooting;
};

#endif