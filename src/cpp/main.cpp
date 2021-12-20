#include <iostream>
#include <string>
#include <array>
#include "shader-program.h"
#include "event-handlers.h"
#include "vec.h"
// glad must always be included before glfw
#include "glad/glad.h"
#include "GLFW/glfw3.h"
using std::string;


#define True         GL_TRUE
#define False        GL_FALSE
#define Any          GLFW_DONT_CARE
#define Int          GL_INT
#define Unsigned_Int GL_UNSIGNED_INT
#define Float        GL_FLOAT

#define Win_Width      800
#define Win_Min_Width  167
#define Win_Height     600
#define Win_Min_Height 100

struct Shape2D
{
    float* vertices;
    //! @brief use the Vertex Array that holds a specified object/shape we want to render
    void bind_array() const { glBindVertexArray(this->vertex_array); }
    void draw() const
    {
        // use the Vertex Array that holds a specified object/shape we want to render
        glBindVertexArray(vertex_array);
        /*! @brief Render from indices (not vertices)
         *  @param mode    type of primitive (shape) to render
         *  @param count   how many vertices to render
         *  @param type    data type of indices (e.g. Int, Float, etc.)
         *  @param indices offset of indices to use from the Element Array */
        glDrawElements(GL_TRIANGLES, 6, Unsigned_Int, nullptr); // * USE FOR MORE COMPLEX SHAPES
    }

    #pragma clang diagnostic push
    #pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
    explicit Shape2D(float* _vertices, unsigned int* const _indices=nullptr)
        : vertices(_vertices)
    {
        if (!_indices)
        {
            // defaults to triangle
            unsigned int a[] = { 1, 2, 3 };
            indices = a;
        }
        else // if indices are passed in just use them
            indices = _indices;

        // allocate VRAM
        glGenVertexArrays( 1, &this->vertex_array   );
        glGenBuffers(      1, &this->vertex_buffer  );
        glGenBuffers(      1, &this->element_buffer );

        // * the following must be done in sequence:
        glBindVertexArray(this->vertex_array);
        glBindBuffer(GL_ARRAY_BUFFER,         this->vertex_buffer ); // (can simultaneously bind buffers of different types)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->element_buffer);

        /*! @brief Transfer vertices data from RAM (CPU) to VRAM (GPU).
         *  Do this the least amount of times possible (or do it in bulk) because it is slow
         *  @param usage Options:
         *                  GL_STREAM_DRAW:  is written once,  is read few times
         *                  GL_STATIC_DRAW:  is written a lot, is read few times
         *                  GL_DYNAMIC_DRAW: is written a lot, is read a lot     */
        glBufferData(GL_ARRAY_BUFFER,         sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices),  this->indices,  GL_STATIC_DRAW);
        /*! @brief Create attribute object, attributes to be given to the vertex shader
         *  @param position   layout location (matches with the vertex shader)
         *  @param size       how many values the vertex attribute stores (vec3)
         *  @param type       data type (e.g. Int, Float, etc.)
         *  @param normalized use normalized values (from -1 to 1 or 0 to 1)
         *  @param stride     size (bytes) of each attribute (tightly packed) and tells space between each attribute
         *          (if vertices have color, the size would be 3 but stride would be 16 (4 * sizeof(float))
         *  @param offset where to start reading data from in the array.  */
        glVertexAttribPointer(0, 3, Float, False, 3 * sizeof(float), nullptr);
        // use attribute object with current vertex array
        glEnableVertexAttribArray(0);
    }

    // TODO:
    template <size_t v_size, size_t i_size>
    explicit Shape2D(std::array<float, v_size> _vertices, std::array<unsigned int, i_size> _indices=nullptr)
        :Shape2D((float*)_vertices, (unsigned int*)_indices) {  }

    template <size_t v_size>
    explicit Shape2D(std::array<float, v_size> _vertices, unsigned int* _indices=nullptr) // NOLINT(readability-non-const-parameter)
        :Shape2D((float*)_vertices, _indices) {  }

    // TODO:
    // template <size_t i_size>
    // explicit Shape2D(float* _vertices, std::array<unsigned int, i_size> _indices=nullptr) // NOLINT(readability-non-const-parameter)
    //     :Shape2D(_vertices, (unsigned int*)_indices) {  }
    #pragma clang diagnostic pop

private:
    /*! @brief Specify the order to draw vertices. Stores *indices* to a vertex. Used by Element Buffer
     *  OpenGL uses triangles, the indices will be in order of a triangle (to draw a rectangle, draw 2 triangles) */
    unsigned int* indices;
    //! @brief An array of Vertex Buffer and Element Buffer pointers
    unsigned int vertex_array; // Calls BIND for Vertex and Element Buffers when it is bound
    //! @brief A pointer to some data in the GPU. Contains an array of vertices
    unsigned int vertex_buffer;
    //! @brief Specifies the order in which to use vertices in the Vertex Buffer
    unsigned int element_buffer;
};

struct Triangle : Shape2D
{

};

struct Rectangle : Shape2D
{
    Rectangle(const vec4<float>& v)
        : Shape2D(std::array<float, 4>{v.x, v.y, v.z, v.w}, std::array<unsigned int, 6>{ 0, 1, 3, 1, 2, 3 })
    {

    }
};


int main() {
    std::cout << "init\n";

    // initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // version x.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    // glfwWindowHint(GLFW_FLOATING, True); // window is "always on top". Let user decide in context-menu
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, True); // transparent window


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
    ShaderProgram basic_SP{true };



    // --- DRAWING TRIANGLE ---
    /*! @brief defined points of a rectangle to be drawn. Two triangles that are related
     *  For a triangle an Element Buffer is NOT necessary, only for more complex shapes */
    float triangle_vertices[] = {
        0.5f,  0.5f,  0.0f, // no defined color
        0.5f,  -0.5f, 0.0f, // no defined color
        -0.5f, 0.5f,  0.0f, // no defined color
    };
    float rectangle_vertices[] = {
        0.5f,  0.5f,  0.0f,  //    top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f, 0.0f   //    top left
    };
    /*! @brief specify the order that we want to draw vertices. Store *indices* to a vertex. Used by Element Buffer
     *  OpenGL uses triangles, the indices will be in order of a triangle (to draw a rectangle, draw 2 triangles) */
    unsigned int rectangle_indices[] = {
        // * first triangle
        0, //    top right
        1, // bottom right
        3, //    top left
        // * second triangle
        1, // bottom right
        2, // bottom left
        3  //    top left
    };



    //! @brief Fill the color buffer with this color. Acts as a background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.75f);
    //! @brief Shader program to be used (with defined pipeline)
    glUseProgram(basic_SP.GL_program);

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
        // use the Vertex Array that holds a specified object/shape we want to render
        glBindVertexArray(vertex_array);

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
        glDrawElements(GL_TRIANGLES, 6, Unsigned_Int, nullptr); // * USE FOR MORE COMPLEX SHAPES

        // transition from one frame to another with no flickers
        glfwSwapBuffers(window);
        // call events
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}