cmake_minimum_required(VERSION 3.10)
project(BoidFlockingSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow users to specify paths for SFML Widgets
option(USE_CUSTOM_SFML_WIDGETS "Use custom SFML Widgets path" OFF)

if (USE_CUSTOM_SFML_WIDGETS)
    set(SFML_WIDGETS_LIBRARY_PATH "" CACHE PATH "Path to SFML Widgets library")
    set(SFML_WIDGETS_HEADER_PATH "" CACHE PATH "Path to SFML Widgets headers")
else()
    set(SFML_WIDGETS_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libs/sfml-widgets/lib")
    set(SFML_WIDGETS_HEADER_PATH "${CMAKE_SOURCE_DIR}/libs/sfml-widgets/src/Gui")
endif()

# Find SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Include library header files
include_directories(
    ${SFML_WIDGETS_HEADER_PATH}
    ${CMAKE_SOURCE_DIR}/Boid
    ${CMAKE_SOURCE_DIR}/Flock
    ${SFML_INCLUDE_DIR}
)

# Link SFML Widgets library dynamically
link_directories(${SFML_WIDGETS_LIBRARY_PATH})

# Add executable
add_executable(BoidFlockingSimulation 
    src/main.cpp 
    Boid/Boid.cpp 
    Flock/Flock.cpp
)

# Install widget styles to a specific directory
install(DIRECTORY ${CMAKE_SOURCE_DIR}/widget_styles/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/myapp/widget_styles
    FILES_MATCHING PATTERN "*.png" PATTERN "*.ttf" PATTERN "*.jpg"
)

# Copy necessary resources to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/widget_styles/tahoma.ttf DESTINATION ${CMAKE_BINARY_DIR}/widget_styles)
file(COPY ${CMAKE_SOURCE_DIR}/widget_styles/texture-default.png DESTINATION ${CMAKE_BINARY_DIR}/widget_styles)

# Link the libraries
target_link_libraries(BoidFlockingSimulation PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-widgets
)
