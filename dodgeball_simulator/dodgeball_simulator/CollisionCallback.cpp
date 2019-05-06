#include "CollisionCallback.h"
#include <iostream>



CollisionCallback::CollisionCallback()
{
}


CollisionCallback::~CollisionCallback()
{
}

void CollisionCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) {
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
	void CollisionCallback::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {};

	void CollisionCallback::onWake(PxActor** actors, PxU32 count) {};

	void CollisionCallback::onSleep(PxActor** actors, PxU32 count) {};

	void CollisionCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
		const PxU32 buff = 64; //buffer size
		PxContactPairPoint contacts[buff];
		//loop through all contact pairs of PhysX simulation
		for (PxU32 i = 0; i < nbPairs; i++)
		{
			//extract contant info from current contact-pair
			const PxContactPair& curContactPair = pairs[i];
			PxU32 nbContacts = curContactPair.extractContacts
			(contacts, buff);
			for (PxU32 j = 0; j < nbContacts; j++)
			{
				//print all positions of contact.
				PxVec3 point = contacts[j].position;
				std::cout << "Contact point("<<point.x <<" "<< point.y<<" "<<point.x<<")\n";
			}
		}
	};

	void CollisionCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {};

