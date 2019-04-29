#pragma once
#include "PlayerCharacter.h"

class Camera
{
	PlayerCharacter *player;
	glm::vec3 cameraPosition;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	const double distance;
	const double mouseSensitivity;
	// Euler Angles
	float yaw;
	float pitch;

public:
	Camera();
	Camera(PlayerCharacter *newPlayer, glm::vec3 startPosCam);
	glm::mat4 getWorldToViewMat() const;
	void rotate(double phi, double theta, float deltaTime);
	void sidewaysMotion(bool running, Movement direction, float deltaTime);
};

