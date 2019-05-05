#pragma once
#include "camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include "PlayerCharacter.h"



class settings
public:
	settings();
	//settings(PlayerCharacter *playP, Camera *cam, float deltaT);
	settings(PlayerCharacter *playP, Camera *cam);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void processInput(GLFWwindow *window);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	 //void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	 //void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	 //void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	 //void processInput(GLFWwindow *window);
	 //void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	 int getScreen();
	 bool headUpDisplay();
	 float getDeltaTime();
	 void setDeltaTime(float toSet);

};

