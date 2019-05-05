#pragma once
#include "physics.h"

using namespace physx;

class CollisionCallback: PxSimulationEventCallback
{
public:
	CollisionCallback();
	~CollisionCallback();

	void  PxSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count);

	void PxSimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);

	void PxSimulationEventCallback::onWake(PxActor** actors, PxU32 count);

	void PxSimulationEventCallback::onSleep(PxActor** actors, PxU32 count);

	void PxSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

	void PxSimulationEventCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count);

};

