# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# PLEASE CUSTOMIZE THESE TWO BEFORE IMPORTING PHYSX PACKAGE
# set(VCPKG_TARGET_TRIPLET x64-windows-static)
# set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_TARGET_TRIPLET x64-windows)
# set(VCPKG_LIBRARY_LINKAGE dynamic)
##############################################################

# Set the following variable to the location of your vcpkg local installation
set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(HelloPhysX)

find_package(OMNIVERSE-PHYSX-SDK REQUIRED)
if (NOT OMNIVERSE-PHYSX-SDK_FOUND)
    message(FATAL_ERROR "PhysX not found")
endif()

add_executable(hello_physx main.cpp)


message(FATAL "YEAAA ${OMNIVERSE-PHYSX-SDK_CRT_LINKAGE}")
if(WIN32)
    set_property(TARGET hello_physx PROPERTY MSVC_RUNTIME_LIBRARY ${OMNIVERSE-PHYSX-SDK_CRT_LINKAGE})
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(hello_physx PRIVATE NDEBUG)
endif()

target_include_directories(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_INCLUDE_DIRS}")
target_link_directories(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_RELEASE_LIBS_DIR}")
target_link_libraries(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_LIBRARIES}")


