/// --- VEC1 ---
template<typename Type>
double vec1<Type>::length() const
requires std::is_arithmetic_v<Type>
{
    return this->x;
}

template<typename Type>
vec1<double> vec1<Type>::normalized() const
requires std::is_arithmetic_v<Type>
{
    return vec1<double>{ 1.0 };
}

template<typename Type>
Type& vec1<Type>::operator[](unsigned char i)
{
    if (i < 1)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec1 only has 1 component"};
}
template<typename Type>
Type vec1<Type>::operator[](unsigned char i) const
{
    if (i < 1)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec1 only has 1 component"};
}

// -- vector addition

template<typename Type> template<typename Type2>
vec4<Type> vec1<Type>::operator+(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
                  other.y,
                  other.z,
                  other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec1<Type>::operator+(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
                  other.y,
                  other.z
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec1<Type>::operator+(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
                  other.y
    };
}

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator+(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x
    };
}

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator+(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + val
    };
}

// -- vector subtraction

template<typename Type> template<typename Type2>
vec4<Type> vec1<Type>::operator-(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
                - other.y,
                - other.z,
                - other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec1<Type>::operator-(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
                - other.y,
                - other.z
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec1<Type>::operator-(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
                - other.y
    };
}

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator-(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x
    };
}

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator-(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - val
    };
}

// -- vector division

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator/(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x / val
    };
}

// -- vector multiplication

template<typename Type> template<typename Type2>
double vec1<Type>::dot_mult(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return (double) this->x * other.x;
}

template<typename Type> template<typename Type2>
vec1<Type> vec1<Type>::operator*(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x * val
    };
}



/// --- VEC2 ---
template<typename Type>
double vec2<Type>::length() const
requires std::is_arithmetic_v<Type>
{
    return sqrt(SQR(this->x) + SQR(this->y));
}

template<typename Type>
vec2<double> vec2<Type>::normalized() const
requires std::is_arithmetic_v<Type>
{
    double len = this->length();
    return {
        this->x / len,
        this->y / len
    };
}

template<typename Type>
Type& vec2<Type>::operator[](unsigned char i)
{
    if (i < 2)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec2 only has 2 components"};
}

template<typename Type>
Type vec2<Type>::operator[](unsigned char i) const
{
    if (i < 2)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec2 only has 2 components"};
}

// -- vector addition

template<typename Type> template<typename Type2>
vec4<Type> vec2<Type>::operator+(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
                  other.z,
                  other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec2<Type>::operator+(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
                  other.z
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator+(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator+(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator+(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + val,
        this->y + val
    };
}

// -- vector subtraction

template<typename Type> template<typename Type2>
vec4<Type> vec2<Type>::operator-(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
                - other.z,
                - other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec2<Type>::operator-(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
                - other.z
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator-(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator-(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y
    };
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator-(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - val,
        this->y - val
    };
}

// -- vector division

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator/(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x / val,
        this->y / val
    };
}

// -- vector multiplication

template<typename Type> template<typename Type2>
double vec2<Type>::dot_mult(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return (double) this->x * other.x +
           (double) this->y * other.y ;
}

template<typename Type> template<typename Type2>
vec2<Type> vec2<Type>::operator*(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x * val,
        this->y * val
    };
}



/// --- VEC3 ---
template<typename Type>
double vec3<Type>::length() const
requires std::is_arithmetic_v<Type>
{
    return sqrt(SQR(this->x) + SQR(this->y) + SQR(this->z));
}

template<typename Type>
vec3<double> vec3<Type>::normalized() const
requires std::is_arithmetic_v<Type>
{
    double len = this->length();
    return {
        this->x / len,
        this->y / len,
        this->z / len
    };
}

template<typename Type>
Type& vec3<Type>::operator[](unsigned char i)
{
    if (i < 3)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec3 only has 3 components"};
}
template<typename Type>
Type vec3<Type>::operator[](unsigned char i) const
{
    if (i < 3)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec3 only has 3 components"};
}

// -- vector addition

template<typename Type> template<typename Type2>
vec4<Type> vec3<Type>::operator+(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z,
                  other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator+(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator+(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator+(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y,
        this->z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator+(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + val,
        this->y + val,
        this->z + val
    };
}

// -- vector subtraction

template<typename Type> template<typename Type2>
vec4<Type> vec3<Type>::operator-(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z,
                - other.w
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator-(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator-(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator-(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y,
        this->z
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator-(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - val,
        this->y - val,
        this->z - val
    };
}

// -- vector division

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator/(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x / val,
        this->y / val,
        this->z / val
    };
}

// -- vector multiplication

template<typename Type> template<typename Type2>
double vec3<Type>::dot_mult(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return (double) this->x * other.x +
           (double) this->y * other.y +
           (double) this->z * other.z ;
}

template<typename Type> template<typename Type2>
vec3<double> vec3<Type>::cross_mult(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        (double) this->y * other.z - this->z * other.y,
        (double) this->z * other.x - this->x * other.z,
        (double) this->x * other.y - this->y * other.x
    };
}

template<typename Type> template<typename Type2>
vec3<Type> vec3<Type>::operator*(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x * val,
        this->y * val,
        this->z * val
    };
}



/// --- VEC4 ---
template<typename Type>
double vec4<Type>::length() const
requires std::is_arithmetic_v<Type>
{
    return sqrt(SQR(this->x) + SQR(this->y) + SQR(this->z) + SQR(this->w));
}

template<typename Type>
vec4<double> vec4<Type>::normalized() const
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

template<typename Type>
Type& vec4<Type>::operator[](unsigned char i)
{
    if (i < 3)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec4 only has 4 components"};
}
template<typename Type>
Type vec4<Type>::operator[](unsigned char i) const
{
    if (i < 3)
        return *(&this->x + i);
    throw std::out_of_range{"STD::OUT_OF_RANGE Exception: vec4 only has 4 components"};
}

// -- vector addition

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator+(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z,
        this->w + other.w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator+(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator+(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y + other.y,
        this->z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator+(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + other.x,
        this->y,
        this->z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator+(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x + val,
        this->y + val,
        this->z + val,
        this->w + val
    };
}

// -- vector subtraction

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator-(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z,
        this->w - other.w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator-(const vec3<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator-(const vec2<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y - other.y,
        this->z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator-(const vec1<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - other.x,
        this->y,
        this->z,
        this->w
    };
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator-(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x - val,
        this->y - val,
        this->z - val,
        this->w - val
    };
}

// -- vector division

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator/(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x / val,
        this->y / val,
        this->z / val,
        this->w / val
    };
}

// -- vector multiplication

template<typename Type> template<typename Type2>
double vec4<Type>::dot_mult(const vec4<Type2>& other) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return (double) this->x * other.x +
           (double) this->y * other.y +
           (double) this->z * other.z +
           (double) this->w * other.w ;
}

template<typename Type> template<typename Type2>
vec4<Type> vec4<Type>::operator*(const Type2& val) const
requires std::is_arithmetic_v<Type> && std::is_arithmetic_v<Type2>
{
    return {
        this->x * val,
        this->y * val,
        this->z * val,
        this->w * val
    };
}




// --- PRINTING VECS ---
// -- vec1
template<typename Type>
std::ostream& operator<<(std::ostream &os, const vec1<Type>& v)
{
    os << "{ " << v.x << " }";
    return os;
}
// TODO: (vec1) Fix Linker problem with template overload for print char, str
// std::ostream& operator<<(std::ostream &os, const vec1<char>& v)
// {
//     os << "{ '" << v.x << "' }";
//     return os;
// }
// std::ostream& operator<<(std::ostream &os, const vec1<std::string>& v)
// {
//     os << "{ \"" << v.x << "\" }";
//     return os;
// }

// -- vec2
template<typename Type>
std::ostream &operator<<(std::ostream &os, const vec2<Type> &v)
{
    os << "{ " << v.x << ", " << v.y << " }";
    return os;
}
// TODO: (vec2) Fix Linker problem with template overload for print char, str
// std::ostream& operator<<(std::ostream &os, const vec2<char>& v)
// {
//     os << "{ '" << v.x << "', '" << v.y << "' }";
//     return os;
// }
// std::ostream& operator<<(std::ostream &os, const vec2<std::string>& v)
// {
//     os << "{ \"" << v.x << "\", \"" << v.y << "\" }";
//     return os;
// }

// -- vec3
template<typename Type>
std::ostream& operator<<(std::ostream &os, const vec3<Type>& v)
{
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
}
// TODO: (vec3) Fix Linker problem with template overload for print char, str
// std::ostream& operator<<(std::ostream &os, const vec3<char>& v)
// {
//     os << "{ '" << v.x << "', '" << v.y << "', '" << v.z << "' }";
//     return os;
// }
// std::ostream& operator<<(std::ostream &os, const vec3<std::string>& v)
// {
//     os << "{ \"" << v.x << "\", \"" << v.y << "\", \"" << v.z << "\" }";
//     return os;
// }

// -- vec4
template<typename Type>
std::ostream& operator<<(std::ostream &os, const vec4<Type>& v)
{
    os << "{ " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " }";
    return os;
}
// TODO: (vec4) Fix Linker problem with template overload for print char, str
// std::ostream& operator<<(std::ostream &os, const vec4<char>& v)
// {
//     os << "{ '" << v.x << "', '" << v.y << "', '" << v.z << "', '" << v.w << "' }";
//     return os;
// }
// std::ostream& operator<<(std::ostream &os, const vec4<std::string>& v)
// {
//     os << "{ \"" << v.x << "\", \"" << v.y << "\", \"" << v.z << "\", \"" << v.w << "\" }";
//     return os;
// }
