# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/carlios/cpp-projects/boid_flocking_simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/carlios/cpp-projects/boid_flocking_simulation/build

# Include any dependencies generated for this target.
include CMakeFiles/BoidFlockingSimulation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BoidFlockingSimulation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BoidFlockingSimulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BoidFlockingSimulation.dir/flags.make

CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/flags.make
CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlios/cpp-projects/boid_flocking_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o -MF CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o.d -o CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o -c /home/carlios/cpp-projects/boid_flocking_simulation/src/main.cpp

CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlios/cpp-projects/boid_flocking_simulation/src/main.cpp > CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.i

CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlios/cpp-projects/boid_flocking_simulation/src/main.cpp -o CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.s

CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/flags.make
CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o: ../Boid/Boid.cpp
CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlios/cpp-projects/boid_flocking_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o -MF CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o.d -o CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o -c /home/carlios/cpp-projects/boid_flocking_simulation/Boid/Boid.cpp

CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlios/cpp-projects/boid_flocking_simulation/Boid/Boid.cpp > CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.i

CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlios/cpp-projects/boid_flocking_simulation/Boid/Boid.cpp -o CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.s

CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/flags.make
CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o: ../Flock/Flock.cpp
CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o: CMakeFiles/BoidFlockingSimulation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/carlios/cpp-projects/boid_flocking_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o -MF CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o.d -o CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o -c /home/carlios/cpp-projects/boid_flocking_simulation/Flock/Flock.cpp

CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/carlios/cpp-projects/boid_flocking_simulation/Flock/Flock.cpp > CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.i

CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/carlios/cpp-projects/boid_flocking_simulation/Flock/Flock.cpp -o CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.s

# Object files for target BoidFlockingSimulation
BoidFlockingSimulation_OBJECTS = \
"CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o" \
"CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o" \
"CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o"

# External object files for target BoidFlockingSimulation
BoidFlockingSimulation_EXTERNAL_OBJECTS =

BoidFlockingSimulation: CMakeFiles/BoidFlockingSimulation.dir/src/main.cpp.o
BoidFlockingSimulation: CMakeFiles/BoidFlockingSimulation.dir/Boid/Boid.cpp.o
BoidFlockingSimulation: CMakeFiles/BoidFlockingSimulation.dir/Flock/Flock.cpp.o
BoidFlockingSimulation: CMakeFiles/BoidFlockingSimulation.dir/build.make
BoidFlockingSimulation: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
BoidFlockingSimulation: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
BoidFlockingSimulation: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
BoidFlockingSimulation: CMakeFiles/BoidFlockingSimulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/carlios/cpp-projects/boid_flocking_simulation/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable BoidFlockingSimulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BoidFlockingSimulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BoidFlockingSimulation.dir/build: BoidFlockingSimulation
.PHONY : CMakeFiles/BoidFlockingSimulation.dir/build

CMakeFiles/BoidFlockingSimulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BoidFlockingSimulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BoidFlockingSimulation.dir/clean

CMakeFiles/BoidFlockingSimulation.dir/depend:
	cd /home/carlios/cpp-projects/boid_flocking_simulation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/carlios/cpp-projects/boid_flocking_simulation /home/carlios/cpp-projects/boid_flocking_simulation /home/carlios/cpp-projects/boid_flocking_simulation/build /home/carlios/cpp-projects/boid_flocking_simulation/build /home/carlios/cpp-projects/boid_flocking_simulation/build/CMakeFiles/BoidFlockingSimulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BoidFlockingSimulation.dir/depend

