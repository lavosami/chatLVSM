# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /Library/Frameworks/Python.framework/Versions/3.11/lib/python3.11/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /Library/Frameworks/Python.framework/Versions/3.11/lib/python3.11/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/start_client.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/start_client.cpp.o: /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/start_client.cpp
CMakeFiles/client.dir/start_client.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/start_client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/start_client.cpp.o -MF CMakeFiles/client.dir/start_client.cpp.o.d -o CMakeFiles/client.dir/start_client.cpp.o -c /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/start_client.cpp

CMakeFiles/client.dir/start_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client.dir/start_client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/start_client.cpp > CMakeFiles/client.dir/start_client.cpp.i

CMakeFiles/client.dir/start_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client.dir/start_client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/start_client.cpp -o CMakeFiles/client.dir/start_client.cpp.s

CMakeFiles/client.dir/Client.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/Client.cpp.o: /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/Client.cpp
CMakeFiles/client.dir/Client.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/Client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/Client.cpp.o -MF CMakeFiles/client.dir/Client.cpp.o.d -o CMakeFiles/client.dir/Client.cpp.o -c /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/Client.cpp

CMakeFiles/client.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/client.dir/Client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/Client.cpp > CMakeFiles/client.dir/Client.cpp.i

CMakeFiles/client.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/client.dir/Client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/Client.cpp -o CMakeFiles/client.dir/Client.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/start_client.cpp.o" \
"CMakeFiles/client.dir/Client.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/start_client.cpp.o
client: CMakeFiles/client.dir/Client.cpp.o
client: CMakeFiles/client.dir/build.make
client: /usr/local/lib/libboost_system-mt.dylib
client: /usr/local/lib/libboost_thread-mt.dylib
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build /Users/lavosami/Downloads/Code/CPProjects/chatLVSM/client/build/CMakeFiles/client.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/client.dir/depend

