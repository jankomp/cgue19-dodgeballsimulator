#include "CollisionCallback.h"
#include <iostream>

bool firstCollision;

CollisionCallback::CollisionCallback(PlayerCharacter* newPlayer, enemy* newEnemy1, enemy* newEnemy2, enemy* newEnemy3)
{
	player = newPlayer;
	enemy1 = newEnemy1;
	enemy2 = newEnemy2;
	enemy3 = newEnemy3;
}


CollisionCallback::~CollisionCallback() {}

void CollisionCallback::setFirstCollision(bool value) {
	firstCollision = value;
}


void CollisionCallback::onTrigger(PxTriggerPair* pairs, PxU32 count) 
{
	if(firstCollision){
	//loop through all trigger-pairs of PhysX simulation
		for (PxU32 i = 0; i < 1; i++)
		{
			//get current trigger actor & other actor info
			//from current trigger-pair
			const PxTriggerPair& curTriggerPair = pairs[i];

			PxFilterData otherFilterData = curTriggerPair.otherShape->getSimulationFilterData(); //word0 = 0 : ball or word0 = 1 : other enemy
			PxU32 word0otherTrigger = otherFilterData.word0;
			PxFilterData triggerFilterData = curTriggerPair.triggerShape->getSimulationFilterData(); // word0 = 1 : enemy or word0 = 2 : player
			PxU32 word0mainTrigger = triggerFilterData.word0;
			PxU32 word1mainTrigger = triggerFilterData.word1;

			if (word0otherTrigger == 0) {
				if (word0mainTrigger == 1) {
					switch (word1mainTrigger) {
					case 0: enemy1->hit(); break;
					case 1: enemy2->hit(); break;
					case 2: enemy3->hit(); break;
					}
				}
				else if (word0mainTrigger == 2) {
					player->hit();
				}
			}
		}
		firstCollision = false;
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

			std::cout << "on Contact" << std::endl;

		}
	};

	void CollisionCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) {};

