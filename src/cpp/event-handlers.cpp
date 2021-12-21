#include "event-handlers.h"

void closeWindow(GLFWwindow* window)
{
    glfwSetWindowShouldClose(window, true);
}

void onWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void onKeyDown(GLFWwindow* window, int key, const std::function<void()>& handler)
{
    if(glfwGetKey(window, key) == GLFW_PRESS)
        handler();
}