#pragma once

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
};

template <typename Type>
struct vec2
{
    Type x;
    Type y;

             vec2(const vec1<Type>& v, Type _y) : x(v.x), y(_y)  {  }
             vec2(Type _x, Type _y)             : x(_x),  y(_y)  {  }
    explicit vec2(const vec3<Type>& v)          : x(v.x), y(v.y) {  }
    explicit vec2(const vec4<Type>& v)          : x(v.x), y(v.y) {  }
};

template <typename Type>
struct vec3
{
    Type x;
    Type y;
    Type z;

             vec3(const vec1<Type>& v, Type _y, Type _z) : x(v.x), y(_y),  z(_z)  {  }
             vec3(const vec2<Type>& v, Type _z)          : x(v.x), y(v.y), z(_z)  {  }
             vec3(Type _x, Type _y, Type _z)             : x(_x),  y(_y),  z(_z)  {  }
    explicit vec3(const vec4<Type>& v)                   : x(v.x), y(v.y), z(v.z) {  }
};

template <typename Type>
struct vec4
{
    Type x;
    Type y;
    Type z;
    Type w;

    vec4(const vec1<Type>& v, Type _y, Type _z, Type _w) : x(v.x), y(_y),  z(_z),  w(_w) {  }
    vec4(const vec2<Type>& v, Type _z, Type _w)          : x(v.x), y(v.y), z(_z),  w(_w) {  }
    vec4(const vec3<Type>& v, Type _w)                   : x(v.x), y(v.y), z(v.z), w(_w) {  }
    vec4(Type _x, Type _y, Type _z, Type _w)             : x(_x),  y(_y),  z(_z),  w(_w) {  }
};

#endif //OPENGL_VEC_H
