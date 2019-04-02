#include "Camera.h"
#include <glm/gtx/transform.hpp>


Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f)
{
}


glm::mat4 Camera::getWorldToViewMat() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}