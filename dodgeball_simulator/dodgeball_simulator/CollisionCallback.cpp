#include "CollisionCallback.h"



CollisionCallback::CollisionCallback()
{
}


CollisionCallback::~CollisionCallback()
{
}

void PxSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) {
	//loop through all trigger-pairs of PhysX simulation
	for (PxU32 i = 0; i < pairs; i++)
	 {
		 //get current trigger actor & other actor info
		 //from current trigger-pair
		 const PxTriggerPair& curTriggerPair = pairs[i];
		 PxRigidActor* triggerActor = curTriggerPair.triggerActor; //enemy or character
		 PxRigidActor* otherActor = curTriggerPair.otherActor; //ball
	 }
}
