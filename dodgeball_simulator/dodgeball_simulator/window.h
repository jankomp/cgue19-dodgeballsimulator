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
	int genWindow();
	GLFWwindow* getWindow();
	bool run();
	GLFWwindow* gameWindow;

	//static void APIENTRY DebugCallbackDefault(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);
	//static std::string FormatDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, const char* msg);
};

#endif