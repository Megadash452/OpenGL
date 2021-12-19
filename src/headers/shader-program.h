#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H


struct ShaderProgram {
    unsigned int GL_program;

    explicit ShaderProgram(
        bool use_now,
        const char* vertex_shader_src   = nullptr,
        const char* fragment_shader_src = nullptr
    );

    void use() const;
    //! @brief alias to shader-program::use()
    void bind() const;
};


#endif //OPENGL_SHADERPROGRAM_H
