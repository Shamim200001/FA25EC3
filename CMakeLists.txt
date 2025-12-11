cmake_minimum_required(VERSION 3.10)
project(TextBasedRPG)

set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(TextBasedRPG main.cpp)

# Include current directory
target_include_directories(TextBasedRPG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})