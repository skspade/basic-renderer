#include <cmath>
#include "tgaimage.h"

void line(int startX, int startY, int endX, int endY, TGAImage &image, TGAColor color)
{
    for (float interpolationFactor = 0; interpolationFactor < 1; interpolationFactor += 0.1)
    {
        int currentX = startX + (endX - startX) * interpolationFactor;
        int currentY = startY + (endY - startY) * interpolationFactor;
        image.set(currentX, currentY, color);
    }
}

// Define color constants in BGRA format (Blue, Green, Red, Alpha)
// Each color component ranges from 0-255
constexpr TGAColor white = {{255, 255, 255, 255}}; // Pure white (all channels at max)
constexpr TGAColor green = {{0, 255, 0, 255}};     // Pure green
constexpr TGAColor red = {{0, 0, 255, 255}};       // Pure red
constexpr TGAColor blue = {{255, 128, 64, 255}};   // Custom blue
constexpr TGAColor yellow = {{0, 200, 255, 255}};  // Custom yellow

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

    // Set individual pixels to white at the specified coordinates
    // This is the most basic form of rendering - setting individual pixels
    framebuffer.set(ax, ay, white); // Draw point A
    framebuffer.set(bx, by, white); // Draw point B
    framebuffer.set(cx, cy, white); // Draw point C

    // Save the framebuffer to a TGA image file
    // This creates a 64x64 image with three white dots
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}
