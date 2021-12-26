#include "texture.h"

Texture::Texture(const char *filename)
    : border_col(0, 0, 0, 1)
{
    // generate texture id (ptr)
    glGenTextures(1, &this->gl_texture);
    glBindTexture(GL_TEXTURE_2D, this->gl_texture);

    /// --- insert any filtering and wrapping settings. (see this->set_wrap_mode() and this->set_filter_mode())
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // use bilinear filtering with nearest mipmap level (?) when making image smaller
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // use nearest neighbor filtering (without mipmap) when making image larger
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Using mipmap with magnification has no effect
    // Using mipmap here will give GL_INVALID_ENUM error code          // because mipmap only creates images 2x smaller

    // load image data
    unsigned char* data = stbi_load(filename, &_width, &_height, &_num_col_channels, 0);

    if (data)
    {
        // check if image uses RGB or RGBA
        unsigned int img_read_mode = GL_RGB;
        if (_num_col_channels == 3)
            ; // already set to GL_RGB
        else if (_num_col_channels == 4)
            img_read_mode = GL_RGBA;

        /*! @brief Allocate and create image
         *  @param _2nd mipmap_level:    how many mipmaps to generate. no need for mipmap when everything is only 2D
         *  @param _3rd channels:        what channels to load the image onto the GPU with
         *  @param _6th legacy:          should always stay 0
         *  @param _7th source_channels: which channels was the original image loaded with (stb_image)
         *  @param _8th type:            the type of data the image is using (stb_image) */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, img_read_mode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        std::cerr << "Error loading texture at path \"" << filename << "\"" << std::endl;

    // delete image data from the cpu
    stbi_image_free(data);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-else"
void Texture::set_wrap_mode(vec3<int> modes) const
{
    this->bind();
    float b[] = {
        this->border_col.x,
        this->border_col.y,
        this->border_col.z,
    };

    if (modes.x != 0)
        if (modes.x == GL_CLAMP_TO_BORDER) // border
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, b);
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modes.x);
    if (modes.y != 0)
        if (modes.z == GL_CLAMP_TO_BORDER) // border
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, b);
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modes.y);
    if (modes.z != 0)
        if (modes.z == GL_CLAMP_TO_BORDER) // border
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, b);
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, modes.z);
}
#pragma clang diagnostic pop

void Texture::set_filter_mode(vec2<int> modes) const
{
    this->bind();

    if (modes.x != 0)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, modes.x);
    if (modes.y != 0)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, modes.y);
}

void Texture::use() const { glBindTexture(GL_TEXTURE_2D, this->gl_texture); }
void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, this->gl_texture); }
