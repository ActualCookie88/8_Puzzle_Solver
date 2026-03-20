cmake_minimum_required(VERSION 3.16)
project(EightPuzzleSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(header)

# Add executable and source files
add_executable(8puzzle
    8puzzle.cpp
    src/globals.cpp
    src/Heuristics.cpp
    src/Puzzle.cpp
    src/Search.cpp
)