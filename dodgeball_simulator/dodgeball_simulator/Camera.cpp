#include "Camera.h"
#include <glm/gtx/transform.hpp>


Camera::Camera(PlayerCharacter *newPlayer) : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f), distance(3.0), mouseSensitivity(0.75)
{
	player = newPlayer;
}

Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f), distance(3.0), mouseSensitivity(0.75) {}

glm::mat4 Camera::getWorldToViewMat() const
{	
	return glm::lookAt(cameraPosition, player->getPosition(), UP);
}

void Camera::rotate(double phi, double theta, float deltaTime)
{
	phi *= mouseSensitivity;
	theta *= mouseSensitivity;

	yaw += phi;
	pitch -= theta;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	player->rotate(yaw, deltaTime);

	double x = distance * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	double y = distance * sin(glm::radians(pitch));
	double z = distance * sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraPosition = glm::vec3(x, y, z);
}


