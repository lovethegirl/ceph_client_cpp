# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/workspace/code/client/ceph_client_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/code/client/ceph_client_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/ceph-client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ceph-client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ceph-client.dir/flags.make

CMakeFiles/ceph-client.dir/src/cephclient.cpp.o: CMakeFiles/ceph-client.dir/flags.make
CMakeFiles/ceph-client.dir/src/cephclient.cpp.o: ../src/cephclient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/code/client/ceph_client_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ceph-client.dir/src/cephclient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceph-client.dir/src/cephclient.cpp.o -c /root/workspace/code/client/ceph_client_cpp/src/cephclient.cpp

CMakeFiles/ceph-client.dir/src/cephclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceph-client.dir/src/cephclient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/code/client/ceph_client_cpp/src/cephclient.cpp > CMakeFiles/ceph-client.dir/src/cephclient.cpp.i

CMakeFiles/ceph-client.dir/src/cephclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceph-client.dir/src/cephclient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/code/client/ceph_client_cpp/src/cephclient.cpp -o CMakeFiles/ceph-client.dir/src/cephclient.cpp.s

CMakeFiles/ceph-client.dir/src/main.cpp.o: CMakeFiles/ceph-client.dir/flags.make
CMakeFiles/ceph-client.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/code/client/ceph_client_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ceph-client.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ceph-client.dir/src/main.cpp.o -c /root/workspace/code/client/ceph_client_cpp/src/main.cpp

CMakeFiles/ceph-client.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ceph-client.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/code/client/ceph_client_cpp/src/main.cpp > CMakeFiles/ceph-client.dir/src/main.cpp.i

CMakeFiles/ceph-client.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ceph-client.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/code/client/ceph_client_cpp/src/main.cpp -o CMakeFiles/ceph-client.dir/src/main.cpp.s

# Object files for target ceph-client
ceph__client_OBJECTS = \
"CMakeFiles/ceph-client.dir/src/cephclient.cpp.o" \
"CMakeFiles/ceph-client.dir/src/main.cpp.o"

# External object files for target ceph-client
ceph__client_EXTERNAL_OBJECTS =

../ceph-client: CMakeFiles/ceph-client.dir/src/cephclient.cpp.o
../ceph-client: CMakeFiles/ceph-client.dir/src/main.cpp.o
../ceph-client: CMakeFiles/ceph-client.dir/build.make
../ceph-client: CMakeFiles/ceph-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/code/client/ceph_client_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../ceph-client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ceph-client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ceph-client.dir/build: ../ceph-client

.PHONY : CMakeFiles/ceph-client.dir/build

CMakeFiles/ceph-client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ceph-client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ceph-client.dir/clean

CMakeFiles/ceph-client.dir/depend:
	cd /root/workspace/code/client/ceph_client_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/code/client/ceph_client_cpp /root/workspace/code/client/ceph_client_cpp /root/workspace/code/client/ceph_client_cpp/build /root/workspace/code/client/ceph_client_cpp/build /root/workspace/code/client/ceph_client_cpp/build/CMakeFiles/ceph-client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ceph-client.dir/depend

