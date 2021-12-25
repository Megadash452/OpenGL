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
    // initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    // glfwWindowHint(GLFW_FLOATING, True); // window is "always on top". Let user decide in context-menu
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


    // --- Define Shapes (work like masks)---
    ShaderProgram basic_shader{  };
    primitive::Rectangle rectangle{ vec2<float>{-1, 0.5}, vec2<float>{1, 1} };

    ShaderProgram tex_shader{
        Shaders_Path"/texture.vert.glsl",
        Shaders_Path"/texture.frag.glsl"
    };
    stbi_set_flip_vertically_on_load(true); // flip textures on the y-axis when loading them
    Texture heart_tex{ Resource_Path"/heart.png" };
    primitive::Shape2D tex_rectangle{
        std::array<float, 4*3 + 4*4 + 4*2> {
           //position //color       // tex_coord
            0, 1, 0,   0, 1, 0, 1,   0, 1, //    top left
            0, 0, 0,   1, 0, 0, 1,   0, 0, // bottom left
            1, 1, 0,   0, 1, 0, 1,   1, 1, //    top right
            1, 0, 0,   0, 0, 1, 1,   1, 0  // bottom right
        }, 3 + 4 + 2,
        std::array<unsigned int, 6> {
            0, 1, 3,  0, 2, 3
        }
    };

    // ShaderProgram uniform_color_shader{ nullptr, Shaders_Path"/uniform-color.frag.glsl" };
    // uniform_color_shader.set_uniform("color", {0.5f, 0.4f, 0.3f, 0.0f});
    // primitive::Triangle triangle{ std::array<float, 3*3> {
    //     0.0f, -0.5f, 0.0f, // bottom left
    //     1.0f, -0.5f, 0.0f, // bottom right
    //     0.5f,  0.5f, 0.0f, //    top middle
    // } };
    //
    // ShaderProgram gradient_shader{
    //     Shaders_Path"/gradient.vert.glsl",
    //     Shaders_Path"/gradient.frag.glsl"
    // };
    // // triangle acts like a mask?? // doesn't blend with other shapes and bg
    // primitive::Shape2D gradient_triangle{
    //     std::array<float, 3*3 + 4*3> {
    //         //position        //color
    //         -0.5f, -1.0f, 0,   1, 0, 0, 0.0, // bottom left
    //          0.0f,  0.0f, 0,   0, 1, 0, 0.0, //    top middle
    //          0.5f, -1.0f, 0,   0, 0, 1, 0.0  // bottom right
    //     }, 7,
    //     std::array<unsigned int, 3> {
    //         0, 1, 2
    //     }
    // };


    // -- set texture uniforms
    tex_shader.set_uniform("texture_data", 0);


    //! @brief Fill the color buffer with this color. Acts as a background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.75f);

    // draw in WireFrame mode
    /*! @brief Set which mode to draw shapes. DEFAULT: GL_Fill
     *  @param face which side of the triangle to apply this to
     *  @param mode what to draw*/
    // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // only draws the vertices
    // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // only draws the outline of a shape

    //! @brief Render loop
    while(!glfwWindowShouldClose(window))
    {
        onKeyDown(window, GLFW_KEY_ESCAPE, [&window]() {
            closeWindow(window);
        });

        // clear previous frame
        glClear(GL_COLOR_BUFFER_BIT);

        basic_shader.use();
        rectangle.draw();
        //
        tex_shader.use();
        glActiveTexture(GL_TEXTURE0); // texture unit
        heart_tex.use();
        // TODO: app crashes when drawing with texture shader when frag uses the color input (exit code -1073741819 (0xC0000005))
        tex_rectangle.draw();
        //
        //uniform_color_shader.use();
        //triangle.draw();
        //
        //gradient_shader.use();
        //gradient_triangle.draw();

        /*! @brief Render vertices
         *  @param mode  type of primitive (shape) to render
         *  @param first index of the vertex array where we want to take vertices from
         *  @param count how many vertices to render */
        // glDrawArrays(GL_TRIANGLES, 0, 3); // * USE FOR TRIANGLES
        /*! @brief Render from indices (not vertices)
         *  @param mode    type of primitive (shape) to render
         *  @param count   how many vertices to render
         *  @param type    data type of indices (e.g. Int, Float, etc.)
         *  @param indices offset of indices to use from the Element Array */
        // glDrawElements(GL_TRIANGLES, 6, Unsigned_Int, nullptr); // * USE FOR MORE COMPLEX SHAPES

        // transition from one frame to another with no flickers
        glfwSwapBuffers(window);
        // call events
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}