#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include "settings.h"
class window
{
	

public:
	int genWindow(int SCR_WIDTH, int SCR_HEIGHT);
	GLFWwindow* getWindow();
	bool run();
	GLFWwindow* gameWindow;
};

