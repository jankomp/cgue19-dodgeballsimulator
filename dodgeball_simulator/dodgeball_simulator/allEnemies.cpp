#include "allEnemies.h"



allEnemies::allEnemies()
{
	score = 0;
}


int allEnemies::getScore() {
	return score;
}

void allEnemies::increaseScore() {
	score = score + 1;
}

void allEnemies::draw(Shader &gameShader) {

}

allEnemies::~allEnemies()
{
}
