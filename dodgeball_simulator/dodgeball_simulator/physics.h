#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>

#include "PlayerCharacter.h"
#include "enemy.h"
#include "Camera.h"
#include "CollisionCallback.h"


class physics {
	public:
		physics(PlayerCharacter* player, enemy* enemy_character, enemy* enemy2_character, enemy* enemy3_character);

		void setupScene();
		void releaseScene();

		void stepPhysicSimulation(float deltaTime);
		void dealBall(PlayerCharacter* player, Ball* ball, enemy* enemy_character, enemy* enemy2_character, enemy* enemy3_character);
		void simulateBallShot(float deltaTime, PlayerCharacter* player, Ball* ball, enemy* enemy_character, enemy* enemy2_character, enemy* enemy3_character, Camera* camera);
		physx::PxVec3 getBallPos();
		void setPlayerPos(physx::PxVec3 playerPos);
		void setEnemyPositions(physx::PxVec3 enmy1Pos, physx::PxVec3 enmy2Pos, physx::PxVec3 enmy3Pos);
};