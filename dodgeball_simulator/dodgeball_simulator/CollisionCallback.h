#pragma once
#include <physx/PxPhysicsAPI.h>

using namespace physx;

class CollisionCallback: public PxSimulationEventCallback
{
public:
	CollisionCallback();
	~CollisionCallback();

	void onTrigger(PxTriggerPair* pairs, PxU32 count);

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);

	void onWake(PxActor** actors, PxU32 count);

	void onSleep(PxActor** actors, PxU32 count);

	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

	void onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);

};