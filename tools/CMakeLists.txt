cmake_minimum_required(VERSION 3.14...3.30)

project(
    JSON-128-LEMON
    VERSION 1.0.0
    DESCRIPTION "JSON-128-LEMON"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_C_FLAGS "-Wno-strict-prototypes")

add_executable(lemon lemon.c)
