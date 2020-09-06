cmake_minimum_required(VERSION 3.17)
project(pantheon)

set(CMAKE_CXX_STANDARD 14)
file(GLOB SOURCES src/*.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)

add_executable(pantheon ${SOURCES})
target_link_libraries(pantheon glfw)