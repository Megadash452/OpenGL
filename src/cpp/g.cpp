#include "shader-program.h"
#include "event-handlers.h"
#include "primitive.h"
#include "texture.h"
#include "util.h"
using std::string;

#define Win_Width      800
#define Win_Min_Width  167
#define Win_Height     600
#define Win_Min_Height 100

#define Shaders_Path  "../../src/shaders"
#define Resource_Path "../../res"


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(Win_Width, Win_Height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }
    glfwSetWindowSizeLimits(window, Win_Min_Width, Win_Min_Height, Any, Any);
    glfwSetFramebufferSizeCallback(window, onWindowResize);



    // --- THE SQUARE ---
    ShaderProgram tex_shader{
        Shaders_Path"/texture.vert.glsl",
        Shaders_Path"/texture.frag.glsl"
    };
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int vertex_buffer, vertex_array, element_array;
    glGenVertexArrays(1, &vertex_array);
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &element_array);
    //
    glBindVertexArray(vertex_array);
    //
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(Resource_Path"/opengl.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //
    tex_shader.set_uniform("texture_data", 0);
    // --- ---


    // TODO: image kind of shows now but the entire rectangle has the accent color
    // ^^^^  only happens when second color arg in glTexImage2d is RGB


    glViewport(0, 0, Win_Width, Win_Height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.75f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        tex_shader.use();
        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &element_array);

    glfwTerminate();
    return 0;
}