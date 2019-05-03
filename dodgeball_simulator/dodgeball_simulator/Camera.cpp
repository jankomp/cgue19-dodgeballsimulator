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
	if (pitch > 50.0f)
		pitch = 50.0f;
	if (pitch < -40.0f)
		pitch = -40.0f;

	//player->rotate(yaw, deltaTime);

	double x = distance * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	double y = -distance * sin(glm::radians(pitch));
	double z = distance * sin(glm::radians(yaw)) * cos(glm::radians(pitch));


	glm::vec3 playerPos = player->getPosition();
	
	cameraRotation = glm::vec3(x, y + 2.0, z);
	cameraPosition = playerPos + cameraRotation;
	std::cout << "Camera: " << cameraPosition.x << "," << cameraPosition.y << "," << cameraPosition.z << std::endl;
}

void Camera::sidewaysMotion() {
	cameraPosition = player->getPosition() + cameraRotation;
}

void Camera::camReset(PlayerCharacter *newPlayer, glm::vec3 startPosCam)
{
	cameraPosition = glm::vec3(0.0f, 2.0f, -6.5f);
	player->updatePlayerCharacter(glm::vec3(0.0, 0.0, -4.5));
	//player = newPlayer;
	viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	//UP = glm::vec3(0.0f, 1.0f, 0.0f); 
	//distance = (3.0);
	//mouseSensitivity = (0.5);
	yaw = (-90.0);

}

glm::vec3 Camera::getViewDirection()
{
	return player->getPosition() - cameraPosition;
}