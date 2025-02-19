cmake_minimum_required(VERSION 3.10)
project(BoidFlockingSimulation)

set(SFML_WIDGETS_LIBRARY_PATH "/home/carlios/cpp-projects/sfml-widgets/lib")
set(SFML_WIDGETS_HEADER_PATH "/home/carlios/cpp-projects/sfml-widgets/src/Gui")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find SFML
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Include library header files
include_directories(
    ${SFML_WIDGETS_HEADER_PATH}
    ${PROJECT_SOURCE_DIR}/Boid
    ${PROJECT_SOURCE_DIR}/Flock
    ${SFML_INCLUDE_DIR}
)

# Link the library
link_directories(${SFML_WIDGETS_LIBRARY_PATH})

# Add executable
add_executable(BoidFlockingSimulation 
    src/main.cpp 
    Boid/Boid.cpp 
    Flock/Flock.cpp
)

# Install widget styles to a specific directory
install(DIRECTORY ${WIDGET_STYLES_PATH}/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/myapp/widget_styles
    FILES_MATCHING PATTERN "*.png" PATTERN "*.ttf" PATTERN "*.jpg"
)

file(COPY ${PROJECT_SOURCE_DIR}/widget_styles/tahoma.ttf DESTINATION ${CMAKE_BINARY_DIR}/widget_styles)
file(COPY ${PROJECT_SOURCE_DIR}/widget_styles/texture-default.png DESTINATION ${CMAKE_BINARY_DIR}/widget_styles)

# Link the libraries
target_link_libraries(BoidFlockingSimulation PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-widgets
)