#include "enemy.h"
#include <iostream>

extern int scorePlayer;

int runOrNot = 0, dir = 0, counter = 0;

enemy::enemy(glm::vec3 startPos, Ball* newBall)
{
	position = startPos;
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	active = true;
	ball = newBall;
}

void enemy::rotate(float rotation, float deltaTime) {
	front.x = cos(glm::radians(rotation));
	front.z = sin(glm::radians(rotation));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

}

void enemy::move(float deltaTime) {

	if (counter % 100 == 1) {
		runOrNot = rand() % 2;
		dir = rand() % 4;
	}
	
	float movementSpeed;
	if (runOrNot == 1) {
		movementSpeed = 2;
	}
	else {
		movementSpeed = 1;
	}
	float velocity = movementSpeed * deltaTime;

	switch (dir) {
		case 0: {
			float newz = position.z + velocity;
			if (newz <= 26.0)
				position.z = newz;
			else
				dir = 1;
			break;
		}
		case 1: {
			float newz = position.z - velocity;
			if (newz >= 0.5)
				position.z = newz;
			else
				dir = 0;
			break;
			}
		case 2: {
			float newx = position.x + velocity;
			if (newx <= 12.5)
				position.x = newx;
			else
				dir = 3;
			break;
			}
		case 3: {
			float newx = position.x - velocity;
			if (newx >= -12.5)
				position.x = newx;
			else
				dir = 2;
			break;
			}
	}

	//std::cout << "Player: " << position.x << "," << position.y << "," << position.z << std::endl;

	counter = counter + 1;
}



glm::vec3 enemy::getPosition() {
	return position;
}

void enemy::setPosition(glm::vec3 newPos) {
	position = newPos;
}

void enemy::sethasball(bool possession) {
	hasBall = possession;
}

bool enemy::gethasball() {
	return hasBall;
}

bool enemy::getActive() {
	return active;
}

void enemy::hit () {
	active = false;
	//player->increaseScore();
	scorePlayer = scorePlayer + 1;
	Shader textShader("shaders/text.vert", "shaders/text.frag");
	TextRenderer text;
	text.Load("fonts/arial.ttf", 80);
	text.RenderText(textShader, "+1", ((float)1920 / 2) - 20, ((float)1800 / 2) - 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}


void enemy::shootBall() {
	if (hasBall) {
		count = 120;
		shooting = true;
		ball->flyBall();
		hasBall = false;
	}
}

bool enemy::shootingBall() {
	bool returnVal = shooting;
	if (count-- < 0) {
		shooting = false;
	}
	return returnVal;
}
