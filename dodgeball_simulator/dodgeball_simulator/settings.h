#ifndef SETTINGS_H
#define SETTINGS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>

#include "camera.h"
#include "PlayerCharacter.h"
#include "enemy.h"
#include "INIReader.h"




class settings 
{
public:
	settings();
	//settings(PlayerCharacter *playP, Camera *cam, float deltaT);
	settings(PlayerCharacter *playP, Camera *cam);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void processInput(GLFWwindow *window);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	

	 int getScreen();
	 bool headUpDisplay();
	 float getDeltaTime();
	 float getBrightness();
	 void setDeltaTime(float toSet);
	 void setScreen(int scr);
};

#endif