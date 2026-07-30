#include <cstdint>
#include <string>
#include <vector>

enum class ImageFormat {
    PNG,
    JPEG,
    BMP,
    TGA
};

struct Image{
    uint8_t* data = nullptr;
    size_t size = 0;
    int width;
    int height;
    int channels;
    
    Image(const char* filename);
    Image(int width, int height, int channels);
    Image(const Image& other);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename);

    ImageFormat getFormat(const char* filename);

    Image& grayscale();
    Image& invert();
    Image& threshold(uint8_t thresholdValue);
    Image& maxContrast();
    Image& twoBandThreshold(uint8_t lowThreshold, uint8_t highThreshold);
    Image sobelEdgeDetection(std::vector<int> &angles, int threshold );

    Image& operator=(const Image& other);
};