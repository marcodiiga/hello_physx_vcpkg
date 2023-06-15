# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)

# PLEASE CUSTOMIZE THESE TWO BEFORE IMPORTING PHYSX PACKAGE
##############################################################
# set(VCPKG_TARGET_TRIPLET x64-windows)
# set(VCPKG_CRT_LINKAGE dynamic)

# set(VCPKG_TARGET_TRIPLET x64-windows-static)
# set(VCPKG_CRT_LINKAGE static)

set(VCPKG_TARGET_TRIPLET x64-linux)
##############################################################

# Set the following variable to the location of your vcpkg local installation
set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_PREFIX_PATH "/home/alex/vcpkg/installed/x64-linux/share/omniverse-physx-sdk")

project(HelloPhysX)

add_executable(hello_physx main.cpp)

# Note: if the package cannot be found, check that you're using the right triplet
find_package(unofficial-omniverse-physx-sdk CONFIG REQUIRED)
target_link_libraries(hello_physx PRIVATE unofficial::omniverse-physx-sdk::sdk)

# Optional: import the defined target to copy over the GPU acceleration libraries (3rd party provided by NVIDIA)
if(TARGET unofficial::omniverse-physx-sdk::gpu-library)
    if(UNIX)
        # Add rpath setting to find so libraries on unix based systems
        set_target_properties(hello_physx PROPERTIES
            BUILD_WITH_INSTALL_RPATH TRUE
            INSTALL_RPATH "$ORIGIN"
        )
    endif()
    add_custom_command(TARGET hello_physx POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-library>
                    $<TARGET_FILE_DIR:hello_physx>)
    if(WIN32)
        add_custom_command(TARGET hello_physx POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        $<TARGET_FILE:unofficial::omniverse-physx-sdk::gpu-device-library>
                        $<TARGET_FILE_DIR:hello_physx>)
    endif()
else()
    message(WARNING "GPU acceleration library target not defined - GPU acceleration will NOT be available!")
endif()


