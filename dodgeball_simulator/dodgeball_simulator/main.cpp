#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>

#include "shader.h"
//#include "square.h"
#include "geometry.h"
#include "mesh.h"
#include "model.h"


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


	float points[9] = {
		-0.5f, 0.2f, 0.4f,
		1.0f, 0.8f, -0.3f,
		0.7f, 0.5f, 0.2f
	};

	unsigned int buffer;

	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	testShader.useShader();



	//square floor = square(2.0f, 3.0f);

	
	//geometry sphere = geometry::geometry(glm::translate(glm::mat4(1.0f), glm::vec3(-1.2f, 1.0f, 0.0f)), geometry::createSphereGeometry(32, 16, 1.0f), glm::vec3(1.3,1.3,1.3));

	//geometry cube = geometry(glm::translate(glm::mat4(1.0f), glm::vec3(-1.2f, -1.5f, 0.0f)), geometry::createCubeGeometry(1.5f, 1.5f, 1.5f));
	//geometry sphere = geometry(glm::translate(glm::mat4(1.0f), glm::vec3(-1.2f, 1.0f, 0.0f)), geometry::createSphereGeometry(32, 16, 1.0f));



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/*draw triangle*/
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//floor.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	testShader.deleteShader();




	glfwTerminate();
	return 0;
}