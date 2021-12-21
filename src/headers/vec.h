#ifndef OPENGL_VEC_H
#define OPENGL_VEC_H

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

    // TODO: operator[]
};

template <typename Type>
struct vec2
{
    Type x, y;

             vec2(const vec1<Type>& v, Type _y) : x(v.x), y(_y)  {  }
             vec2(Type _x, Type _y)             : x(_x),  y(_y)  {  }
    explicit vec2(const vec3<Type>& v)          : x(v.x), y(v.y) {  }
    explicit vec2(const vec4<Type>& v)          : x(v.x), y(v.y) {  }
};

template <typename Type>
struct vec3
{
    union {
        struct{ Type x, y, z; };
    };

             vec3(const vec1<Type>& v, Type _y, Type _z) : x(v.x), y(_y),  z(_z)  {  }
             vec3(const vec2<Type>& v, Type _z)          : x(v.x), y(v.y), z(_z)  {  }
             vec3(Type _x, Type _y, Type _z)             : x(_x),  y(_y),  z(_z)  {  }
    explicit vec3(const vec4<Type>& v)                   : x(v.x), y(v.y), z(v.z) {  }
};

template <typename Type>
struct vec4
{
    Type x, y, z, w;

    vec4(const vec1<Type>& v, Type _y, Type _z, Type _w) : x(v.x), y(_y),  z(_z),  w(_w) {  }
    vec4(const vec2<Type>& v, Type _z, Type _w)          : x(v.x), y(v.y), z(_z),  w(_w) {  }
    vec4(const vec3<Type>& v, Type _w)                   : x(v.x), y(v.y), z(v.z), w(_w) {  }
    vec4(Type _x, Type _y, Type _z, Type _w)             : x(_x),  y(_y),  z(_z),  w(_w) {  }
};

// TODO: maike struct, and make constructor for vecs here and there
template<typename Type>
using rgb = vec3<Type>;

template<typename Type>
using rgba = vec4<Type>;


#endif //OPENGL_VEC_H
