# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ginnsato/VisualStudioProjects/CS250-Project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ginnsato/VisualStudioProjects/CS250-Project1/build

# Include any dependencies generated for this target.
include CMakeFiles/image-soa.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image-soa.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image-soa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image-soa.dir/flags.make

CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o: CMakeFiles/image-soa.dir/flags.make
CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o: /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-soa/main-soa.cpp
CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o: CMakeFiles/image-soa.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o -MF CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o.d -o CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o -c /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-soa/main-soa.cpp

CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-soa/main-soa.cpp > CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.i

CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ginnsato/VisualStudioProjects/CS250-Project1/image-soa/main-soa.cpp -o CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.s

# Object files for target image-soa
image__soa_OBJECTS = \
"CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o"

# External object files for target image-soa
image__soa_EXTERNAL_OBJECTS =

image-soa: CMakeFiles/image-soa.dir/image-soa/main-soa.cpp.o
image-soa: CMakeFiles/image-soa.dir/build.make
image-soa: libcommon.a
image-soa: libsoa.a
image-soa: CMakeFiles/image-soa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable image-soa"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image-soa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image-soa.dir/build: image-soa
.PHONY : CMakeFiles/image-soa.dir/build

CMakeFiles/image-soa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image-soa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image-soa.dir/clean

CMakeFiles/image-soa.dir/depend:
	cd /Users/ginnsato/VisualStudioProjects/CS250-Project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ginnsato/VisualStudioProjects/CS250-Project1 /Users/ginnsato/VisualStudioProjects/CS250-Project1 /Users/ginnsato/VisualStudioProjects/CS250-Project1/build /Users/ginnsato/VisualStudioProjects/CS250-Project1/build /Users/ginnsato/VisualStudioProjects/CS250-Project1/build/CMakeFiles/image-soa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/image-soa.dir/depend

