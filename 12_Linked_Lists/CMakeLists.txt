cmake_minimum_required(VERSION 3.10)
project(LinkedListProject)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/LinkedList.cpp
    src/Node.cpp
)

# Executable
add_executable(LinkedListProject ${SOURCES})

# Optionally add testing configuration here
