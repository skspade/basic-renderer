#pragma once
#include "model.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

/**
 * @brief A class for loading Wavefront OBJ files and converting them to Model objects
 */
class OBJLoader
{
public:
    /**
     * @brief Loads an OBJ file and converts it to a Model object
     * @param filename The path to the OBJ file
     * @return A Model object containing the loaded mesh data
     * @throws std::runtime_error if the file cannot be opened or parsed
     */
    static Model loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        Model model;
        std::vector<vec3> vertices;
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "v")
            { // Vertex
                float x, y, z;
                iss >> x >> y >> z;
                vertices.push_back(vec3(x, y, z));
            }
            else if (type == "f")
            { // Face
                std::vector<int> faceIndices;
                std::string vertex;
                while (iss >> vertex)
                {
                    // OBJ indices are 1-based, convert to 0-based
                    int idx = std::stoi(vertex) - 1;
                    faceIndices.push_back(idx);
                }

                // Create edges for the face (assuming triangular faces)
                if (faceIndices.size() >= 3)
                {
                    for (size_t i = 0; i < faceIndices.size(); i++)
                    {
                        int current = faceIndices[i];
                        int next = faceIndices[(i + 1) % faceIndices.size()];
                        model.addEdge(current, next);
                    }
                }
            }
        }

        // Add all vertices to the model
        for (const auto &vertex : vertices)
        {
            model.addVertex(vertex);
        }

        return model;
    }
};