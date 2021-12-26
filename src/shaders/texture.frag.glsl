#version 330 core
in vec4 color;
in vec2 tex_coord;
uniform sampler2D texture_data;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture_data, tex_coord) * color;
}