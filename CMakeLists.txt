cmake_minimum_required(VERSION 3.17)
project(pantheon)

set(CMAKE_CXX_STANDARD 14)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/lib/glad)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(pantheon ${SOURCES} src/Triangle.cpp src/Triangle.h)

#glfw
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)

#glad
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)

target_link_libraries(pantheon glfw glad)