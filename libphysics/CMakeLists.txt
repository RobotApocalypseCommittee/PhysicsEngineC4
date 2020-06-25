cmake_minimum_required(VERSION 3.10)
project(libphysics-c4 LANGUAGES CXX)

add_library(libphysics-c4 src/main.cpp src/collision.cpp src/core.cpp src/world.cpp src/circle.cpp src/object.cpp src/polygon.cpp)

add_library(PhysicsEngineC4::physics ALIAS libphysics-c4)

#Set target properties
target_include_directories(libphysics-c4
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )