#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include <vector>

class square
{
public:
	square( float hight,  float length);
	~square();

	void draw();

	float height;
	float length;

	std::vector<GLfloat> square::calcVertices();
	
};

