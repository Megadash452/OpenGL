#ifndef OPENGL_VEC_H
#define OPENGL_VEC_H
#include <stdexcept>
#include <iostream>

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

    explicit vec1(Type _x)             : x(_x)  {  }
    explicit vec1(const vec2<Type>& v) : x(v.x) {  }
    explicit vec1(const vec3<Type>& v) : x(v.x) {  }
    explicit vec1(const vec4<Type>& v) : x(v.x) {  }

    //! @brief For printing a vec1 object
    friend std::ostream& operator<<(std::ostream& os, const vec1& v);

    //! @brief The Pythagoras Theorem. Only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec1& normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const;

    // vector addition
    template<typename Type2> vec4<Type>& operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type>& operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type>& operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    // vector subtraction
    template<typename Type2> vec4<Type>& operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type>& operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type>& operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
};


template<typename Type>
struct vec2
{
    Type x, y;

             vec2(const vec1<Type>& v, Type _y) : x(v.x), y(_y)  {  }
             vec2(Type _x, Type _y)             : x(_x),  y(_y)  {  }
    explicit vec2(const vec3<Type>& v)          : x(v.x), y(v.y) {  }
    explicit vec2(const vec4<Type>& v)          : x(v.x), y(v.y) {  }

    //! @brief For printing a vec1 object
    friend std::ostream& operator<<(std::ostream& os, const vec2& v);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec2& normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const;

    // vector addition
    template<typename Type2> vec4<Type>& operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    // vector subtraction
    template<typename Type2> vec4<Type>& operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type>& operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
};


template <typename Type>
struct vec3
{
    Type x, y, z;

             vec3(const vec1<Type>& v, Type _y, Type _z) : x(v.x), y(_y),  z(_z)  {  }
             vec3(const vec2<Type>& v, Type _z)          : x(v.x), y(v.y), z(_z)  {  }
             vec3(Type _x, Type _y, Type _z)             : x(_x),  y(_y),  z(_z)  {  }
    explicit vec3(const vec4<Type>& v)                   : x(v.x), y(v.y), z(v.z) {  }

    //! @brief For printing a vec1 object
    friend std::ostream& operator<<(std::ostream& os, const vec3& v);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec3& normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const;

    // vector addition
    template<typename Type2> vec4<Type>& operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    // vector subtraction
    template<typename Type2> vec4<Type>& operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type>& operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                      std::is_arithmetic_v<Type2>;
};


template <typename Type>
struct vec4
{
    Type x, y, z, w;

    vec4(const vec1<Type>& v, Type _y, Type _z, Type _w) : x(v.x), y(_y),  z(_z),  w(_w) {  }
    vec4(const vec2<Type>& v, Type _z, Type _w)          : x(v.x), y(v.y), z(_z),  w(_w) {  }
    vec4(const vec3<Type>& v, Type _w)                   : x(v.x), y(v.y), z(v.z), w(_w) {  }
    vec4(Type _x, Type _y, Type _z, Type _w)             : x(_x),  y(_y),  z(_z),  w(_w) {  }

    //! @brief For printing a vec1 object
    friend std::ostream& operator<<(std::ostream& os, const vec4& v);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    vec4& normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned int i) const;

    // vector addition
    template<typename Type2> vec4& operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    // vector subtraction
    template<typename Type2> vec4& operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4& operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                std::is_arithmetic_v<Type2>;

    // TODO: cross and dot multiply
};


// TODO: maike struct, and make constructor for vecs here and there
template<typename Type>
using rgb = vec3<Type>;

template<typename Type>
using rgba = vec4<Type>;


#endif //OPENGL_VEC_H
