#ifndef OPENGL_PRIMITIVE_H
#define OPENGL_PRIMITIVE_H

#include <array>
#include "vec.h"
#include "util.h"


namespace primitive
{
    template<size_t v_size, size_t i_size>
    struct Shape2D
    {
    public:
        /*! @brief Define a Shape (2 dimensional).
         *         Vertex attributes must follow this order: position(3), color(4), tex_coord(2)
         *  @param vertices the points of the shape
         *  @param vertex_length how many objects (a single data type) long is a vertex
         *      (e.g. vertex has point 1, 1, 0 and color 1, 1, 1, 1, so a single vertex is 7 (3+4) long
         *  @param indices Specify the order to draw vertices. Stores *indices* to a vertex array.
         *  OpenGL draws triangles, the indices will be in order of a triangle (to draw a rectangle, draw 2 triangles)*/
        Shape2D(std::array<float, v_size> vertices, unsigned int vertex_length, std::array<unsigned int, i_size> indices) // NOLINT(cppcoreguidelines-pro-type-member-init)
        {
            if (i_size == 0)
            {
                const char* error_str = "Cannot use array of length 0 for indices. "
                                        "@param<l_length> has to be greater than 0.";
                std::cerr << error_str;
                throw std::invalid_argument{error_str};
            }


            // allocate VRAM and assign id (ptr)
            glGenVertexArrays(1, &this->vertex_array);
            glGenBuffers(1, &this->vertex_buffer);
            glGenBuffers(1, &this->element_buffer);

            // * the following must be done in sequence:
            glBindVertexArray(this->vertex_array);
            glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer); // (can simultaneously bind buffers of different types)
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->element_buffer);

            /*! @brief Transfer vertices data from RAM (CPU) to VRAM (GPU).
             *  Do this the least amount of times possible (or do it in bulk) because it is slow
             *  @param usage Options:
             *                  GL_STREAM_DRAW:  is written once,  is read few times
             *                  GL_STATIC_DRAW:  is written once,  is read a lot
             *                  GL_DYNAMIC_DRAW: is written a lot, is read a lot     */
            glBufferData(GL_ARRAY_BUFFER, (unsigned int) sizeof(float) * vertices.size(),
                         vertices.data(), GL_STATIC_DRAW);
            // We don't change the indices so safe to keep static
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int) sizeof(unsigned int) * indices.size(),
                         indices.data(),  GL_STATIC_DRAW);

            /*! @brief Create attribute object, attributes to be given to the vertex shader
             *  @param position   layout location (matches with the vertex shader)
             *  @param size       how many values the vertex attribute stores (vec3)
             *  @param type       data type (e.g. Int, Float, etc.)
             *  @param normalized use normalized values (from -1 to 1 or 0 to 1)
             *  @param stride     size (bytes) of each attribute (tightly packed) and tells space between each attribute
             *          (if vertices have color, the size would be 3 but stride would be 16 (4 * sizeof(float))
             *  @param offset where to start reading data from in the array. nullptr=beginning */
            // position attribute
            glVertexAttribPointer(0, 3, Float, False, int(vertex_length * sizeof(float)), nullptr);
            glEnableVertexAttribArray(0);
            if (vertex_length > 3) // vertices have color attribute (RGBA)
            {
                // use with shaders that take in the layout location = 1 attribute
                // color attribute // <offset> start reading color after 3 floats (after x, y, z of position attribute)
                glVertexAttribPointer(1, 4, Float, False, int(vertex_length * sizeof(float)),
                                                          (void*)(3 * sizeof(float))
                );  glEnableVertexAttribArray(1);
            }
            if (vertex_length > 7) // vertices have texture coordinate attribute
            {
                glVertexAttribPointer(2, 2,Float, False, int(vertex_length * sizeof(float)),
                                                         (void*)(7 * sizeof(float))
                );  glEnableVertexAttribArray(2);
            }
        }

        // TODO: create constructor where vertex position, color, and tex_coord are separate arrays

        ~Shape2D()
        {
            glDeleteVertexArrays(1, &this->vertex_array);
            glDeleteBuffers(1, &this->vertex_buffer);
            glDeleteBuffers(1, &this->element_buffer);
        }


        //! @brief Use the Vertex Array that holds a specified object/shape we want to render
        void bind_array() const { glBindVertexArray(this->vertex_array); }

        void draw() const
        {
            glBindVertexArray(this->vertex_array);

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
        }

    private:
        //! @brief An array of Vertex Buffer and Element Buffer pointers
        unsigned int vertex_array; // Calls BIND for Vertex and Element Buffers when it is bound
        //! @brief A pointer to some data in the GPU. Contains an array of vertices
        unsigned int vertex_buffer;
        //! @brief Stores indices that specify the order in which to draw vertices in the Vertex Buffer
        unsigned int element_buffer;
    };


    // For a triangle an Element Buffer is NOT necessary, only for more complex shapes
    struct Triangle : public Shape2D<3*3, 3>
    {
    public:
        /*! @brief Triangle object
         *  @param vertices a 1-dimensional array. Order of draw vertices doesn't matter if triangle is 1 color,
         *                  but is still defined for functionality */
        explicit Triangle(std::array<float, 3*3> vertices)
            : Shape2D(vertices, 3, inds) {  }

        /*! @brief Triangle object, indices are user defined
         *  @param vertices a 1-dimensional array. (in this case it follows the order of the given indices)
         *  @param indices the order in which the vertices are to be drawn */
        Triangle(std::array<float, 3*3> vertices, std::array<unsigned int, 3> indices)
        : Shape2D(vertices, 3, indices) {  }

    private:
        static constexpr std::array<unsigned int, 3> inds = { 0, 1, 2 };
    };


    struct Rectangle : public Shape2D<4*3, 6>
    {
    public:
        /*! @brief Rectangle object
         *  @param vertices a 1-dimensional array. vertices must be defined in the following order:
         *            top left,
                   bottom left,
                      top right,
                   bottom right */
        explicit Rectangle(std::array<float, 4*3> vertices, unsigned int vertex_length)
            : Shape2D(vertices, vertex_length, inds) {  }

        /*! @brief Rectangle object, indices are user defined
         *  @param vertices a 1-dimensional array. (in this case it follows the order of the given indices)
         *  @param indices the order in which the vertices are to be drawn*/
        Rectangle(std::array<float, 4*3> vertices, unsigned int vertex_length, std::array<unsigned int, 6> indices)
            : Shape2D(vertices, vertex_length, indices) {  }

        /*! @brief Rectangle with percentage attributes. Uses Cartesian Plane (origin(0, 0), y up)
         *  @param x     range: -1.0f to 1.0f  @param y      range: -1.0f to 1.0f
         *  @param width range: -1.0f to 1.0f  @param height range: -1.0f to 1.0f */
        Rectangle(float x, float y, float width, float height)
            : Shape2D(gen_vertices(x, y, width, height), 3, inds) {  }

        /*! @brief Rectangle with percentage attributes. Uses Cartesian Plane (origin(0, 0), y up)
         *  @param position   contains x and y positions. range: -1.0f to 1.0f
         *  @param dimensions contains width and height.  range: -1.0f to 1.0f */
        Rectangle(vec2<float> position, vec2<float> dimensions)
            : Shape2D(gen_vertices(position.x,      position.y,
                                   dimensions.x, dimensions.y),
                      3, inds) {  }

        /*! @brief Generate an array containing vertices for the rectangle. Uses Cartesian Plane (origin(0, 0), y up)
         *  @param x     range: -1.0f to 1.0f  @param y      range: -1.0f to 1.0f
         *  @param width range: -1.0f to 1.0f  @param height range: -1.0f to 1.0f */
        static std::array<float, 4*3> gen_vertices(float x, float y, float width, float height)
        {
            return std::array<float, 4 * 3> {
                x,         y         , 0.0f, //    top left
                x,         y - height, 0.0f, // bottom left
                x + width, y         , 0.0f, //    top right
                x + width, y - height, 0.0f  // bottom right
            };
        }

    private:
        static constexpr std::array<unsigned int, 6> inds = {
            // * first triangle
            0, //    top left   |\_
            1, // bottom left   |  \_
            3, // bottom right  |____\
            // * second triangle ______
            0, //    top left    \_   |
            2, //    top right     \_ |
            3  // bottom right       \|
        };
    };
}


#endif //OPENGL_PRIMITIVE_H
