#include "event-handlers.h"

void onWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}