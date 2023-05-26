# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# PLEASE CUSTOMIZE THESE TWO BEFORE IMPORTING PHYSX PACKAGE
# set(VCPKG_TARGET_TRIPLET x64-windows-static)
# set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_TARGET_TRIPLET x64-linux)
# set(VCPKG_LIBRARY_LINKAGE dynamic)
##############################################################

# Set the following variable to the location of your vcpkg local installation
set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(HelloPhysX)

# find_package(OMNIVERSE-PHYSX-SDK REQUIRED)
# if (NOT OMNIVERSE-PHYSX-SDK_FOUND)
#     message(FATAL_ERROR "PhysX not found")
# endif()

add_executable(hello_physx main.cpp)

# Add rpath setting
set_target_properties(hello_physx PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
)

find_package(omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(hello_physx omniverse-physx-sdk)

# message(FATAL "YEAAA ${OMNIVERSE-PHYSX-SDK_CRT_LINKAGE}")
# if(WIN32)
#     set_property(TARGET hello_physx PROPERTY MSVC_RUNTIME_LIBRARY ${OMNIVERSE-PHYSX-SDK_CRT_LINKAGE})
# endif()

# Determine the suffix based on the build type
set(SUFFIX "bin")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(hello_physx PRIVATE _DEBUG)
    set(SUFFIX "debug/bin")
endif()

# Initialize GPU library name list
set(GPULIBNAMES "")

# Check if the target triplet includes specific substrings and set the GPU library names accordingly
string(FIND "${VCPKG_TARGET_TRIPLET}" "arm64" arm64_pos)
string(FIND "${VCPKG_TARGET_TRIPLET}" "linux" linux_pos)
string(FIND "${VCPKG_TARGET_TRIPLET}" "windows" windows_pos)

if(NOT arm64_pos EQUAL -1 OR NOT linux_pos EQUAL -1)
    list(APPEND GPULIBNAMES "libPhysXGpu_64.so")
elseif(NOT windows_pos EQUAL -1)
    list(APPEND GPULIBNAMES "PhysXGpu_64.dll" "PhysXDevice64.dll")
else()
    message(WARNING "Unsupported target architecture (arm64/linux/windows only) in triplet")
endif()

# Add a post build command to copy the GPU libraries if they were set
foreach(GPULIBNAME IN LISTS GPULIBNAMES)
    if(GPULIBNAME)
        add_custom_command(TARGET hello_physx POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/${SUFFIX}/${GPULIBNAME}"
                           $<TARGET_FILE_DIR:hello_physx>)
    endif()
endforeach()


# target_include_directories(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_INCLUDE_DIRS}")
# target_link_directories(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_RELEASE_LIBS_DIR}")
# target_link_libraries(hello_physx PRIVATE "${OMNIVERSE-PHYSX-SDK_LIBRARIES}")


