#include <iostream>
#include <string>
#include "event-handlers.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
using std::string;


#define True GL_TRUE
#define False GL_FALSE
#define Any GLFW_DONT_CARE

#define Win_Width 800
#define Win_Min_Width 167
#define Win_Height 600
#define Win_Min_Height 100


int main() {


    // initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    //glfwWindowHint(GLFW_FLOATING, True); // window is "always on top". Let user decide in context-menu
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, True); // transparent window


    // create a window of size 800x600 called "LearnOpenGL"
    GLFWwindow* window = glfwCreateWindow(Win_Width, Win_Height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    // set minimum size to 200x200. max size is any
    glfwSetWindowSizeLimits(window, Win_Min_Width, Win_Min_Height, Any, Any);
    // the space OpenGL will work with relative to the window
    glViewport(0, 0, Win_Width, Win_Height);
    // register events
    glfwSetFramebufferSizeCallback(window, onWindowResize);


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        onKeyDown(window, GLFW_KEY_ESCAPE, [&window]() {
            closeWindow(window);
        });

        // clear: fill the color buffer with this color. Acts as a background color
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // transition from one frame to another with no flickers
        glfwSwapBuffers(window);
        // call events
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}