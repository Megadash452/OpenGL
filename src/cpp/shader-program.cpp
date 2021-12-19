#include "shader-program.h"

// struct ShaderProgram
// {
//     unsigned int GL_program;
//
//     /*! @brief takes care of loading shaders
//      *  @param use_now if true will bind the shader program to be used
//      * */
//     explicit ShaderProgram(bool use_now, const char* vertex_shader_src, const char* fragment_shader_src)
//     {
//
//     }
//
//     void use() const  { glUseProgram(this->GL_program); }
//     //! @brief alias to shader-program::use()
//     void bind() const { glUseProgram(this->GL_program); }
// };
ShaderProgram::ShaderProgram(bool use_now, const char *vertex_shader_src, const char *fragment_shader_src)
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
    // check for errors
    glGetProgramiv(this->GL_program, GL_LINK_STATUS, &no_errors);
    if (!no_errors)
    {
        char error_info[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, error_info);
        std::cout << "Link Error: Failed to bind shader program <FRAGMENT SHADER>\n" << error_info << std::endl;
    }

    if (use_now)
        this->bind();

    // these are already compiled and used by this->program, so they have no use now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}


void ShaderProgram::use()  const { glUseProgram(this->GL_program); }
void ShaderProgram::bind() const { glUseProgram(this->GL_program); }