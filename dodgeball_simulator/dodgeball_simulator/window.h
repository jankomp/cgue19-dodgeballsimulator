#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <sstream>
#include <string>

//#include "Utils.h"
#include "settings.h"


class window
{
	
public:


	int genWindow(int SCR_WIDTH, int SCR_HEIGHT);
	GLFWwindow* getWindow();
	bool run();
	GLFWwindow* gameWindow;
	int refresh_rate;
};

#endif