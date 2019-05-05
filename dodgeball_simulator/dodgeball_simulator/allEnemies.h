#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>


#include "shader.h"


//#include "enemy.h"
class allEnemies
{

	int score;

public:
	allEnemies();
	int getScore();
	void increaseScore();
	void draw(Shader &gameShader);
	~allEnemies();
};

