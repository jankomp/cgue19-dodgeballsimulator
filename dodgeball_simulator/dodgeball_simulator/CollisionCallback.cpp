#include "CollisionCallback.h"



CollisionCallback::CollisionCallback()
{
}


CollisionCallback::~CollisionCallback()
{
}

void PxSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) {
	//loop through all trigger-pairs of PhysX simulation
	for (PxU32 i = 0; i < 2; i++)
	{
		//get current trigger actor & other actor info
		//from current trigger-pair
		const PxTriggerPair& curTriggerPair = pairs[i];
		PxRigidActor* triggerActor = curTriggerPair.triggerActor; //enemy or character
		PxRigidActor* otherActor = curTriggerPair.otherActor; //ball
	}
}
	void PxSimulationEventCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {};

	void PxSimulationEventCallback::onWake(PxActor** actors, PxU32 count) {};

	void PxSimulationEventCallback::onSleep(PxActor** actors, PxU32 count) {};

	void PxSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {};

	void PxSimulationEventCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {};

