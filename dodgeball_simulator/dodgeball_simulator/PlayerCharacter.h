#pragma once
#include <glm/glm.hpp>
#include "Camera.h"

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
	//Camera * camera;

public:
	//PlayerCharacter();
	//PlayerCharacter(Camera* newCamera);

	void rotate(float rotation, float deltaTime);
	void move(bool running,  Movement direction, float deltaTime);


private:
	void updatePlayerCharacter();
};

