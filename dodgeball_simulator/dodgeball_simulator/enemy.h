#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

public:
	enemy(glm::vec3 startPos);

	glm::vec3 getPosition();
	glm::mat4 getModelMat();

	void rotate(float rotation, float deltaTime);
	void move(float deltaTime);
	int collision();



private:
	void updatePlayerCharacter();
};

