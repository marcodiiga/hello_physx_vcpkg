#include "PxConfig.h"
#include "PxPhysicsAPI.h"
#include <iostream>

using namespace physx;

int main(int argc, char** argv) {
    std::cout << "Starting PhysX up.." << std::endl;
    PxDefaultAllocator allocator;
    PxDefaultErrorCallback error_callback;
    auto foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, error_callback);
    auto physics_sdk = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, nullptr);
    std::cout << "PhysX set up" << std::endl;
    PX_RELEASE(physics_sdk);
    PX_RELEASE(foundation);
    std::cout << "Shutting down.." << std::endl;
}