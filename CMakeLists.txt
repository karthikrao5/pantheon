cmake_minimum_required(VERSION 3.17)
project(pantheon)

set(CMAKE_CXX_STANDARD 14)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/lib/glad)

#need to tell cmake where the glm cmake is. removing this after building it once
#does not cause errors since it is cached. remove the cmake-build-debug folder
#in order to "refresh" the cache
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib/glm/cmake)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(pantheon ${SOURCES} src/common/debugBreak.h src/common/Texture.h)

#glfw
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)

#glad
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)

#glm
find_package(glm REQUIRED)

target_link_libraries(pantheon glfw glad glm::glm)