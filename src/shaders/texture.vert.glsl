#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 vert_color;
layout (location = 2) in vec2 vert_tex_coord;

out vec4 color;
out vec2 tex_coord;

void main()
{
    gl_Position = vec4(position, 1.0);
    color = vert_color;
    tex_coord = vert_tex_coord;
}