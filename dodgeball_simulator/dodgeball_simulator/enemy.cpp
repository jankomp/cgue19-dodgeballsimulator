#include "enemy.h"
#include <iostream>

int runOrNot = 0, dir = 0, counter = 0;

enemy::enemy(glm::vec3 startPos)
{
	position = startPos;
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
}

void enemy::rotate(float rotation, float deltaTime) {
	front.x = cos(glm::radians(rotation));
	front.z = sin(glm::radians(rotation));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

}

void enemy::move(float deltaTime) {

	if (counter % 100 == 0) {
		runOrNot = rand() % 2;
		dir = rand() % 4;
	}


	float movementSpeed;
	if (runOrNot == 1) {
		movementSpeed = 1;
	}
	else {
		movementSpeed = 0.5;
	}
	float velocity = movementSpeed * deltaTime;


	if (dir == 0)
		position += front * velocity;
	if (dir == 1)
		position -= front * velocity;
	if (dir == 2)
		position += right * velocity;
	if (dir == 3)
		position -= right * velocity;

	std::cout << "Player: " << position.x << "," << position.y << "," << position.z << std::endl;

	counter = counter + 1;
}


glm::vec3 enemy::getPosition() {
	return position;
}

void enemy::updatePlayerCharacter() {

}