# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\applications\cmake\cmake-3.30.3-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = D:\applications\cmake\cmake-3.30.3-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build"

# Include any dependencies generated for this target.
include CMakeFiles/hellobinary.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hellobinary.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hellobinary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hellobinary.dir/flags.make

CMakeFiles/hellobinary.dir/main.cpp.obj: CMakeFiles/hellobinary.dir/flags.make
CMakeFiles/hellobinary.dir/main.cpp.obj: CMakeFiles/hellobinary.dir/includes_CXX.rsp
CMakeFiles/hellobinary.dir/main.cpp.obj: D:/courses/embedded\ course/Embedded\ system/Cmake/Labs/Lab4/main.cpp
CMakeFiles/hellobinary.dir/main.cpp.obj: CMakeFiles/hellobinary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hellobinary.dir/main.cpp.obj"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hellobinary.dir/main.cpp.obj -MF CMakeFiles\hellobinary.dir\main.cpp.obj.d -o CMakeFiles\hellobinary.dir\main.cpp.obj -c "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\main.cpp"

CMakeFiles/hellobinary.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hellobinary.dir/main.cpp.i"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\main.cpp" > CMakeFiles\hellobinary.dir\main.cpp.i

CMakeFiles/hellobinary.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hellobinary.dir/main.cpp.s"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\main.cpp" -o CMakeFiles\hellobinary.dir\main.cpp.s

CMakeFiles/hellobinary.dir/src/calc.cpp.obj: CMakeFiles/hellobinary.dir/flags.make
CMakeFiles/hellobinary.dir/src/calc.cpp.obj: CMakeFiles/hellobinary.dir/includes_CXX.rsp
CMakeFiles/hellobinary.dir/src/calc.cpp.obj: D:/courses/embedded\ course/Embedded\ system/Cmake/Labs/Lab4/src/calc.cpp
CMakeFiles/hellobinary.dir/src/calc.cpp.obj: CMakeFiles/hellobinary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hellobinary.dir/src/calc.cpp.obj"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hellobinary.dir/src/calc.cpp.obj -MF CMakeFiles\hellobinary.dir\src\calc.cpp.obj.d -o CMakeFiles\hellobinary.dir\src\calc.cpp.obj -c "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\src\calc.cpp"

CMakeFiles/hellobinary.dir/src/calc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hellobinary.dir/src/calc.cpp.i"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\src\calc.cpp" > CMakeFiles\hellobinary.dir\src\calc.cpp.i

CMakeFiles/hellobinary.dir/src/calc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hellobinary.dir/src/calc.cpp.s"
	D:\applications\eclipse\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\src\calc.cpp" -o CMakeFiles\hellobinary.dir\src\calc.cpp.s

# Object files for target hellobinary
hellobinary_OBJECTS = \
"CMakeFiles/hellobinary.dir/main.cpp.obj" \
"CMakeFiles/hellobinary.dir/src/calc.cpp.obj"

# External object files for target hellobinary
hellobinary_EXTERNAL_OBJECTS =

hellobinary.exe: CMakeFiles/hellobinary.dir/main.cpp.obj
hellobinary.exe: CMakeFiles/hellobinary.dir/src/calc.cpp.obj
hellobinary.exe: CMakeFiles/hellobinary.dir/build.make
hellobinary.exe: lib/libwifi_lib.a
hellobinary.exe: CMakeFiles/hellobinary.dir/linkLibs.rsp
hellobinary.exe: CMakeFiles/hellobinary.dir/objects1.rsp
hellobinary.exe: CMakeFiles/hellobinary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hellobinary.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hellobinary.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hellobinary.dir/build: hellobinary.exe
.PHONY : CMakeFiles/hellobinary.dir/build

CMakeFiles/hellobinary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hellobinary.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hellobinary.dir/clean

CMakeFiles/hellobinary.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4" "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4" "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build" "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build" "D:\courses\embedded course\Embedded system\Cmake\Labs\Lab4\build\CMakeFiles\hellobinary.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/hellobinary.dir/depend

