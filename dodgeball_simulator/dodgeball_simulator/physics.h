#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>

physx::PxFoundation* foundation;
physx::PxPhysics* physics;
physx::PxScene* scene;

physx::PxDefaultAllocator gDefaultAllocatorCallback;
physx::PxDefaultErrorCallback gDefaultErrorCallback;

bool initPhysics() {
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (foundation == nullptr) {
		return false;
	}

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale());

	if (physics == nullptr) {
		return false;
	}

	return true;
}