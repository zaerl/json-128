cmake_minimum_required(VERSION 3.14...3.30)

project(
    JSON-128
    VERSION 1.0.0
    DESCRIPTION "JSON-128"
    LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wno-unused-parameter")

# Debug flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
# set(CMAKE_C_FLAGS_DEBUG "-g -O0 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_TEST "-g -O0 -DJ128_TEST")
# set(CMAKE_C_FLAGS_TEST "-g -O0 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -DJ128_TEST")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Test" CACHE STRING "Configurations" FORCE)

# Mojibake library
add_subdirectory(src)

# Tests
add_subdirectory(tests)

# Lemon parser
add_subdirectory(tools)
