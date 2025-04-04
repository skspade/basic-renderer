#include "geometry.h"
#include <cmath>

// Most operations are implemented inline in the header file for performance
// Only the more complex operations should be implemented here

vec3 vec3::normalize() const
{
    float len = length();
    // Avoid division by zero
    if (len > 0)
    {
        return *this / len;
    }
    return *this; // Return original vector if length is zero
}

// Overload the multiplication operator to allow scalar * vector
vec3 operator*(float scalar, const vec3 &v)
{
    return v * scalar;
}

// Overload the division operator to allow vector / scalar
vec3 operator/(float scalar, const vec3 &v)
{
    return vec3(scalar / v.x, scalar / v.y, scalar / v.z);
}

// Overload the output stream operator
std::ostream &operator<<(std::ostream &os, const vec3 &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}