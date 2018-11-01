# - Main CMake buildscript for mpags-cypher

# - Set CMake requirements then declare project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# - When Makefiles are generated, output all command lines by default
set(CMAKE_VERBOSE_MAKEFILE ON)

# - Set the C++ Standard directly
set(CMAKE_CXX_STANDARD 14)

# - Declare the build of mpags-cipher main program
add_executable(mpags-cipher mpags-cipher.cpp MPAGSSCipher/TransformChar.cpp MPAGSSCipher/ProcessCommandLine.cpp MPAGSSCipher/CaesarCipher.cpp)

target_include_directories(mpags-cipher
PRIVATE MPAGSSCipher
)

# - Don't allow C++ Vendor Extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# - Use our standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

target_compile_features(mpags-cipher
	PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
)
