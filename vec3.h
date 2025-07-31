#ifndef VEC3_H
#define VEC3_H

template <typename T>
class vec3
{
public:
    T x, y, z;

    vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    vec3(T xx) : x(xx), y(xx), z(xx) {}
    vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    vec3<T> operator-() const
    {
        return vec3<T>(-x, -y, -z);
    }

    vec3<T> &operator+=(const vec3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3<T> &operator*=(T t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3<T> &operator/=(T t)
    {
        return *this *= 1 / t;
    }

    T length() const
    {
        return std::sqrt(length_sq());
    }

    T length_sq() const
    {
        return x * x + y * y + z * z;
    }

    T sum() const
    {
        return x + y + z;
    }
};

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const vec3<T> &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <typename T>
inline vec3<T> operator*(T t, const vec3<T> &v)
{
    return vec3<T>(t * v.x, t * v.y, t * v.z);
}

// Commutative behaviour
template <typename T>
inline vec3<T> operator*(const vec3<T> &v, T t)
{
    return t * v;
}

template <typename T>
inline vec3<T> operator/(const vec3<T> &v, T t)
{
    return (1 / t) * v;
}

template <typename T>
inline T dot(const vec3<T> &u, const vec3<T> &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T>
inline vec3<T> cross(const vec3<T> &u, const vec3<T> &v)
{
    return vec3<T>(u.y * v.z - u.z * v.y,
                   u.z * v.x - u.x * v.z,
                   u.x * v.y - u.y * v.x);
}

template <typename T>
inline vec3<T> normalize(const vec3<T> &v) // Unit vector
{
    T len = v.length_sq();
    return (len > 0) ? v / std::sqrt(len) : vec3<T>(); // Avoid div by 0
}

using point3f = vec3<float>;
using vec3f = vec3<float>;

#endif // VEC3_H