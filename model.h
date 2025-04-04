#pragma once
#include <vector>
#include "geometry.h" // Assuming Vec3f is defined here

/**
 * @brief A 3D model class that represents a mesh with vertices and edges
 *
 * This class stores the geometric data of a 3D model, including:
 * - Vertices: Points in 3D space
 * - Edges: Connections between vertices
 */
class Model
{
private:
    std::vector<vec3> vertices_;             // List of vertices in the model
    std::vector<std::pair<int, int>> edges_; // List of edges as pairs of vertex indices

public:
    /**
     * @brief Default constructor
     */
    Model() = default;

    /**
     * @brief Add a vertex to the model
     * @param vertex The 3D point to add
     * @return The index of the added vertex
     */
    int addVertex(const vec3 &vertex)
    {
        vertices_.push_back(vertex);
        return static_cast<int>(vertices_.size() - 1);
    }

    /**
     * @brief Add an edge between two vertices
     * @param v1 Index of the first vertex
     * @param v2 Index of the second vertex
     */
    void addEdge(int v1, int v2)
    {
        edges_.emplace_back(v1, v2);
    }

    /**
     * @brief Get the number of vertices in the model
     * @return The vertex count
     */
    size_t getVertexCount() const
    {
        return vertices_.size();
    }

    /**
     * @brief Get the number of edges in the model
     * @return The edge count
     */
    size_t getEdgeCount() const
    {
        return edges_.size();
    }

    /**
     * @brief Get a vertex by index
     * @param index The vertex index
     * @return The vertex at the specified index
     */
    const vec3 &getVertex(int index) const
    {
        return vertices_[index];
    }

    /**
     * @brief Get an edge by index
     * @param index The edge index
     * @return The edge at the specified index as a pair of vertex indices
     */
    const std::pair<int, int> &getEdge(int index) const
    {
        return edges_[index];
    }

    /**
     * @brief Get all vertices
     * @return A const reference to the vector of vertices
     */
    const std::vector<vec3> &getVertices() const
    {
        return vertices_;
    }

    /**
     * @brief Get all edges
     * @return A const reference to the vector of edges
     */
    const std::vector<std::pair<int, int>> &getEdges() const
    {
        return edges_;
    }
};
