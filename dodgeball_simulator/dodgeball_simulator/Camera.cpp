#include "Camera.h"
#include <glm/gtx/transform.hpp>


Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f), distance(3.0)
{
}


glm::mat4 Camera::getWorldToViewMat() const
{
	return glm::lookAt(cameraPosition, playerPosition, UP);
}

void Camera::rotate(double phi, double theta)
{
	double x = distance * sin(phi);
	double y = distance * cos(phi) * sin(theta);
	double z = distance * cos(phi);

	cameraPosition = glm::vec3(x, y, z);
}

void Camera::updatePlayerPosition(glm::vec3 newPos)
{
	playerPosition = newPos;
}
