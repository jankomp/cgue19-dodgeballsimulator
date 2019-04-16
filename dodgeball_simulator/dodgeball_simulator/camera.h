#pragma once
#include <glm/glm.hpp>
#include "PlayerCharacter.cpp"

class Camera
{
	//PlayerCharacter player;
	glm::vec3 cameraPosition;
	glm::vec3 playerPosition;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	const double distance;
	const double mouseSensitivity;
	// Euler Angles
	float yaw;
	float pitch;

public:
	Camera();
	glm::mat4 getWorldToViewMat() const;
	void rotate(double phi, double theta, float deltaTime);
	void updatePlayerPosition(glm::vec3 newPos);

};

