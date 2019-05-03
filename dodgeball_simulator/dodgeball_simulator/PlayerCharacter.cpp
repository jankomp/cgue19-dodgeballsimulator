#include "PlayerCharacter.h"
#include <iostream>


PlayerCharacter::PlayerCharacter(glm::vec3 startPos, Ball* newBall)
{
	position = startPos;
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	ball = newBall;
}

void PlayerCharacter::rotate(float rotation, float deltaTime) {
	front.x = cos(glm::radians(rotation));
	front.z = sin(glm::radians(rotation));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

}

int PlayerCharacter::collision()
{
	if (position.z >= 0 - 0.8)
	{
		return 1;
	}
	if (position.z <= -27 + 0.3)
	{
		return 2;
	}
	if (position.x >= 13.5 - 0.8)
	{
		return 3;
	}
	if (position.x <= -13.5 + 0.8)
	{
		return 4;
	}
	else
	{
		return 0;
	}
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

	if (collision() == 0) {
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position += right * velocity;
		if (direction == RIGHT)
			position -= right * velocity;
	}
	if (collision() == 1) {
		if (direction == FORWARD)
			position = position;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position += right * velocity;
		if (direction == RIGHT)
			position -= right * velocity;
	}
	if (collision() == 2) {
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position = position;
		if (direction == LEFT)
			position += right * velocity;
		if (direction == RIGHT)
			position -= right * velocity;
	}
	if (collision() == 3) {
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position = position;
		if (direction == RIGHT)
			position -= right * velocity;
	}
	if (collision() == 4) {
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position += right * velocity;
		if (direction == RIGHT)
			position = position;
	}

	




	std::cout << "Player: " << position.x << "," << position.y << "," << position.z << std::endl;
}

glm::vec3 PlayerCharacter::getPosition() {
	return position;
}

void PlayerCharacter::updatePlayerCharacter(glm::vec3 newPos) {
	position = newPos;
}

void PlayerCharacter::shootBall(glm::vec3 direction) {
	if (true) {
		shooting = true;
		ball->flyBall(position, direction);
	}
}

bool PlayerCharacter::shootingBall() {
	bool returnVal = shooting;
	shooting = false;
	return returnVal;
}