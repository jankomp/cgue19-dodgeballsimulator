#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include <ft2build.h>

#include "physics.h"
#include "shader.h"
#include "model.h"
#include "Camera.h"
#include "text_renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1800;

// player & camera
bool running = false;
PlayerCharacter player (glm::vec3(0.0, 0.0, -4.5));
PlayerCharacter player_gegner(glm::vec3(0.0, 0.0, 4.5));

glm::vec3 camPos;

//camPos.x = player.getPosition.x + 0.0f;



Camera camera(&player, glm::vec3(0.0f,2.0f,-6.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(void)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "dodgeball simulator", NULL, NULL);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	
	
	if (!window)
	{
		glfwTerminate();
		std::printf("Failed to create window");
		//exit;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewExperimental = true;
	GLenum err = glewInit();

	// If GLEW wasn't initialized
	if (err != GLEW_OK) {
		std::printf("Failed to init GLEW");
		//exit;
	}

	Shader gameShader("shaders/model.vert", "shaders/model.frag");
	Shader hudShader("shaders/basic.vert", "shaders/basic.frag");
	Shader textShader("shaders/text.vert", "shaders/text.frag");

	Model ball("modells/ball/ball.obj");
	Model turnhalle("modells/turnhalle/turnhalle.obj");

	Model spieler("modells/junge_rot/Lt_boy.obj");
	Model gegner("modells/junge_blau/Lt_boy.obj");


	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initPhysics();

	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


	TextRenderer level;
	level.Load("fonts/arial.ttf", 48);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{


		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);


		/* Render here */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT );


		// view/projection transformations

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getWorldToViewMat();
		gameShader.setMat4("projection", projection);
		gameShader.setMat4("view", view);


		glm::mat4 proj2 = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
		textShader.use();
		textShader.setMat4("projection", proj2);
		level.RenderText(textShader, "Level", 200.0f, 200.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));


		gameShader.use();





		// render the loaded model

		//turnhalle
		glm::mat4 model_turnhalle = glm::mat4(1.0f);
		model_turnhalle = glm::rotate(model_turnhalle, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		gameShader.setMat4("model", model_turnhalle);
		turnhalle.Draw(gameShader);

		//ball
		glm::mat4 model_ball = glm::mat4(1.0f);
		model_ball = glm::translate(model_ball, glm::vec3(2.0f, 2.0f, 0.0f)); // translate it down so it's at the center of the scene
		model_ball = glm::scale(model_ball, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
		gameShader.setMat4("model", model_ball);
		ball.Draw(gameShader);

		//spieler
		glm::mat4 model_spieler = glm::mat4(1.0f);
		model_spieler = glm::translate(model_spieler, player.getPosition());
		model_spieler = glm::scale(model_spieler, glm::vec3(0.3f, 0.3f, 0.3f));
		gameShader.setMat4("model", model_spieler);
		spieler.Draw(gameShader);

		glm::mat4 model_gegner = glm::mat4(1.0f);
		model_gegner = glm::translate(model_gegner, player_gegner.getPosition());
		model_gegner = glm::rotate(model_gegner, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model_gegner = glm::scale(model_gegner, glm::vec3(0.3f, 0.3f, 0.3f));
		gameShader.setMat4("model", model_gegner);
		gegner.Draw(gameShader);



		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}



	glfwTerminate();
	return 0;
}


// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		running = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		running = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		player.move(running, FORWARD, deltaTime);
		camera.sidewaysMotion(running, FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		player.move(running, BACKWARD, deltaTime);
		camera.sidewaysMotion(running, BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		player.move(running, LEFT, deltaTime);
		camera.sidewaysMotion(running, LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		player.move(running, RIGHT, deltaTime);
		camera.sidewaysMotion(running, RIGHT, deltaTime);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.rotate(xoffset, yoffset, deltaTime);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}