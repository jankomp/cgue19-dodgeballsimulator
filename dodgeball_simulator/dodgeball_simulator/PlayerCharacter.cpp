#include "PlayerCharacter.h"
#include <iostream>





PlayerCharacter::PlayerCharacter(glm::vec3 startPos)
{
	position = startPos;
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
}

void PlayerCharacter::rotate(float rotation, float deltaTime) {
	front.x = cos(glm::radians(rotation));
	front.z = sin(glm::radians(rotation));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

}

void PlayerCharacter::move(bool running, Movement direction, float deltaTime) {
	float movementSpeed;
 	if (running) {
		movementSpeed = 20;
	}
	else {
		movementSpeed = 5;
	}
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position += right * velocity;
	if (direction == RIGHT)
		position -= right * velocity;

	std::cout << "Player: " << position.x << "," << position.y << "," << position.z << std::endl;
}

glm::vec3 PlayerCharacter::getPosition() {
	return position;
}

void PlayerCharacter::updatePlayerCharacter(glm::vec3 newPos) {
	position = newPos;
}

void shootBall(glm::vec3 direction) {

}