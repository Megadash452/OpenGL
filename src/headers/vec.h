#ifndef OPENGL_VEC_H
#define OPENGL_VEC_H
#include <stdexcept>
#include <string>
using std::string;

#define SQR(x) x*x

// template<typename Type>
// concept number = std::is_arithmetic_v<Type>;

template <typename Type> struct vec1;
template <typename Type> struct vec2;
template <typename Type> struct vec3;
template <typename Type> struct vec4;


template <typename Type>
struct vec1
{
    Type x;

    explicit vec1(Type _x)              : x(_x)  {  }
    explicit vec1(const vec2<Type>& v)  : x(v.x) {  }
    explicit vec1(const vec3<Type>& v)  : x(v.x) {  }
    explicit vec1(const vec4<Type>& v)  : x(v.x) {  }

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const
    requires std::is_arithmetic_v<Type>
    {
        return this->x;
    }

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec1 normalized() const
    requires std::is_arithmetic_v<Type>
    {
        return { 1 };
    }

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const
    {
        if (i < 1)
            return *(&this->x + i);
        throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec1 only has 1 component"};
    }
};

template<typename Type>
struct vec2
{
    Type x, y;

             vec2(const vec1<Type>& v, Type _y) : x(v.x), y(_y)  {  }
             vec2(Type _x, Type _y)             : x(_x),  y(_y)  {  }
    explicit vec2(const vec3<Type>& v)          : x(v.x), y(v.y) {  }
    explicit vec2(const vec4<Type>& v)          : x(v.x), y(v.y) {  }

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const
    requires std::is_arithmetic_v<Type>
    {
        return sqrt(SQR(this->x) + SQR(this->y));
    }

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec2 normalized() const
    requires std::is_arithmetic_v<Type>
    {
        double len = this->length();
        return {
            this->x / len,
            this->y / len
        };
    }

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const
    {
        if (i < 2)
            return *(&this->x + i);
        throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec2 only has 2 components"};
    }
};

template <typename Type>
struct vec3
{
    Type x, y, z;

             vec3(const vec1<Type>& v, Type _y, Type _z) : x(v.x), y(_y),  z(_z)  {  }
             vec3(const vec2<Type>& v, Type _z)          : x(v.x), y(v.y), z(_z)  {  }
             vec3(Type _x, Type _y, Type _z)             : x(_x),  y(_y),  z(_z)  {  }
    explicit vec3(const vec4<Type>& v)                   : x(v.x), y(v.y), z(v.z) {  }

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const
    requires std::is_arithmetic_v<Type>
    {
        return sqrt(SQR(this->x) + SQR(this->y) + SQR(this->z));
    }

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec3 normalized() const
    requires std::is_arithmetic_v<Type>
    {
        double len = this->length();
        return {
            this->x / len,
            this->y / len,
            this->z / len
        };
    }

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const
    {
        if (i < 3)
            return *(&this->x + i);
        throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec3 only has 3 components"};
    }
};

template <typename Type>
struct vec4
{
    Type x, y, z, w;

    vec4(const vec1<Type>& v, Type _y, Type _z, Type _w) : x(v.x), y(_y),  z(_z),  w(_w) {  }
    vec4(const vec2<Type>& v, Type _z, Type _w)          : x(v.x), y(v.y), z(_z),  w(_w) {  }
    vec4(const vec3<Type>& v, Type _w)                   : x(v.x), y(v.y), z(v.z), w(_w) {  }
    vec4(Type _x, Type _y, Type _z, Type _w)             : x(_x),  y(_y),  z(_z),  w(_w) {  }

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const
    requires std::is_arithmetic_v<Type>
    {
        return sqrt(SQR(this->x) + SQR(this->y) + SQR(this->z) + SQR(this->w));
    }

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec4 normalized() const
    requires std::is_arithmetic_v<Type>
    {
        double len = this->length();
        return {
            this->x / len,
            this->y / len,
            this->z / len,
            this->w / len
        };
    }

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const
    {
        if (i < 3)
            return *(&this->x + i);
        throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec3 only has 3 components"};
    }

    // vector addition
    template<typename Type2> vec4& operator+(const vec4<Type2>& other) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z,
            this->w + other.w,
        };
    }
    template<typename Type2> vec4& operator+(const vec3<Type2>& other) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z,
            this->w,
        };
    }
    template<typename Type2> vec4& operator+(const vec2<Type2>& other) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x + other.x,
            this->y + other.y,
            this->z,
            this->w,
        };
    }
    template<typename Type2> vec4& operator+(const vec1<Type2>& other) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x + other.x,
            this->y,
            this->z,
            this->w,
        };
    }
    template<typename Type2> vec4& operator+(const Type2& val) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x + val,
            this->y + val,
            this->z + val,
            this->w + val,
        };
    }

    // vector subtraction
    template<typename Type2> vec4& operator-(const vec4<Type2>& other) const
    requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
    {
        return {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z,
            this->w - other.w,
        };
    }

    // TODO: cross and dot multiply
};

// TODO: maike struct, and make constructor for vecs here and there
template<typename Type>
using rgb = vec3<Type>;

template<typename Type>
using rgba = vec4<Type>;


#endif //OPENGL_VEC_H
