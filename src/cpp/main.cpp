#include <iostream>
#include <string>
#include "event-handlers.h"
// glad must always be included before glfw
#include "glad/glad.h"
#include "GLFW/glfw3.h"
using std::string;


#define True GL_TRUE
#define False GL_FALSE
#define Any GLFW_DONT_CARE
#define Float GL_FLOAT

#define Win_Width 800
#define Win_Min_Width 167
#define Win_Height 600
#define Win_Min_Height 100

struct ShaderProgram
{
    unsigned int GL_program;

    /*! @brief takes care of loading shaders
     * @param use_now if true will bind the shader program to be used
     * */
    ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src, bool use_now)
    {
        const char* used_VS_src;
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        int no_errors;

        // if no vertex shader was provided, use default
        if (vertex_shader_src == nullptr)
            // very basic shader that doesn't do much
            used_VS_src = "#version 330 core\n"
                          "layout (location = 0) in vec3 aPos;"
                          "void main() {"
                          "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
                          "}";
        else
            used_VS_src = vertex_shader_src;

        // compile vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &used_VS_src, nullptr);
        glCompileShader(vertex_shader);
        // check for errors
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &no_errors);
        if (!no_errors)
        {
            char error_info[512];
            glGetShaderInfoLog(vertex_shader, 512, nullptr, error_info);
            std::cout << "Compilation Error: Failed to compile shader <VERTEX SHADER>\n" << error_info << std::endl;
        }


        const char* used_FS_src;
        // if no fragment shader was provided, use default
        if (fragment_shader_src == nullptr)
            used_FS_src = "#version 330 core\n"
                          "out vec4 fragment_color;"
                          "void main() {"
                          "    fragment_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                          "}";
        else
            used_FS_src = fragment_shader_src;

        // compile fragment shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &used_FS_src, nullptr);
        glCompileShader(fragment_shader);
        // check for errors
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &no_errors);
        if (!no_errors)
        {
            char error_info[512];
            glGetShaderInfoLog(fragment_shader, 512, nullptr, error_info);
            std::cout << "Compilation Error: Failed to compile shader <FRAGMENT SHADER>\n" << error_info << std::endl;
        }


        // shader program to run shaders
        this->GL_program = glCreateProgram();
        glAttachShader(this->GL_program, vertex_shader);
        glAttachShader(this->GL_program, fragment_shader);
        glLinkProgram(this->GL_program);
        if (use_now)
            this->bind();
        // check for errors
        glGetProgramiv(this->GL_program, GL_LINK_STATUS, &no_errors);
        if (!no_errors)
        {
            char error_info[512];
            glGetShaderInfoLog(fragment_shader, 512, nullptr, error_info);
            std::cout << "Link Error: Failed to bind shader program <FRAGMENT SHADER>\n" << error_info << std::endl;
        }

        // these are already compiled and used by this->program, so they have no use now
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    void use() const  { glUseProgram(this->GL_program); }
    //! @brief alias to ShaderProgram::use()
    void bind() const { glUseProgram(this->GL_program); }
};


int main() {
    std::cout << "init\n";

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


    // -- Load Shaders ---
    ShaderProgram basic_SP{ nullptr, nullptr, true };

    // --- DRAWING TRIANGLE ---
    //! @brief defined points of a triangle to be drawn
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // no defined color
        0.5f,  -0.5f, 0.0f, // no defined color
        0.0f,  0.5f,  0.0f  // no defined color
    };
    //! @brief A pointer to some data in the GPU. Contains an array of vertices.
    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);

    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    // (can bind multiple buffers as long as they are different types)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    /*! move the vertices data from RAM (CPU) to VRAM (GPU).
     *  Do this the least amount of times possible (or do it in bulk) because it is slow
     *  @param usage Options:
     *                  GL_STREAM_DRAW:  is written once,  is read few times
     *                  GL_STATIC_DRAW:  is written a lot, is read few times
     *                  GL_DYNAMIC_DRAW: is written a lot, is read a lot     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // create attribute object
    // first param is layout location (matches with the vertex shader)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // use attribute object with current vertex array
    glEnableVertexAttribArray(0);


    // render loop
    while(!glfwWindowShouldClose(window))
    {
        onKeyDown(window, GLFW_KEY_ESCAPE, [&window]() {
            closeWindow(window);
        });

        // clear: fill the color buffer with this color. Acts as a background color
        glClearColor(0.0f, 0.0f, 0.0f, 0.75f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basic_SP.GL_program);
        glBindVertexArray(vertex_array);
        // render vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // transition from one frame to another with no flickers
        glfwSwapBuffers(window);
        // call events
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}