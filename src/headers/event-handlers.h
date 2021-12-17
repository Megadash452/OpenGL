#pragma once
#include <functional>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#ifndef OPENGL_EVENT_HANDLERS_H
#define OPENGL_EVENT_HANDLERS_H

//! @brief Close specified window
void closeWindow(GLFWwindow* window);

/*! @brief Event handler for when the user resizes the window
 *  @param width  New width of the window
 *  @param height New height of the window */
void onWindowResize(GLFWwindow* window, int width, int height);

/*! @brief Check if a key or mouse button is being pressed
 *  @param window GLFW window to be queried
 *  @param key The key being pressed
 *  @param handler a function that will be called when the event is triggered
 * */
void onKeyDown(GLFWwindow* window, int key, const std::function<void()>& handler);

#endif //OPENGL_EVENT_HANDLERS_H