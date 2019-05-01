#pragma once
#include <glm/glm.hpp>

class Ball
{
public:
	bool caught;
	glm::vec3 position;
	glm::vec3 direction;

	Ball();
	~Ball();
};

