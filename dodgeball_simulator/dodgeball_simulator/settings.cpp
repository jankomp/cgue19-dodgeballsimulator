#include "settings.h"

extern enemy enemy_character;
extern enemy enemy2_character;
extern enemy enemy3_character;

bool running = false;
PlayerCharacter *player;
Camera *camera;
float deltaTime = 0.0f;

/* --------------------------------------------- */
// Load settings.ini
/* --------------------------------------------- */
INIReader reader("settings.ini");

int SCR_WIDTH = reader.GetInteger("window", "width", 800);
int SCR_HEIGHT = reader.GetInteger("window", "height", 800);
int refresh_rate = reader.GetInteger("window", "refresh_rate", 60);
bool fullscreen = reader.GetBoolean("window", "fullscreen", false);
float brightness = reader.GetReal("window", "brightness", 1.0f);


int screen = 1;
bool head_up_display = true;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

settings::settings(PlayerCharacter *playP, Camera *cam) 
{
	player = playP;
	camera = cam;
}

settings::settings() {}

void settings::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (screen == 2) {
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
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		if (screen == 1) {
			screen = 2;
			camera->camReset(player, camera->getPosition());
			enemy_character.setPosition(glm::vec3(0.0, 0.0, 6.0));
			enemy2_character.setPosition(glm::vec3(-3.0, 0.0, 3.5));
			enemy3_character.setPosition(glm::vec3(3.0, 0.0, 3.5));
		}
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		camera->camReset(player, camera->getPosition());
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE) {
		head_up_display = !head_up_display;
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void settings::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void settings::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	if (screen != 1) {
		camera->rotate(xoffset, yoffset, deltaTime);
	}
}

void settings::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if(screen == 2)
			player->shootBall();
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
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

float settings::getBrightness()
{
	return brightness;
}

void settings::setDeltaTime(float toSet)
{
	deltaTime = toSet;
}

void settings::setScreen(int scr) 
{
	screen = scr;
}



