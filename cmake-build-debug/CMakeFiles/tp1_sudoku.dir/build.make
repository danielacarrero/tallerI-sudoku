# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tp1_sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tp1_sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp1_sudoku.dir/flags.make

CMakeFiles/tp1_sudoku.dir/src/main.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tp1_sudoku.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/main.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/main.c

CMakeFiles/tp1_sudoku.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/main.c > CMakeFiles/tp1_sudoku.dir/src/main.c.i

CMakeFiles/tp1_sudoku.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/main.c -o CMakeFiles/tp1_sudoku.dir/src/main.c.s

CMakeFiles/tp1_sudoku.dir/src/errors.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/errors.c.o: ../src/errors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tp1_sudoku.dir/src/errors.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/errors.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/errors.c

CMakeFiles/tp1_sudoku.dir/src/errors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/errors.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/errors.c > CMakeFiles/tp1_sudoku.dir/src/errors.c.i

CMakeFiles/tp1_sudoku.dir/src/errors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/errors.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/errors.c -o CMakeFiles/tp1_sudoku.dir/src/errors.c.s

CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o: ../src/adt_socket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_socket.c

CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_socket.c > CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.i

CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_socket.c -o CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.s

CMakeFiles/tp1_sudoku.dir/src/client.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/client.c.o: ../src/client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/tp1_sudoku.dir/src/client.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/client.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/client.c

CMakeFiles/tp1_sudoku.dir/src/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/client.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/client.c > CMakeFiles/tp1_sudoku.dir/src/client.c.i

CMakeFiles/tp1_sudoku.dir/src/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/client.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/client.c -o CMakeFiles/tp1_sudoku.dir/src/client.c.s

CMakeFiles/tp1_sudoku.dir/src/server.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/server.c.o: ../src/server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/tp1_sudoku.dir/src/server.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/server.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/server.c

CMakeFiles/tp1_sudoku.dir/src/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/server.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/server.c > CMakeFiles/tp1_sudoku.dir/src/server.c.i

CMakeFiles/tp1_sudoku.dir/src/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/server.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/server.c -o CMakeFiles/tp1_sudoku.dir/src/server.c.s

CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o: CMakeFiles/tp1_sudoku.dir/flags.make
CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o: ../src/adt_sudoku.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o   -c /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_sudoku.c

CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_sudoku.c > CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.i

CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/src/adt_sudoku.c -o CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.s

# Object files for target tp1_sudoku
tp1_sudoku_OBJECTS = \
"CMakeFiles/tp1_sudoku.dir/src/main.c.o" \
"CMakeFiles/tp1_sudoku.dir/src/errors.c.o" \
"CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o" \
"CMakeFiles/tp1_sudoku.dir/src/client.c.o" \
"CMakeFiles/tp1_sudoku.dir/src/server.c.o" \
"CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o"

# External object files for target tp1_sudoku
tp1_sudoku_EXTERNAL_OBJECTS =

tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/main.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/errors.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/adt_socket.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/client.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/server.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/src/adt_sudoku.c.o
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/build.make
tp1_sudoku: CMakeFiles/tp1_sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable tp1_sudoku"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp1_sudoku.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp1_sudoku.dir/build: tp1_sudoku

.PHONY : CMakeFiles/tp1_sudoku.dir/build

CMakeFiles/tp1_sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp1_sudoku.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp1_sudoku.dir/clean

CMakeFiles/tp1_sudoku.dir/depend:
	cd /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug /Users/dcarrero/Documents/FIUBA/tallerI/TPs/TP1/tp1-sudoku/cmake-build-debug/CMakeFiles/tp1_sudoku.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp1_sudoku.dir/depend

