#include "physics.h"

using namespace physx;


physx::PxDefaultAllocator gDefaultAllocatorCallback;
physx::PxDefaultErrorCallback gDefaultErrorCallback;

physx::PxFoundation* gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
physx::PxPhysics* gPhysicsSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());
physx::PxScene* gScene = NULL;

CollisionCallback gContactReportCallback(NULL, NULL, NULL, NULL);

int countBallIdle = 0;

physx::PxRigidDynamic* ballActor;
physx::PxRigidDynamic* playerActor;
physx::PxRigidDynamic* enemy_characterActor;
physx::PxRigidDynamic* enemy2_characterActor;
physx::PxRigidDynamic* enemy3_characterActor;


PlayerCharacter* pplayer;
enemy* penemy_character;
enemy* penemy2_character;
enemy* penemy3_character;


physics::physics(PlayerCharacter* newplayer, enemy* newenemy_character, enemy* newenemy2_character, enemy* newenemy3_character) {
	pplayer = newplayer;
	penemy_character = newenemy_character;
	penemy2_character = newenemy2_character;
	penemy3_character = newenemy3_character;

	gContactReportCallback = CollisionCallback(pplayer, penemy_character, penemy2_character, penemy3_character);
}


void physics::setupScene() {
	//PxScene* gScene = NULL;
	//Creating scene
	PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	// Set Instance of CollisionCallback as SimulationEventCallback of Scene
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	//create the scene with the corresponding scene description
	gScene = gPhysicsSDK->createScene(sceneDesc);

	//Creating material
	PxMaterial* mMaterial =
		//static friction, dynamic friction, restitution
		gPhysicsSDK->createMaterial(0.5, 0.5, 0.35);

	//1-Creating static plane (floor)
	PxTransform floorPos = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* gymActor = gPhysicsSDK->createRigidStatic(floorPos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	//Creating walls
	PxTransform wall1Pos = PxTransform(PxVec3(0.0f, 0.0f, 27.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall1Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	PxTransform wall2Pos = PxTransform(PxVec3(0.0f, 0.0f, -27.0f), PxQuat(-PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall2Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	PxTransform wall3Pos = PxTransform(PxVec3(-13.5f, 0.0f, 0.0f));
	gymActor = gPhysicsSDK->createRigidStatic(wall3Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	PxTransform wall4Pos = PxTransform(PxVec3(13.5f, 0.0f, 0.0f), PxQuat(-PxPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall4Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	//1-Creating static plane (roof)
	PxTransform roofPos = PxTransform(PxVec3(0.0f, 12.0f, 0.0f), PxQuat(-PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* roofActor = gPhysicsSDK->createRigidStatic(roofPos);
	roofActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*roofActor);

	//creating sphere (ball)
	PxTransform ballPos = PxTransform(PxVec3(2.0f, 2.0f, -1.0f));
	ballActor = gPhysicsSDK->createRigidDynamic(ballPos);
	PxShape* ballShape = gPhysicsSDK->createShape(PxSphereGeometry(0.2), *mMaterial);
	//set filter data for collision detection (to detect what object is hit)
	PxFilterData filterData; filterData.word0 = 0;	filterData.word1 = 0; ballShape->setSimulationFilterData(filterData);
	ballActor->attachShape(*ballShape);
	gScene->addActor(*ballActor);

	//creating box (player)
	PxVec3 playerPos = PxVec3(0.0);
	playerPos.x = pplayer->getPosition().x;	playerPos.y = pplayer->getPosition().y;	playerPos.z = pplayer->getPosition().z;
	PxTransform playerPosition = PxTransform(playerPos);
	playerActor = gPhysicsSDK->createRigidDynamic(playerPosition);
	PxShape* playerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(2.0f, 4.0f, 2.0f)), *mMaterial);
	filterData.word0 = 2;	filterData.word1 = 0; playerShape->setSimulationFilterData(filterData);
	playerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	playerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	playerActor->attachShape(*playerShape);
	gScene->addActor(*playerActor);

	//creating boxes (enemys)
	PxVec3 enemy_characterPos = PxVec3(0.0);
	enemy_characterPos.x = penemy_character->getPosition().x;	enemy_characterPos.y = penemy_character->getPosition().y;	enemy_characterPos.z = penemy_character->getPosition().z;
	PxTransform enemy_characterPosition = PxTransform(enemy_characterPos);
	enemy_characterActor = gPhysicsSDK->createRigidDynamic(enemy_characterPosition);
	PxShape* triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 0; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy_characterActor);

	PxVec3 enemy2_characterPos = PxVec3(0.0);
	enemy2_characterPos.x = penemy2_character->getPosition().x;	enemy2_characterPos.y = penemy2_character->getPosition().y;	enemy2_characterPos.z = penemy2_character->getPosition().z;
	PxTransform enemy2_characterPosition = PxTransform(enemy2_characterPos);
	enemy2_characterActor = gPhysicsSDK->createRigidDynamic(enemy2_characterPosition);
	triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 1; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy2_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy2_characterActor);

	PxVec3 enemy3_characterPos = PxVec3(0.0);
	enemy3_characterPos.x = penemy3_character->getPosition().x;	enemy3_characterPos.y = penemy3_character->getPosition().y;	enemy3_characterPos.z = penemy3_character->getPosition().z;
	PxTransform enemy3_characterPosition = PxTransform(enemy3_characterPos);
	enemy3_characterActor = gPhysicsSDK->createRigidDynamic(enemy3_characterPosition);
	triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 2; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy3_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy3_characterActor);
}

void physics::releaseScene() {
	gScene->release();
	gPhysicsSDK->release();
}

void physics::stepPhysicSimulation(float deltaTime) {
	//advance the PhysX simulation by one step
	gScene->simulate(deltaTime);
	gScene->fetchResults(true);
}

void physics::dealBall(PlayerCharacter* player, Ball* ball, enemy* enemy_character, enemy* enemy2_character, enemy* enemy3_character) {
	//if the ball is idle it goes to a player in whos field it currently is
	if (ballActor->isSleeping() && !ball->caught) {
		ball->caught = true;
		//detect in which field the ball is
		if (ballActor->getGlobalPose().p.z <= 0) {
			player->sethasball(true);
		}
		else {
			//give the ball to a randomly selected enemy
			bool enemyfound = false;
			ball->shot = true;
			while (!enemyfound) {
				int random = rand() % 3;
				if (random == 0 && enemy_character->getActive()) {
					enemy_character->sethasball(true); enemyfound = true;
				}
				else if (random == 1 && enemy2_character->getActive()) {
					enemy2_character->sethasball(true); enemyfound = true;
				}
				else if (random == 2 && enemy3_character->getActive()) {
					enemy3_character->sethasball(true); enemyfound = true;
				}
			}
		}
	}
}

void physics::simulateBallShot(float deltaTime, PlayerCharacter* player, Ball* ball, enemy* enemy_character, enemy* enemy2_character, enemy* enemy3_character, Camera* camera) {
	//ball is shot, when the player presses the left mouse-button or immediatly when an enemy gets the ball
	if (ball->isShot()) {
		if (player->gethasball()) {
			//start the ball a little bit in front of the player, so it doesn't collide with itself
			glm::vec3 playerPos = player->getPosition() + camera->getViewDirection();
			playerPos.y += 2.0;
			ballActor->setGlobalPose(PxTransform(PxVec3(playerPos.x, playerPos.y, playerPos.z)));
			ball->caught = false;
			gContactReportCallback.setPlayerShooting(true);
			player->sethasball(false);
		}
		else if (enemy_character->getActive() && enemy_character->gethasball()) {
			//start the ball a little bit in front of the enemy, so it doesn't collide with itself
			glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy_character->getPosition();	enemyPos.y += 2.0;
			glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
			enemyPos += shotdirection;
			ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
			ball->caught = false;
			enemy_character->shootBall();
			gContactReportCallback.setPlayerShooting(false);
		}
		else if (enemy2_character->getActive() && enemy2_character->gethasball()) {
			//start the ball a little bit in front of the enemy, so it doesn't collide with itself
			glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy2_character->getPosition();	enemyPos.y += 2.0;
			glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
			enemyPos += shotdirection;
			ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
			ball->caught = false;
			enemy2_character->shootBall();
			gContactReportCallback.setPlayerShooting(false);
		}
		else if (enemy3_character->getActive() && enemy3_character->gethasball()) {
			//start the ball a little bit in front of the enemy, so it doesn't collide with itself
			glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy3_character->getPosition();	enemyPos.y += 2.0;
			glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
			enemyPos += shotdirection;
			ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
			ball->caught = false;
			enemy3_character->shootBall();
			gContactReportCallback.setPlayerShooting(false);
		}
		//set firstCollision (global variable) to true -> next collision counts
		gContactReportCallback.setFirstCollision(true);
	}

	//get from where ball i shot and add force to the ball as long as the character is shooting (120 loop iterations)
	if (player->shootingBall(deltaTime)) {
		glm::vec3 grafic = camera->getViewDirection();
		PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + 0.75; direction.z = grafic.z;
		direction *= 14.0;
		ballActor->addForce(direction);
	}
	else if (enemy_character->shootingBall(deltaTime)) {
		glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
		glm::vec3 enemyPos = enemy_character->getPosition();	enemyPos.y += 2.0;	enemyPos.z -= 2.0;
		glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
		float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
		PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;
		direction *= 26.5;
		ballActor->addForce(direction);
	}
	else if (enemy2_character->shootingBall(deltaTime)) {
		glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
		glm::vec3 enemyPos = enemy2_character->getPosition();
		enemyPos.y += 2.0;	enemyPos.z -= 2.0;
		glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
		float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
		PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;
		direction *= 26.5;
		ballActor->addForce(direction);
	}
	else if (enemy3_character->shootingBall(deltaTime)) {
		glm::vec3 playerPos = player->getPosition(); playerPos.y += 2.0;
		glm::vec3 enemyPos = enemy3_character->getPosition();
		enemyPos.y += 2.0;	enemyPos.z -= 2.0;
		glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
		float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
		PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;
		direction *= 26.5;
		ballActor->addForce(direction);
	}
	else {
		//if nobody is shooting anymore clear the forces acting on the ball
		ballActor->clearForce();
		//if the ball is hardly moving it gets send to sleep so that it goes to a character
		if (ballActor->getLinearVelocity().magnitude() < 0.5) {

			if (countBallIdle++ > 60) {
				ballActor->putToSleep();
				countBallIdle = 0;
			}
		}
	}
}

PxVec3 physics::getBallPos() {
	return ballActor->getGlobalPose().p;
}

void physics::setPlayerPos(physx::PxVec3 playerPos) {
	playerActor->setGlobalPose(PxTransform(playerPos));
}

void physics::setEnemyPositions(physx::PxVec3 enmy1Pos, physx::PxVec3 enmy2Pos, physx::PxVec3 enmy3Pos) {
	//enemies
	enemy_characterActor->setGlobalPose(PxTransform(enmy1Pos));
	enemy2_characterActor->setGlobalPose(PxTransform(enmy2Pos));
	enemy3_characterActor->setGlobalPose(PxTransform(enmy3Pos));

}