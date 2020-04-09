cmake_minimum_required(VERSION 3.7)

project(cucurucho)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(cucurucho main.cpp)
target_link_libraries(cucurucho ${SDL2_LIBRARIES})