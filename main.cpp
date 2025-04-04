#include <cmath>
#include "tgaimage.h"

// Define color constants in BGRA format (Blue, Green, Red, Alpha)
// Each color component ranges from 0-255
constexpr TGAColor white = {{255, 255, 255, 255}}; // Pure white (all channels at max)
constexpr TGAColor green = {{0, 255, 0, 255}};     // Pure green
constexpr TGAColor red = {{0, 0, 255, 255}};       // Pure red
constexpr TGAColor blue = {{255, 128, 64, 255}};   // Custom blue
constexpr TGAColor yellow = {{0, 200, 255, 255}};  // Custom yellow

void line(int startX, int startY, int endX, int endY, TGAImage &framebuffer, TGAColor color)
{
    // Iterate through each x-coordinate between start and end points
    for (int x = startX; x <= endX; x++)
    {
        // Check if the line is steep (more vertical than horizontal) rises more than it runs
        bool steep = std::abs(endY - startY) > std::abs(endX - startX);
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
    constexpr int width = 64;  // Width in pixels
    constexpr int height = 64; // Height in pixels

    // Create a new TGA image with specified dimensions and RGB color mode
    // This acts as our framebuffer - the memory where we'll draw our image
    TGAImage framebuffer(width, height, TGAImage::RGB);

    // Define coordinates for three points that will form a triangle
    // Each point has an x (horizontal) and y (vertical) coordinate
    int ax = 7, ay = 3;   // Point A coordinates
    int bx = 12, by = 37; // Point B coordinates
    int cx = 62, cy = 53; // Point C coordinates

    // Draw the points
    framebuffer.set(ax, ay, white); // Draw point A
    framebuffer.set(bx, by, white); // Draw point B
    framebuffer.set(cx, cy, white); // Draw point C

    // Draw the lines between points with different colors
    line(ax, ay, bx, by, framebuffer, blue);   // Draw blue line from A to B
    line(bx, by, cx, cy, framebuffer, green);  // Draw green line from B to C
    line(ax, ay, cx, cy, framebuffer, red);    // Draw red line from A to C
    line(cx, cy, ax, ay, framebuffer, yellow); // Draw yellow line from C to A

    // Save the framebuffer to a TGA image file
    // This creates a 64x64 image with three white dots
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
