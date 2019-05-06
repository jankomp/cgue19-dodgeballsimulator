#include "window.h"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

int window::genWindow()
{
	settings s;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	//GLFWwindow* window;

	/* Create a windowed mode window and its OpenGL context */
	gameWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "dodgeball simulator", NULL, NULL);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	if (!gameWindow)
	{
		glfwTerminate();
		std::printf("Failed to create window");
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(gameWindow);
	glfwSetFramebufferSizeCallback(gameWindow, s.framebuffer_size_callback);
	glfwSetCursorPosCallback(gameWindow, s.mouse_callback);
	glfwSetScrollCallback(gameWindow, s.scroll_callback);
	glfwSetMouseButtonCallback(gameWindow, s.mouse_button_callback);
	//hide cursor
	glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glewExperimental = true;
	GLenum err = glewInit();

	// If GLEW wasn't initialized
	if (err != GLEW_OK) {
		std::printf("Failed to init GLEW");
	}
}

GLFWwindow* window::getWindow()
{
	return gameWindow;
}

bool window::run()
{
	return !glfwWindowShouldClose(gameWindow);
}

