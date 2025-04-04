#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

// TGA (Truevision Targa) file format header structure
// The #pragma pack ensures the struct is packed without padding
#pragma pack(push,1)
struct TGAHeader {
    std::uint8_t  idlength = 0;        // Length of the image ID field
    std::uint8_t  colormaptype = 0;    // Whether a color map is included
    std::uint8_t  datatypecode = 0;    // Image type (uncompressed, RLE, etc.)
    std::uint16_t colormaporigin = 0;  // First color map entry
    std::uint16_t colormaplength = 0;  // Number of color map entries
    std::uint8_t  colormapdepth = 0;   // Bits per color map entry
    std::uint16_t x_origin = 0;        // X coordinate of lower left corner
    std::uint16_t y_origin = 0;        // Y coordinate of lower left corner
    std::uint16_t width = 0;           // Image width in pixels
    std::uint16_t height = 0;          // Image height in pixels
    std::uint8_t  bitsperpixel = 0;    // Bits per pixel (8, 16, 24, 32)
    std::uint8_t  imagedescriptor = 0; // Image attributes (alpha, origin)
};
#pragma pack(pop)

// Color structure for TGA images
// Uses BGRA format (Blue, Green, Red, Alpha)
struct TGAColor {
    std::uint8_t bgra[4] = {0,0,0,0};  // Color components in BGRA order
    std::uint8_t bytespp = 4;          // Bytes per pixel (4 for RGBA)
    std::uint8_t& operator[](const int i) { return bgra[i]; } // Array access operator
};

// Main TGA image class for handling TGA file operations
struct TGAImage {
    // Supported image formats
    enum Format { 
        GRAYSCALE=1,  // 8-bit grayscale
        RGB=3,        // 24-bit RGB
        RGBA=4        // 32-bit RGBA
    };

    TGAImage() = default;  // Default constructor
    TGAImage(const int w, const int h, const int bpp); // Constructor with dimensions and bits per pixel

    // File operations
    bool  read_tga_file(const std::string filename);  // Read TGA file from disk
    bool write_tga_file(const std::string filename, const bool vflip=true, const bool rle=true) const; // Write TGA file to disk

    // Image manipulation
    void flip_horizontally();  // Flip image horizontally
    void flip_vertically();    // Flip image vertically
    TGAColor get(const int x, const int y) const;  // Get pixel color at (x,y)
    void set(const int x, const int y, const TGAColor &c);  // Set pixel color at (x,y)

    // Image properties
    int width()  const;  // Get image width
    int height() const;  // Get image height

private:
    // Private helper methods for RLE (Run-Length Encoding) compression
    bool   load_rle_data(std::ifstream &in);    // Load RLE compressed data
    bool unload_rle_data(std::ofstream &out) const; // Save data with RLE compression

    // Image data storage
    int w = 0, h = 0;  // Width and height
    std::uint8_t bpp = 0;  // Bits per pixel
    std::vector<std::uint8_t> data = {};  // Raw pixel data
};

