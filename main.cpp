#include <cmath>
#include <filesystem>
#include "tgaimage.h"
#include "model.h"
#include "obj_loader.h"

// Define color constants in BGRA format (Blue, Green, Red, Alpha)
// Each color component ranges from 0-255
constexpr TGAColor white = {{255, 255, 255, 255}}; // Pure white (all channels at max)
constexpr TGAColor green = {{0, 255, 0, 255}};     // Pure green
constexpr TGAColor red = {{0, 0, 255, 255}};       // Pure red
constexpr TGAColor blue = {{255, 128, 64, 255}};   // Custom blue
constexpr TGAColor yellow = {{0, 200, 255, 255}};  // Custom yellow

void line(int startX, int startY, int endX, int endY, TGAImage &framebuffer, TGAColor color)
{
    // Check if the line is steep (more vertical than horizontal) rises more than it runs
    bool steep = std::abs(endY - startY) > std::abs(endX - startX);
    if (steep)
    {
        std::swap(startX, startY);
        std::swap(endX, endY);
    }
    // Iterate through each x-coordinate between start and end points
    for (int x = startX; x <= endX; x++)
    {
        if (startX > endX)
        {
            // Swap the start and end points if startX is greater than endX
            // This ensures we always iterate from left to right
            std::swap(startX, endX);
            std::swap(startY, endY);
        }
        // Calculate the interpolation factor (t) between 0 and 1
        // This represents how far along the line we are from start to end
        // t = 0 means we're at the start point
        // t = 1 means we're at the end point
        float interpolationFactor = (x - startX) / static_cast<float>(endX - startX);

        // Use linear interpolation to find the corresponding y-coordinate
        // y = y1 + (y2 - y1) * t
        // This formula gives us a point that lies on the line between (startX, startY) and (endX, endY)
        // The interpolation ensures we get a straight line by calculating the exact y position
        // for each x position based on the ratio of how far we've progressed along the line
        int y = startY + (endY - startY) * interpolationFactor;

        // Set the pixel at the calculated (x,y) position to the specified color
        // For steep lines (where vertical change > horizontal change), we transpose the coordinates
        // This is crucial because:
        // 1. Steep lines have large y-changes between x-steps, causing gaps because we are iterating through x-coordinates.
        // 2. By transposing, we convert the steep line into a shallow line relative to our iteration
        // 3. This gives us more sampling points along the line's primary axis of change
        // 4. The result is a continuous line with no gaps, regardless of angle
        // Example: For a line from (0,0) to (1,10):
        // - Without transposing: Only 2 points (at x=0 and x=1)
        // - With transposing: 10 points (at y=0 through y=10)
        if (steep)
        {
            framebuffer.set(y, x, color);
        }
        else
        {
            framebuffer.set(x, y, color);
        }
    }
}

int main(int argc, char **argv)
{
    // Define the dimensions of our framebuffer (image)
    constexpr int width = 800;  // Increased width to accommodate the model
    constexpr int height = 800; // Increased height to accommodate the model

    // Create a new TGA image with specified dimensions and RGB color mode
    TGAImage framebuffer(width, height, TGAImage::RGB);

    try
    {
        // Get the absolute path to the model file by going up one directory from the build folder
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::filesystem::path projectRoot = currentPath.parent_path();
        std::filesystem::path modelPath = projectRoot / "obj" / "diablo3_pose" / "diablo3_pose.obj";

        std::cout << "Loading model from: " << modelPath << std::endl;

        // Load the diablo3_pose.obj model
        Model model = OBJLoader::loadFromFile(modelPath.string());

        // Print model statistics
        std::cout << "Model loaded successfully:" << std::endl;
        std::cout << "Number of vertices: " << model.getVertexCount() << std::endl;
        std::cout << "Number of edges: " << model.getEdgeCount() << std::endl;

        // Draw all edges of the model
        for (size_t i = 0; i < model.getEdgeCount(); i++)
        {
            const auto &edge = model.getEdge(i);
            const vec3 &v1 = model.getVertex(edge.first);
            const vec3 &v2 = model.getVertex(edge.second);

            // Convert 3D coordinates to 2D screen coordinates
            // Simple orthographic projection for now
            int x1 = static_cast<int>((v1.x + 1.0f) * width / 2.0f);
            int y1 = static_cast<int>((v1.y + 1.0f) * height / 2.0f);
            int x2 = static_cast<int>((v2.x + 1.0f) * width / 2.0f);
            int y2 = static_cast<int>((v2.y + 1.0f) * height / 2.0f);

            // Draw the edge
            line(x1, y1, x2, y2, framebuffer, white);
        }

        // Save the framebuffer to a TGA image file
        framebuffer.write_tga_file("framebuffer.tga");
        std::cout << "Image saved to framebuffer.tga" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
