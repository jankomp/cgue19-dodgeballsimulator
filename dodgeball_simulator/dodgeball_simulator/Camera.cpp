#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include <iostream>

Camera::Camera(PlayerCharacter *newPlayer, glm::vec3 startPosCam) : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f), distance(3.0), mouseSensitivity(0.5), yaw(-90.0)
{
	player = newPlayer;
	cameraPosition = startPosCam;
}

Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f), distance(3.0), mouseSensitivity(0.75) {}

glm::mat4 Camera::getWorldToViewMat() const
{	
	glm::vec3 playerPos = player->getPosition();
	playerPos.x = playerPos.x;
	playerPos.y = playerPos.y + 2.0;
	playerPos.z = playerPos.z;
	return glm::lookAt(cameraPosition, playerPos, UP);

}

void Camera::rotate(double phi, double theta, float deltaTime)
{
	phi *= mouseSensitivity;
	theta *= mouseSensitivity;

	yaw += phi;
	pitch += theta;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 40.0f)
		pitch = 40.0f;
	if (pitch < -40.0f)
		pitch = -40.0f;

	//player->rotate(yaw, deltaTime);

	double x = distance * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	double y = -distance * sin(glm::radians(pitch));
	double z = distance * sin(glm::radians(yaw)) * cos(glm::radians(pitch));


	glm::vec3 playerPos = player->getPosition();
	cameraPosition.x = x + playerPos.x;
	cameraPosition.y = y + playerPos.y + 2.0;
	cameraPosition.z = z + playerPos.z;
	std::cout << "Camera: " << cameraPosition.x << "," << cameraPosition.y << "," << cameraPosition.z << std::endl;
}

void Camera::sidewaysMotion(bool running, Movement direction, float deltaTime) {
	glm::vec3 front = glm::vec3(0, 0, 1);
	glm::vec3 right = glm::vec3(1, 0, 0);
	float movementSpeed;

	if (running) {
		movementSpeed = 20;
	}
	else {
		movementSpeed = 5;
	}
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		cameraPosition += front * velocity;
	if (direction == BACKWARD)
		cameraPosition -= front * velocity;
	if (direction == LEFT)
		cameraPosition += right * velocity;
	if (direction == RIGHT)
		cameraPosition -= right * velocity;
}