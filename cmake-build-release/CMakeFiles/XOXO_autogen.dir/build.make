# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "F:\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\white\OneDrive\Documents\GitHub\XOXO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\white\OneDrive\Documents\GitHub\XOXO\cmake-build-release

# Utility rule file for XOXO_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/XOXO_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/XOXO_autogen.dir/progress.make

CMakeFiles/XOXO_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\white\OneDrive\Documents\GitHub\XOXO\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target XOXO"
	"F:\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe" -E cmake_autogen C:/Users/white/OneDrive/Documents/GitHub/XOXO/cmake-build-release/CMakeFiles/XOXO_autogen.dir/AutogenInfo.json Release

XOXO_autogen: CMakeFiles/XOXO_autogen
XOXO_autogen: CMakeFiles/XOXO_autogen.dir/build.make
.PHONY : XOXO_autogen

# Rule to build all files generated by this target.
CMakeFiles/XOXO_autogen.dir/build: XOXO_autogen
.PHONY : CMakeFiles/XOXO_autogen.dir/build

CMakeFiles/XOXO_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\XOXO_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/XOXO_autogen.dir/clean

CMakeFiles/XOXO_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\white\OneDrive\Documents\GitHub\XOXO C:\Users\white\OneDrive\Documents\GitHub\XOXO C:\Users\white\OneDrive\Documents\GitHub\XOXO\cmake-build-release C:\Users\white\OneDrive\Documents\GitHub\XOXO\cmake-build-release C:\Users\white\OneDrive\Documents\GitHub\XOXO\cmake-build-release\CMakeFiles\XOXO_autogen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/XOXO_autogen.dir/depend

