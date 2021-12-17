#pragma once
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#ifndef OPENGL_EVENT_HANDLERS_H
#define OPENGL_EVENT_HANDLERS_H

/*! @brief Event handler for when the user resizes the window
 *  @param width  New width of the window
 *  @param height New height of the window */
void onWindowResize(GLFWwindow* window, int width, int height);

#endif //OPENGL_EVENT_HANDLERS_H