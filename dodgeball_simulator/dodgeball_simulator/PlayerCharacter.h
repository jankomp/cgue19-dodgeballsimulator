#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "ball.h"
#include "text_renderer.h"
#include "main.h"

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
	int lifes;

public:
	PlayerCharacter(glm::vec3 startPos, Ball* newBall);
	Ball* ball;

	glm::vec3 getPosition();

	void rotate(float rotation, float deltaTime);
	void move(bool running,  Movement direction, float deltaTime);
	void updatePlayerCharacter(glm::vec3 newPos);
	void shootBall();
	bool shootingBall(float deltaTime);
	void sethasball(bool posession);
	bool gethasball();
	int getLifes();
	void hit();

private:
	bool shooting;
	float count;
};

#endif