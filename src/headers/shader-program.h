#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "util.h"
// glad must always be included before glfw
#include "glad/glad.h"
#include "GLFW/glfw3.h"


//! @brief Shader Programs contain compiled shaders, uniforms, and define how to draw something
struct ShaderProgram {
    //! @brief ID to the Shader Program on the GPU
    unsigned int GL_program;

    /*! @brief Create shader program with Vertex and Fragment Shaders.
     *  @param use_now bind Shader Program as soon as it is created
     *  @param vert_shader_path file path GLSL source code for vertex shader. If not given, will use default shader
     *  @param frag_shader_path file path GLSL source code for fragment shader. If not given, will use default shader */
    explicit ShaderProgram(const char* vert_shader_path=nullptr, const char* frag_shader_path=nullptr);

    void use() const;
    //! @brief alias to shader-program::use()
    void bind() const;

    void get_uniform(const char* uniform) const;

    void set_uniform(const char* uniform, vec4<float> val) const;
    void set_uniform(const char* uniform, float val) const;
    void set_uniform(const char* uniform, int val) const;
    void set_uniform(const char* uniform, unsigned int val) const;
};


#endif //OPENGL_SHADERPROGRAM_H
