#ifndef OPENGL_UTIL_H
#define OPENGL_UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <exception>
#include "vec.h"
// glad must always be included before glfw
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define True         GL_TRUE
#define False        GL_FALSE
#define Any          GLFW_DONT_CARE
#define Int          GL_INT
#define Unsigned_Int GL_UNSIGNED_INT
#define Float        GL_FLOAT


std::string read_file(const char* filename);


#endif //OPENGL_UTIL_H
