# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangxinhao/CLionProjects/Programming_Practice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/add76.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/add76.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/add76.dir/flags.make

CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o: CMakeFiles/add76.dir/flags.make
CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o: ../编程填空：输出指定结果.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o -c /Users/wangxinhao/CLionProjects/Programming_Practice/编程填空：输出指定结果.cpp

CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wangxinhao/CLionProjects/Programming_Practice/编程填空：输出指定结果.cpp > CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.i

CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wangxinhao/CLionProjects/Programming_Practice/编程填空：输出指定结果.cpp -o CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.s

# Object files for target add76
add76_OBJECTS = \
"CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o"

# External object files for target add76
add76_EXTERNAL_OBJECTS =

add76: CMakeFiles/add76.dir/编程填空：输出指定结果.cpp.o
add76: CMakeFiles/add76.dir/build.make
add76: CMakeFiles/add76.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable add76"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/add76.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/add76.dir/build: add76

.PHONY : CMakeFiles/add76.dir/build

CMakeFiles/add76.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/add76.dir/cmake_clean.cmake
.PHONY : CMakeFiles/add76.dir/clean

CMakeFiles/add76.dir/depend:
	cd /Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangxinhao/CLionProjects/Programming_Practice /Users/wangxinhao/CLionProjects/Programming_Practice /Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug /Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug /Users/wangxinhao/CLionProjects/Programming_Practice/cmake-build-debug/CMakeFiles/add76.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/add76.dir/depend
