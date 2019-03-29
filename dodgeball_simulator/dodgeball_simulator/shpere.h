#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include "shader.h"

#include <memory>
#include <glm\gtc\matrix_transform.hpp>

class shpere
{
public:
	shpere(unsigned int longitudeSegments, unsigned int latitudeSegments, float radius);
	~shpere();
};

