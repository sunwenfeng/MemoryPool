# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files (x86)\JetBrains\CLion 2016.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sun\Desktop\MemoryPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sun\Desktop\MemoryPool\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MemoryPool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MemoryPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MemoryPool.dir/flags.make

CMakeFiles/MemoryPool.dir/main.cpp.obj: CMakeFiles/MemoryPool.dir/flags.make
CMakeFiles/MemoryPool.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sun\Desktop\MemoryPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MemoryPool.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MemoryPool.dir\main.cpp.obj -c C:\Users\sun\Desktop\MemoryPool\main.cpp

CMakeFiles/MemoryPool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MemoryPool.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sun\Desktop\MemoryPool\main.cpp > CMakeFiles\MemoryPool.dir\main.cpp.i

CMakeFiles/MemoryPool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MemoryPool.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sun\Desktop\MemoryPool\main.cpp -o CMakeFiles\MemoryPool.dir\main.cpp.s

CMakeFiles/MemoryPool.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/MemoryPool.dir/main.cpp.obj.requires

CMakeFiles/MemoryPool.dir/main.cpp.obj.provides: CMakeFiles/MemoryPool.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\MemoryPool.dir\build.make CMakeFiles/MemoryPool.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/MemoryPool.dir/main.cpp.obj.provides

CMakeFiles/MemoryPool.dir/main.cpp.obj.provides.build: CMakeFiles/MemoryPool.dir/main.cpp.obj


# Object files for target MemoryPool
MemoryPool_OBJECTS = \
"CMakeFiles/MemoryPool.dir/main.cpp.obj"

# External object files for target MemoryPool
MemoryPool_EXTERNAL_OBJECTS =

MemoryPool.exe: CMakeFiles/MemoryPool.dir/main.cpp.obj
MemoryPool.exe: CMakeFiles/MemoryPool.dir/build.make
MemoryPool.exe: CMakeFiles/MemoryPool.dir/linklibs.rsp
MemoryPool.exe: CMakeFiles/MemoryPool.dir/objects1.rsp
MemoryPool.exe: CMakeFiles/MemoryPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sun\Desktop\MemoryPool\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MemoryPool.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MemoryPool.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MemoryPool.dir/build: MemoryPool.exe

.PHONY : CMakeFiles/MemoryPool.dir/build

CMakeFiles/MemoryPool.dir/requires: CMakeFiles/MemoryPool.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/MemoryPool.dir/requires

CMakeFiles/MemoryPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MemoryPool.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MemoryPool.dir/clean

CMakeFiles/MemoryPool.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sun\Desktop\MemoryPool C:\Users\sun\Desktop\MemoryPool C:\Users\sun\Desktop\MemoryPool\cmake-build-debug C:\Users\sun\Desktop\MemoryPool\cmake-build-debug C:\Users\sun\Desktop\MemoryPool\cmake-build-debug\CMakeFiles\MemoryPool.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MemoryPool.dir/depend

