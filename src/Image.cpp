#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include "Image.h"

#include <iostream>

Image::Image(const char* filename) {
    if(read(filename)){
        std::cout << "Read image: " << filename << std::endl;
        size = width * height * channels;
    }
    else{
        std::cerr << "Failed to read image: " << filename << std::endl;
    }
}

Image::Image(int width, int height, int channels) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->size = width * height * channels;
    this->data = (uint8_t*)malloc(size);
    memset(this->data, 0, size); 
}

Image::Image(const Image& other) {
    this->width = other.width;
    this->height = other.height;
    this->channels = other.channels;
    this->size = other.size;
    this->data = (uint8_t*)malloc(size);
    memcpy(this->data, other.data, size);
}

Image::~Image() {
    free(data);
}

bool Image::read(const char* filename){
    int original_channels; // Temporary variable
    
    // Pass &original_channels as the 4th argument, NOT &channels
    data = stbi_load(filename, &width, &height, &original_channels, 3);
    
    if (data != nullptr) {
        // Manually tell your struct that the data array has 3 channels per pixel
        this->channels = 3; 
        return true;
    }
    return false;
}
bool Image::write(const char* filename){
    ImageFormat format = getFormat(filename);
    int success = 0;
    switch (format) {
        case ImageFormat::PNG:
            success = stbi_write_png(filename, width, height, channels, data, width * channels);
            break;
        case ImageFormat::JPEG:
            success = stbi_write_jpg(filename, width, height, channels, data, 100);
            break;
        case ImageFormat::BMP:
            success = stbi_write_bmp(filename, width, height, channels, data);
            break;
        case ImageFormat::TGA:
            success = stbi_write_tga(filename, width, height, channels, data);
            break;
    }
    return success != 0;
}

ImageFormat Image::getFormat(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (ext != nullptr) {
        if (strcmp(ext, ".png") == 0) return ImageFormat::PNG;
        if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return ImageFormat::JPEG;
        if (strcmp(ext, ".bmp") == 0) return ImageFormat::BMP;
        if (strcmp(ext, ".tga") == 0) return ImageFormat::TGA;
    }
    return ImageFormat::PNG; // Default format
}

Image& Image::grayscale() {
    if (channels < 3) {
        std::cerr << "Image does not have enough channels to convert to grayscale." << std::endl;
        return *this;
    }
    for (int i = 0; i < width * height * channels; i += channels) {
        uint8_t gray = (0.2126*data[i] + 0.7152*data[i + 1] + 0.0722*data[i + 2]);
        data[i] = data[i + 1] = data[i + 2] = gray;
    }
    return *this;
}

Image& Image::operator=(const Image& other) {
    if (this != &other) { 
        free(this->data); 
        this->width = other.width;
        this->height = other.height;
        this->channels = other.channels;
        this->size = other.size;
        this->data = (uint8_t*)malloc(this->size); 
        memcpy(this->data, other.data, this->size); 
    }
    return *this;
}

Image& Image::invert() {
    for (int i = 0; i < width * height * channels; ++i) {
        data[i] = 255 - data[i];
    }
    return *this;
}

Image& Image::threshold(uint8_t thresholdValue) {
    for (int i = 0; i < width * height * channels; i += channels) { // Assuming grayscale
        data[i] = (data[i] > thresholdValue) ? 255 : 0;
    }
    return *this;
}

Image& Image::maxContrast() {
    uint8_t minVal = 255;
    uint8_t maxVal = 0;
    for (int i = 0; i < width * height * channels; i += channels) { // Assuming grayscale
        if (data[i] < minVal) minVal = data[i];
        if (data[i] > maxVal) maxVal = data[i];
    }

    for (int i = 0; i < width * height * channels; i += channels) { // Assuming grayscale
        data[i] = static_cast<uint8_t>(255.0 * (data[i] - minVal) / (maxVal - minVal));
    }

    return *this;
}

Image& Image::twoBandThreshold(uint8_t lowThreshold, uint8_t highThreshold){
    for (int i = 0; i < width * height * channels; i += channels) { // Assuming grayscale
        if (data[i] < lowThreshold) {
            data[i] = 0; // Black
            data[i + 1] = 0; // Black
            data[i + 2] = 0; // Black
        } else if (data[i] > highThreshold) {
            data[i] = 255; // White
            data[i + 1] = 255; // White
            data[i + 2] = 255; // White
        }
    }
    return *this;
}

Image Image::sobelEdgeDetection(std::vector<int> &angles, int threshold) {
    if (channels < 3) {
        std::cerr << "Image does not have enough channels for edge detection." << std::endl;
        return Image(0, 0, 0);
    }

    Image edgeImg(width, height, channels);
    angles.assign(width * height, -1);

    std::vector<int> magBuffer(width * height, 0);
    std::vector<float> angleBuffer(width * height, 0.0f);

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int sumX = 0;
            int sumY = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int pixelIndex = ((y + ky) * width + (x + kx)) * channels;
                    uint8_t grayValue = data[pixelIndex]; // Assuming grayscale

                    sumX += grayValue * gx[ky + 1][kx + 1];
                    sumY += grayValue * gy[ky + 1][kx + 1];
                }
            }

            int pixelIndex = y * width + x; 
            magBuffer[pixelIndex] = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            
            angleBuffer[pixelIndex] = static_cast<float>(atan2(sumY, sumX) * 180 / M_PI);
        }

    }

    for(int y = 1; y < height - 1; ++y){
        for(int x = 1; x < width - 1; ++x){
            int index = y * width + x;
            int mag = magBuffer[index];

            if(mag > threshold){
                float direction = angleBuffer[index];
                if(direction < 0) direction += 180;

                int neighborA = 255;
                int neighborB = 255;

                if ((direction >= 0 && direction < 22.5) || (direction >= 157.5 && direction <= 180)) {
                    neighborA = magBuffer[y * width + (x + 1)]; // Right
                    neighborB = magBuffer[y * width + (x - 1)]; // Left
                } else if (direction >= 22.5 && direction < 67.5) {
                    neighborA = magBuffer[(y - 1) * width + (x + 1)]; // Top Right
                    neighborB = magBuffer[(y + 1) * width + (x - 1)]; // Bottom Left
                } else if (direction >= 67.5 && direction < 112.5) {
                    neighborA = magBuffer[(y - 1) * width + x]; // Top
                    neighborB = magBuffer[(y + 1) * width + x]; // Bottom
                } else if (direction >= 112.5 && direction < 157.5) {
                    neighborA = magBuffer[(y - 1) * width + (x - 1)]; // Top Left
                    neighborB = magBuffer[(y + 1) * width + (x + 1)]; // Bottom Right
                }
                
                if (mag >= neighborA && mag >= neighborB) {
                    angles[index] = static_cast<int>(angleBuffer[index] + 180) % 360;
                    int clampedMag = std::min(255, mag);
                    int edgeIndex = index * channels;
                    edgeImg.data[edgeIndex] = edgeImg.data[edgeIndex + 1] = edgeImg.data[edgeIndex + 2] = static_cast<uint8_t>(clampedMag);
                }
            }
        }
    }

    return edgeImg;
}