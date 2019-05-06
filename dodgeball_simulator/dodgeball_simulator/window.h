#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include "settings.h"


class window
{
public:
	int genWindow();
	GLFWwindow* getWindow();
	bool run();
	GLFWwindow* gameWindow;
};

#endif