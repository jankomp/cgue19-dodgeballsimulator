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

	//#ifdef _DEBUG
	//	pvd = PxCreatePvd(*_foundation);
	//	transport = physx::PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
	//	pvd->connect(*_transport, physx::PxPvdInstrumentationFlag::eALL);
	//	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale(), true, _pvd);
	//#else
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale());
	//#endif


	if (physics == nullptr) {
		return false;
	}
	//dispatcher = physx::PxDefaultCpuDispatcherCreate(4);
	//if (dispatcher == nullptr) {
	//	return false;
	//}

	//_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *_foundation, physx::PxCookingParams(physx::PxTolerancesScale()));
	//if (!_cooking) {
	//	LOG_ERROR(PxCreateCooking failed!);
	//}

	//// Create Scene
	//physx::PxSceneDesc sceneDesc(_physics->getTolerancesScale());
	//sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	//sceneDesc.cpuDispatcher = _dispatcher;
	//sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	//_scene = _physics->createScene(sceneDesc);

	//// Create Material
	//_material = _physics->createMaterial(0.5f, 0.5f, 0.6f);


	return true;
}