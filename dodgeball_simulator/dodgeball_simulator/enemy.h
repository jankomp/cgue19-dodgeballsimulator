#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "text_renderer.h"
#include "PlayerCharacter.h"
//#include <PxPhysicsAPI.h>



class enemy
{
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	float speed;
	bool running;
	int runOrNot;
	int dir;
	int counter;
	bool hasBall;
	bool active;
	Ball* ball;

public:
	enemy(glm::vec3 startPos, Ball* ball);

	glm::vec3 getPosition();
	glm::mat4 getModelMat();

	void rotate(float rotation, float deltaTime);
	void move(float deltaTime);
	void setPosition(glm::vec3 newPos);
	void sethasball(bool possession);
	bool gethasball();
	bool getActive();
	void hit(PlayerCharacter *player);
	bool shooting;
	int count;

	void shootBall();
	bool shootingBall();
private:
	
};

