# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pepe/Documents/wro-2022_23/pigpio_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pepe/Documents/wro-2022_23/pigpio_test/build

# Include any dependencies generated for this target.
include CMakeFiles/pigpio_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pigpio_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pigpio_test.dir/flags.make

CMakeFiles/pigpio_test.dir/main.cpp.o: CMakeFiles/pigpio_test.dir/flags.make
CMakeFiles/pigpio_test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pepe/Documents/wro-2022_23/pigpio_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pigpio_test.dir/main.cpp.o"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pigpio_test.dir/main.cpp.o -c /home/pepe/Documents/wro-2022_23/pigpio_test/main.cpp

CMakeFiles/pigpio_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pigpio_test.dir/main.cpp.i"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pepe/Documents/wro-2022_23/pigpio_test/main.cpp > CMakeFiles/pigpio_test.dir/main.cpp.i

CMakeFiles/pigpio_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pigpio_test.dir/main.cpp.s"
	/usr/bin/aarch64-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pepe/Documents/wro-2022_23/pigpio_test/main.cpp -o CMakeFiles/pigpio_test.dir/main.cpp.s

# Object files for target pigpio_test
pigpio_test_OBJECTS = \
"CMakeFiles/pigpio_test.dir/main.cpp.o"

# External object files for target pigpio_test
pigpio_test_EXTERNAL_OBJECTS =

pigpio_test: CMakeFiles/pigpio_test.dir/main.cpp.o
pigpio_test: CMakeFiles/pigpio_test.dir/build.make
pigpio_test: /usr/local/lib/libpigpio.so
pigpio_test: CMakeFiles/pigpio_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pepe/Documents/wro-2022_23/pigpio_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pigpio_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pigpio_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pigpio_test.dir/build: pigpio_test

.PHONY : CMakeFiles/pigpio_test.dir/build

CMakeFiles/pigpio_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pigpio_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pigpio_test.dir/clean

CMakeFiles/pigpio_test.dir/depend:
	cd /home/pepe/Documents/wro-2022_23/pigpio_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pepe/Documents/wro-2022_23/pigpio_test /home/pepe/Documents/wro-2022_23/pigpio_test /home/pepe/Documents/wro-2022_23/pigpio_test/build /home/pepe/Documents/wro-2022_23/pigpio_test/build /home/pepe/Documents/wro-2022_23/pigpio_test/build/CMakeFiles/pigpio_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pigpio_test.dir/depend

