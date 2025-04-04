#include "obj_loader.h"
#include <iostream>

int main()
{
    try
    {
        // Load a model from an OBJ file
        Model model = OBJLoader::loadFromFile("obj/floor.obj");

        // Print some statistics about the loaded model
        std::cout << "Loaded model statistics:" << std::endl;
        std::cout << "Number of vertices: " << model.getVertexCount() << std::endl;
        std::cout << "Number of edges: " << model.getEdgeCount() << std::endl;

        // Example: Print the first few vertices
        std::cout << "\nFirst few vertices:" << std::endl;
        for (size_t i = 0; i < std::min(model.getVertexCount(), size_t(5)); i++)
        {
            const vec3 &v = model.getVertex(i);
            std::cout << "Vertex " << i << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
        }

        // Example: Print the first few edges
        std::cout << "\nFirst few edges:" << std::endl;
        for (size_t i = 0; i < std::min(model.getEdgeCount(), size_t(5)); i++)
        {
            const auto &edge = model.getEdge(i);
            std::cout << "Edge " << i << ": " << edge.first << " -> " << edge.second << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}