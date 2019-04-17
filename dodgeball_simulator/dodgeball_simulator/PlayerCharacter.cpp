#include "PlayerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	front = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	modelMat = glm::mat4(1.0);
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	modelMat = glm::scale(modelMat, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
}

void PlayerCharacter::rotate(float rotation, float deltaTime) {
	front.x = cos(glm::radians(rotation));
	front.z = sin(glm::radians(rotation));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

	modelMat = glm::rotate_slow(modelMat, rotation, glm::vec3(0.0, 1.0, 0.0));
}

void PlayerCharacter::move(bool running, Movement direction, float deltaTime) {
	float movementSpeed;
	glm::vec3 movement;
	if (running) {
		movementSpeed = 50;
	}
	else {
		movementSpeed = 30;
	}
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		movement = front * velocity;
		position += movement;
	if (direction == BACKWARD)
		movement = -(front * velocity);
		position += movement;
	if (direction == LEFT)
		movement = right * velocity;
		position += movement;
	if (direction == RIGHT)
		movement = -(right * velocity);
		position += movement;

	modelMat = glm::translate(modelMat, movement);

}

glm::vec3 PlayerCharacter::getPosition() {
	return position;
}

glm::mat4 PlayerCharacter::getModelMat(){
	return modelMat;
}


void PlayerCharacter::updatePlayerCharacter() {

}



