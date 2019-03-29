#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>

#include "shader.h"
#include "camera.h"
#include "square.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "dodgeball simulator", NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		std::printf("Failed to create window");
		//exit;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum err = glewInit();

	// If GLEW wasn't initialized
	if (err != GLEW_OK) {
		std::printf("Failed to init GLEW");
		//exit;
	}

	shader testShader;
	testShader.loadShader("shaders/basic.vert", "shaders/basic.frag");

	testShader.useShader();

	square floor = square(2.0f, 3.0f);



	
	//geometry sphere = geometry::geometry(glm::translate(glm::mat4(1.0f), glm::vec3(-1.2f, 1.0f, 0.0f)), geometry::createSphereGeometry(32, 16, 1.0f), glm::vec3(1.3,1.3,1.3));


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);



		/*draw triangle*/
		floor.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	testShader.deleteShader();

	glfwTerminate();
	return 0;
}