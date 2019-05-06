#pragma once
#include <physx/PxPhysicsAPI.h>
#include "PlayerCharacter.h"
#include "enemy.h"

using namespace physx;

class CollisionCallback: public PxSimulationEventCallback
{

	PlayerCharacter* player;
	enemy* enemy1;
	enemy* enemy2;
	enemy* enemy3;

public:
	CollisionCallback(PlayerCharacter* newPlayer, enemy* newEnemy1, enemy* newEnemy2, enemy* newEnemy3);
	~CollisionCallback();

	void onTrigger(PxTriggerPair* pairs, PxU32 count);

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);

	void onWake(PxActor** actors, PxU32 count);

	void onSleep(PxActor** actors, PxU32 count);

	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

	void onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);

};