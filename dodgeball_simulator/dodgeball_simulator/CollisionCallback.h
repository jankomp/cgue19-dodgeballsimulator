#pragma once
#include "physics.h"

using namespace physx;

class CollisionCallback: PxSimulationEventCallback
{
public:
	CollisionCallback();
	~CollisionCallback();
	void  PxSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count);
};

