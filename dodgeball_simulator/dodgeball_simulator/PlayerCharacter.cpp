#include "PlayerCharacter.h"
#include <iostream>


PlayerCharacter::PlayerCharacter(glm::vec3 startPos, Ball* newBall)
{
	position = startPos;
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	ball = newBall;
	lifes = 3;
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

	if (direction == FORWARD) {
		float newz = position.z + velocity;
		if (newz <= -0.5)
		{
			position.z = newz;
		}
	}
	if (direction == BACKWARD) {
		float newz = position.z - velocity;
		if (newz >= -26.0)
		{
			position.z = newz;
		}
	}
	if (direction == LEFT){
		float newx = position.x + velocity;
		if (newx <= 12.5)
		{
			position.x = newx;
		}
	}
	if (direction == RIGHT){
		float newx = position.x - velocity;
		if (newx >= -12.5)
		{
			position.x = newx;
		}
	}
	
	//std::cout << "Player: " << position.x << "," << position.y << "," << position.z << std::endl;
}

glm::vec3 PlayerCharacter::getPosition() {
	return position;
}

void PlayerCharacter::updatePlayerCharacter(glm::vec3 newPos) {
	position = newPos;
}

void PlayerCharacter::shootBall(glm::vec3 direction) {
	if (hasBall) {
		count = 120;
		shooting = true;
		ball->flyBall(position, direction);
	}
}

bool PlayerCharacter::shootingBall() {
	bool returnVal = shooting;
	if (count-- < 0) {
		shooting = false;
	}
	return returnVal;
}

void PlayerCharacter::sethasball(bool possession) {
	hasBall = possession;
}

bool PlayerCharacter::gethasball() {
	return hasBall;
}

int PlayerCharacter::getLifes() {
	return lifes;
}

int PlayerCharacter::getScore() {
	return score;
}

void PlayerCharacter::increaseScore() {
	score = score + 1;
}

void PlayerCharacter::hit() {
	lifes = lifes - 1;
	//scoreEnemy = scoreEnemy + 1;
	Shader textShader("shaders/text.vert", "shaders/text.frag");
	TextRenderer text;
	text.Load("fonts/arial.ttf", 80);
	text.RenderText(textShader, "-1", ((float)1920 / 2) - 20, ((float)1800 / 2) - 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}