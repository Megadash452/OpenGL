cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC src/cpp/*.cpp)
add_executable(OpenGL external/glad.c ${SRC} src/cpp/examples.cpp src/headers/examples.h)

# get include/header files
include_directories(src/headers)
include_directories(external/include)

# get lib files
file(GLOB LIB external/lib/*.lib)
target_link_directories(OpenGL PRIVATE external/lib)
target_link_libraries(OpenGL PRIVATE ${LIB})

# build GLFW from source
#add_subdirectory(external/glfw)
#target_link_libraries(OpenGL PRIVATE glfw)

#TODO: try to build GLFW from source again and get the 'glfw3.pdb' file