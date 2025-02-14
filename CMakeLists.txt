cmake_minimum_required(VERSION 3.10)
project(BoidFlockingSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Include library header files
include_directories(Boid Flock)

# Add executable
add_executable(BoidFlockingSimulation src/main.cpp Boid/Boid.cpp Flock/Flock.cpp)

# Link the libraries
target_link_libraries(BoidFlockingSimulation PRIVATE sfml-system sfml-window sfml-graphics)