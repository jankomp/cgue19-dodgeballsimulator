/*#include "PlayerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	
}

PlayerCharacter::PlayerCharacter(Camera* newCamera)
{
	camera = newCamera;
}

void PlayerCharacter::rotate(float rotation, float deltaTime) {
	
}

void PlayerCharacter::move(bool running, Movement direction, float deltaTime) {
	float movementSpeed;
	if (running) {
		movementSpeed = 50;
	}
	else {
		movementSpeed = 30;
	}
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;

	//camera->updatePlayerPosition(position);
}

void PlayerCharacter::updatePlayerCharacter() {

}
*/


