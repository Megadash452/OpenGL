#include "shader-program.h"
using std::string;


ShaderProgram::ShaderProgram(const char* vert_shader_path, const char* frag_shader_path)
{
    int no_errors;

    /// --- VERTEX SHADER ---
    string vert_shader_src;
    // if no vertex shader was provided, use default
    if (vert_shader_path == nullptr)
        // very basic shader that doesn't do much
        vert_shader_src = "#version 330 core\n"
                          "layout (location = 0) in vec3 aPos;"
                          "void main() {"
                          "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
                          "}";
    else // copy file content to string stream
       vert_shader_src = read_file(vert_shader_path);

    // compile vertex shader
    const char* vs = vert_shader_src.c_str(); // needs to be l-value
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vs, nullptr);
    glCompileShader(vertex_shader);
    // check for errors when compiling shader
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &no_errors);
    if (!no_errors)
    {
        char error_info[512];
        glGetShaderInfoLog(vertex_shader, 512, nullptr, error_info);
        std::cerr << "Compilation Error: Failed to compile shader <VERTEX SHADER>:\n" << error_info << std::endl;
    }



    /// --- FRAGMENT SHADER ---
    string frag_shader_src;
    // if no fragment shader was provided, use default
    if (frag_shader_path == nullptr)
        frag_shader_src = "#version 330 core\n"
                          "out vec4 fragment_color;"
                          "void main() {"
                          "    fragment_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                          "}";
    else // copy file content to string stream
        frag_shader_src = read_file(frag_shader_path);

    // compile fragment shader
    const char* fs = frag_shader_src.c_str();
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs, nullptr);
    glCompileShader(fragment_shader);
    // check for errors when compiling shader
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &no_errors);
    if (!no_errors)
    {
        char error_info[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, error_info);
        std::cerr << "Compilation Error: Failed to compile shader <FRAGMENT SHADER>:\n" << error_info << std::endl;
    }



    // --- SHADER PROGRAM ---
    this->GL_program = glCreateProgram();
    glAttachShader(this->GL_program, vertex_shader);
    glAttachShader(this->GL_program, fragment_shader);
    glLinkProgram(this->GL_program);
    // check for errors when attaching shaders
    glGetProgramiv(this->GL_program, GL_LINK_STATUS, &no_errors);
    if (!no_errors)
    {
        char error_info[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, error_info);
        std::cerr << "Link Error: Failed to bind shader program <FRAGMENT SHADER>\n" << error_info << std::endl;
    }

    // these are already compiled and used by this->program, so they have no use now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderProgram::use()  const { glUseProgram(this->GL_program); }
void ShaderProgram::bind() const { glUseProgram(this->GL_program); }


// void ShaderProgram::get_uniform(const char *uniform)
// {
//
// }


void ShaderProgram::set_uniform(const char *uniform, vec4<float> val) const
{
    // have to use Shader Program before setting the uniform value
    this->use();
    glUniform4f(glGetUniformLocation(this->GL_program, uniform), val.x, val.y, val.z, val.w);
}

void ShaderProgram::set_uniform(const char *uniform, int val) const
{
    // have to use Shader Program before setting the uniform value
    this->use();
    glUniform1i(glGetUniformLocation(this->GL_program, uniform), val);
}
