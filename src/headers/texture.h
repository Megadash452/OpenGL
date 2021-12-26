#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H
#include "stb_image.h"
#include "util.h"

struct Texture {
public:
    unsigned int gl_texture{};
    vec4<float> border_col;

    explicit Texture(const char* filename);

    [[nodiscard]] int width() const { return _width; }
    [[nodiscard]] int height() const { return _height; }
    //! @brief number of color channels
    [[nodiscard]] int num_col_channels() const { return _num_col_channels; }

    /*! @brief Set how the image wraps. Means when the texture coordinates go beyond the texture (beyond -1 to 1 range)
     *         Wrap in (s, t, r) -> (x, y, z) directions (z not used for 2D texture).
     *  @param modes a vec containing the wrap modes for directions s, t, r (respectively). Mode is one of these enums:
     *         // 0:                  does not set that direction, leaves it as is
     *         // GL_REPEAT:          Repeats the texture, like 'image-repeat: repeat' in css
     *         // GL_MIRRORED_REPEAT: Every other iteration of the repeat is mirrored (works in both x- and y-axis)
     *         // GL_CLAMP_TO_EDGE:   Repeats the last pixel at the edge of the texture
     *         // GL_CLAMP_TO_BORDER: Use a border color. Have to set this->border_col first (default is transparent) */
    void set_wrap_mode(vec3<int> modes) const;

    /*! @brief Set how the image scales up and down (minifying and magnifying).
     *  @param modes a vec containing the wrap modes for MIN and MAG modes. Mode is one of these enums:
     *         // 0:                  does not set that direction, leaves it as is
     *         // GL_Nearest: Texture appears pixelated
     *         // GL_Linear:  (aka bilinear) Texture appears blurry . Similar to interpolation
     *         //     match with --
     *         // _MIPMAP_NEAREST:
     *         // _MIPMAP_Linear:
     *  @brief // Using mipmap with magnification has no effect because mipmap only creates images 2x smaller
               // Using mipmap here will give GL_INVALID_ENUM error code */
    void set_filter_mode(vec2<int> modes) const;

    void use() const;
    //! @brief alias to this->use()
    void bind() const;

private:
    int _width{};
    int _height{};
    //! @brief number of color channels
    int _num_col_channels{};
};


#endif //OPENGL_TEXTURE_H
