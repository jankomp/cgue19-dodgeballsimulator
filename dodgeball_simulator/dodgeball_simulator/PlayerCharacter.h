#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class PlayerCharacter
{
	glm::mat4 modelMat;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	float speed;
	bool running;

public:
	PlayerCharacter();

	glm::vec3 getPosition();
	glm::mat4 getModelMat();

	void rotate(float rotation, float deltaTime);
	void move(bool running,  Movement direction, float deltaTime);


private:
	void updatePlayerCharacter();
};

