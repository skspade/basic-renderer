#pragma once
#include <cmath>
#include <iostream>

/**
 * @brief A 3D vector class for representing points, directions, and colors in 3D space
 *
 * In 3D graphics, vectors are used to represent:
 * - Points in 3D space (x, y, z coordinates)
 * - Directions (like which way a surface is facing)
 * - Colors (RGB values)
 * - Forces and velocities
 */
class vec3
{
public:
    float x, y, z; // The three components of the vector

    /**
     * @brief Default constructor - creates a zero vector
     *
     * A zero vector has all components set to 0. It represents:
     * - The origin point (0,0,0)
     * - A vector with no direction or magnitude
     */
    vec3() : x(0), y(0), z(0) {}

    /**
     * @brief Constructor with explicit components
     * @param x X component (horizontal)
     * @param y Y component (vertical)
     * @param z Z component (depth)
     */
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * @brief Vector addition
     *
     * Adding two vectors combines their components:
     * (x1,y1,z1) + (x2,y2,z2) = (x1+x2, y1+y2, z1+z2)
     *
     * This is used for:
     * - Moving points in space
     * - Combining forces
     * - Translating objects
     */
    vec3 operator+(const vec3 &v) const
    {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    /**
     * @brief Vector subtraction
     *
     * Subtracting vectors gives the difference between them:
     * (x1,y1,z1) - (x2,y2,z2) = (x1-x2, y1-y2, z1-z2)
     *
     * This is used for:
     * - Finding the direction between two points
     * - Calculating relative positions
     */
    vec3 operator-(const vec3 &v) const
    {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    /**
     * @brief Scalar multiplication
     *
     * Multiplying a vector by a scalar (number) scales its length:
     * (x,y,z) * s = (x*s, y*s, z*s)
     *
     * This is used for:
     * - Scaling objects
     * - Changing vector magnitude
     * - Interpolating between vectors
     */
    vec3 operator*(float scalar) const
    {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Scalar division
     *
     * Dividing a vector by a scalar shrinks its length:
     * (x,y,z) / s = (x/s, y/s, z/s)
     *
     * Note: Division by zero is not handled here
     */
    vec3 operator/(float scalar) const
    {
        return vec3(x / scalar, y / scalar, z / scalar);
    }

    /**
     * @brief Dot product (scalar product)
     *
     * The dot product of two vectors measures how much they point in the same direction:
     * (x1,y1,z1) · (x2,y2,z2) = x1*x2 + y1*y2 + z1*z2
     *
     * This is used for:
     * - Calculating angles between vectors
     * - Projecting one vector onto another
     * - Testing if vectors are perpendicular
     */
    float dot(const vec3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    /**
     * @brief Cross product (vector product)
     *
     * The cross product of two vectors gives a new vector perpendicular to both:
     * (x1,y1,z1) × (x2,y2,z2) = (y1*z2-z1*y2, z1*x2-x1*z2, x1*y2-y1*x2)
     *
     * This is used for:
     * - Finding surface normals
     * - Calculating torque
     * - Creating coordinate systems
     */
    vec3 cross(const vec3 &v) const
    {
        return vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    /**
     * @brief Vector length (magnitude)
     *
     * The length of a vector is calculated using the Pythagorean theorem:
     * length = sqrt(x² + y² + z²)
     *
     * This is used for:
     * - Normalizing vectors
     * - Measuring distances
     * - Comparing vector sizes
     */
    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    /**
     * @brief Normalize the vector
     *
     * Normalization converts a vector to a unit vector (length = 1)
     * while preserving its direction:
     * normalized = vector / length
     *
     * This is used for:
     * - Representing pure directions
     * - Surface normals
     * - Light directions
     */
    vec3 normalize() const
    {
        float len = length();
        return len > 0 ? *this / len : *this;
    }

    /**
     * @brief Output stream operator for debugging
     *
     * Allows printing vectors in a readable format:
     * vec3 v(1,2,3);
     * std::cout << v;  // Outputs: (1, 2, 3)
     */
    friend std::ostream &operator<<(std::ostream &os, const vec3 &v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};