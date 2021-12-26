#ifndef OPENGL_VEC_H
#define OPENGL_VEC_H
#include <stdexcept>
#include <iostream>

#define SQR(x) x*x

// template<typename Type>
// concept number = std::is_arithmetic_v<Type>;

template<typename Type> struct vec1;
template<typename Type> struct vec2;
template<typename Type> struct vec3;
template<typename Type> struct vec4;

// TODO: (func decl) See src/vec.tpp Line 613
template<typename Type> std::ostream& operator<<(std::ostream&, const vec1<Type       >&);
                        // std::ostream& operator<<(std::ostream&, const vec1<char       >&);
                        // std::ostream& operator<<(std::ostream&, const vec1<std::string>&);
template<typename Type> std::ostream& operator<<(std::ostream&, const vec2<Type       >&);
                        // std::ostream& operator<<(std::ostream&, const vec2<char       >&);
                        // std::ostream& operator<<(std::ostream&, const vec2<std::string>&);
template<typename Type> std::ostream& operator<<(std::ostream&, const vec3<Type       >&);
                        // std::ostream& operator<<(std::ostream&, const vec3<char       >&);
                        // std::ostream& operator<<(std::ostream&, const vec3<std::string>&);
template<typename Type> std::ostream& operator<<(std::ostream&, const vec4<Type       >&);
                        // std::ostream& operator<<(std::ostream&, const vec4<char       >&);
                        // std::ostream& operator<<(std::ostream&, const vec4<std::string>&);


template <typename Type>
struct vec1
{
    Type x;
    // TODO: (vec1) angle class [requires arithmetic<Type>] (for vec1 angle is always 0)

    explicit vec1(Type _x)             : x(_x)  {  }
    explicit vec1(const vec2<Type>& v) : x(v.x) {  }
    explicit vec1(const vec3<Type>& v) : x(v.x) {  }
    explicit vec1(const vec4<Type>& v) : x(v.x) {  }

    //! @brief For printing a vec1 object
    friend std::ostream& operator<<<Type       >(std::ostream&, const vec1<Type       >&);
    // TODO: (vec1) See src/vec.tpp Line 613
    // friend std::ostream& operator<<<char       >(std::ostream&, const vec1<char       >&);
    // friend std::ostream& operator<<<std::string>(std::ostream&, const vec1<std::string>&);

    //! @brief The Pythagoras Theorem. Only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    [[nodiscard]] vec1<double> normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned char i);
    Type  operator[](unsigned char i) const;

    // -- vector addition
    template<typename Type2> vec4<Type> operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type> operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar addition
    template<typename Type2> vec1<Type> operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector subtraction
    template<typename Type2> vec4<Type> operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec1<Type> operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar subtraction
    template<typename Type2> vec1<Type> operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector division
    //! @brief vector-scalar division
    template<typename Type2> vec1<Type> operator/(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector multiplication
    template<typename Type2> double dot_mult(const vec1<Type2>&)      const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar multiplication
    template<typename Type2> vec1<Type> operator*(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
};


template<typename Type>
struct vec2
{
    Type x, y;
    // TODO: (vec2) angle class [requires arithmetic<Type>]

             vec2(const vec1<Type>& v, Type _y) : x(v.x), y(_y)  {  }
             vec2(Type _x, Type _y)             : x(_x),  y(_y)  {  }
    explicit vec2(const vec3<Type>& v)          : x(v.x), y(v.y) {  }
    explicit vec2(const vec4<Type>& v)          : x(v.x), y(v.y) {  }

    //! @brief For printing a vec2 object
    friend std::ostream& operator<<<Type       >(std::ostream&, const vec2<Type       >&);
    // TODO: (vec2) See src/vec.tpp Line 632
    // friend std::ostream& operator<<<char       >(std::ostream&, const vec2<char       >&);
    // friend std::ostream& operator<<<std::string>(std::ostream&, const vec2<std::string>&);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    [[nodiscard]] vec2<double> normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned char i);
    Type  operator[](unsigned char i) const;

    // -- vector addition
    template<typename Type2> vec4<Type> operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar addition
    template<typename Type2> vec2<Type> operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector subtraction
    template<typename Type2> vec4<Type> operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec2<Type> operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar subtraction
    template<typename Type2> vec2<Type> operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector division
    //! @brief vector-scalar division
    template<typename Type2> vec2<Type> operator/(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector multiplication
    template<typename Type2> double dot_mult(const vec2<Type2>&)      const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar multiplication
    template<typename Type2> vec2<Type> operator*(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
};


template <typename Type>
struct vec3
{
    Type x, y, z;
    // TODO: (vec3) angle class [requires arithmetic<Type>]

             vec3(const vec1<Type>& v, Type _y, Type _z) : x(v.x), y(_y),  z(_z)  {  }
             vec3(const vec2<Type>& v, Type _z)          : x(v.x), y(v.y), z(_z)  {  }
             vec3(Type _x, Type _y, Type _z)             : x(_x),  y(_y),  z(_z)  {  }
    explicit vec3(const vec4<Type>& v)                   : x(v.x), y(v.y), z(v.z) {  }

    //! @brief For printing a vec3 object
    friend std::ostream& operator<<<Type       >(std::ostream&, const vec3<Type       >&);
    // TODO: (vec3) See src/vec.tpp Line 651
    // friend std::ostream& operator<<<char       >(std::ostream&, const vec3<char       >&);
    // friend std::ostream& operator<<<std::string>(std::ostream&, const vec3<std::string>&);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    [[nodiscard]] vec3<double> normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned char i);
    Type  operator[](unsigned char i) const;

    // -- vector addition
    template<typename Type2> vec4<Type> operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar addition
    template<typename Type2> vec3<Type> operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector subtraction
    template<typename Type2> vec4<Type> operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec3<Type> operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar subtraction
    template<typename Type2> vec3<Type> operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector division
    //! @brief vector-scalar division
    template<typename Type2> vec3<Type> operator/(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                            std::is_arithmetic_v<Type2>;
    // -- vector multiplication
    template<typename Type2> double dot_mult(const vec3<Type2>&)      const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief Produces a vec that is orthogonal to both vecs. Only works with vec3
    template<typename Type2> vec3<double> cross_mult(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                        std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar multiplication
    template<typename Type2> vec3<Type> operator*(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
};


template <typename Type>
struct vec4
{
    Type x, y, z, w;
    // TODO: (vec4) angle class [requires arithmetic<Type>]

    vec4(const vec1<Type>& v, Type _y, Type _z, Type _w) : x(v.x), y(_y),  z(_z),  w(_w) {  }
    vec4(const vec2<Type>& v, Type _z, Type _w)          : x(v.x), y(v.y), z(_z),  w(_w) {  }
    vec4(const vec3<Type>& v, Type _w)                   : x(v.x), y(v.y), z(v.z), w(_w) {  }
    vec4(Type _x, Type _y, Type _z, Type _w)             : x(_x),  y(_y),  z(_z),  w(_w) {  }

    //! @brief For printing a vec4 object
    friend std::ostream& operator<<<Type       >(std::ostream&, const vec4<Type       >&);
    // TODO: (vec4) See src/vec.tpp Line 670
    // friend std::ostream& operator<<<char       >(std::ostream&, const vec4<char       >&);
    // friend std::ostream& operator<<<std::string>(std::ostream&, const vec4<std::string>&);

    // function only works when the Type stored is a number (char, int, float, etc..)
    [[nodiscard]] double length() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the Unit Vector (length=1). Components Type must be a number (char, int, float, etc..)
    [[nodiscard]] vec4<double> normalized() const requires std::is_arithmetic_v<Type>;

    //! @brief Get the ith component of this vector (like an array)
    Type& operator[](unsigned char i);
    Type  operator[](unsigned char i) const;

    // -- vector addition
    template<typename Type2> vec4<Type> operator+(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator+(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator+(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator+(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar addition
    template<typename Type2> vec4<Type> operator+(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector subtraction
    template<typename Type2> vec4<Type> operator-(const vec4<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator-(const vec3<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator-(const vec2<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    template<typename Type2> vec4<Type> operator-(const vec1<Type2>&) const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar subtraction
    template<typename Type2> vec4<Type> operator-(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //--  vector division
    //! @brief vector-scalar division
    template<typename Type2> vec4<Type> operator/(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    // -- vector multiplication
    template<typename Type2> double dot_mult(const vec4<Type2>&)      const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
    //! @brief vector-scalar multiplication
    template<typename Type2> vec4<Type> operator*(const Type2&)       const requires std::is_arithmetic_v<Type>   &&
                                                                                     std::is_arithmetic_v<Type2>;
};

#include "../cpp/vec.tpp"


// TODO: maike struct, and make constructor for vecs here and there
template<typename Type>
using rgb = vec3<Type>;

template<typename Type>
using rgba = vec4<Type>;


#endif //OPENGL_VEC_H
