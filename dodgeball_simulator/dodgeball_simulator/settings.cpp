#include "settings.h"

bool running = false;
PlayerCharacter *player;
Camera *camera;
extern float deltaTime = 0.0f;
int screen = 2;
bool head_up_display = true;
bool firstMouse = true;
float lastX = 1920 / 2.0f;
float lastY = 1800 / 2.0f;

settings::settings(PlayerCharacter *playP, Camera *cam) {
	player = playP;
	camera = cam;
}

settings::settings() {

}

void settings::processInput(GLFWwindow *window)
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
		player->move(running, FORWARD, deltaTime);
		camera->sidewaysMotion();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		player->move(running, BACKWARD, deltaTime);
		camera->sidewaysMotion();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		player->move(running, LEFT, deltaTime);
		camera->sidewaysMotion();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		player->move(running, RIGHT, deltaTime);
		camera->sidewaysMotion();
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		screen = 2;
		//glfwSetTime(0);
		//camera->camReset(&player, camPos);
		//enemy_character.updateEnemy(glm::vec3(0.0, 0.0, 6.0));
		//enemy2_character.updateEnemy(glm::vec3(-3.0, 0.0, 3.5));
		//enemy3_character.updateEnemy(glm::vec3(3.0, 0.0, 3.5));
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		//camera->camReset(&player, camPos);
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		head_up_display = true;
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void settings::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void settings::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	camera->rotate(xoffset, yoffset, deltaTime);
}

void settings::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//player->shootBall(camera.getViewDirection);
		player->shootBall();
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void settings::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

int settings::getScreen() 
{
	return screen;
}

bool settings::headUpDisplay()
{
	return head_up_display;
}

float settings::getDeltaTime() 
{
	return deltaTime;
}

void settings::setDeltaTime(float toSet)
{
	deltaTime = toSet;
}