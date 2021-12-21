#version 330
in vec4 color;
in vec2 tex_cord;
uniform sampler2D texture_data;

out vec4 frag_color;

void main()
{
    // use texture() to sample the image data at a pixel (get the color from the pixel in the image and put it here)
//    frag_color = texture(texture_data, tex_cord);
    // TODO: app crashes without message when using vec4 color
     frag_color = color;
}