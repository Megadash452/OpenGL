cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC src/cpp/*.cpp)
add_executable(OpenGL external/glad.c ${SRC})

include_directories(src/headers)
include_directories(external/include)
link_directories(external/lib)
# TODO: add `Additional Dependencies` static library files