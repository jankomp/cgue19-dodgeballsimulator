#pragma once
#include <glm/glm.hpp>

class Camera
{

	glm::vec3 cameraPosition;
	glm::vec3 playerPosition;
	glm::vec3 viewDirection;
	const glm::vec3 UP;
	const double distance;

public:
	Camera();
	glm::mat4 getWorldToViewMat() const;
	void rotate(double phi, double theta);
	void updatePlayerPosition(glm::vec3 newPos);
};

