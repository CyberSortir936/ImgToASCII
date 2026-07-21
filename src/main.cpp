#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Image.h"
#include <cmath>
#include <fstream>

Image downsample(Image& img, int pixelSize);

std::vector<std::string> convertToASCII(Image& img, int pixelSize, bool onlyEdges);

extern uint8_t highestValue(uint8_t* data, int size, int channels);
extern uint8_t lowestValue(uint8_t* data, int size, int channels);

int sobelFilter(uint8_t* data, int width, int height, int channels, int x, int y);

void printToFile(const std::vector<std::string>& asciiArt, const std::string& filename);

int main() {
    std::string inputFilename;
    std::string outputFilename = "../images/output_ascii.txt";
    int pixelSize = 8;
    bool invertImage = false; 
    int lowThreshold = 30;
    int highThreshold = 220;
    bool onlyEdges = false;

    std::cout << "Input filename: " << std::endl;
    std::cin >> inputFilename;
    std::cout << "Pixel size for downsampling (default 8): " << std::endl;
    std::string pixelSizeInput;
    std::cin >> pixelSizeInput;
    if (!pixelSizeInput.empty()) {
        pixelSize = std::stoi(pixelSizeInput);
    }


    std::cout << "Invert image? (y/n, default n): " << std::endl;
    std::string invertInput;
    std::cin >> invertInput;
    if (!invertInput.empty() && (invertInput == "y" || invertInput == "Y")) {
        invertImage = true;
    }

    std::cout << "Only show edges? (y/n, default n): " << std::endl;
    std::string onlyEdgesInput;
    std::cin >> onlyEdgesInput;
    if (!onlyEdgesInput.empty() && (onlyEdgesInput == "y" || onlyEdgesInput == "Y")) {
        onlyEdges = true;
    }

    Image img(inputFilename.c_str());
    if (invertImage) {
        img.invert();
    }

    /*Image downsampled = downsample(img, 16);
    downsampled.write("../images/output_downsampled.jpg");
    downsampled.maxContrast();
    downsampled.write("../images/output_downsampled_contrast.jpg");*/

    //downsampled.grayscale();
    //downsampled.write("../images/output_downsampled_grayscale.jpg");

    std::vector<std::string> asciiArt = convertToASCII(img, pixelSize, onlyEdges);
    printToFile(asciiArt, outputFilename);

    std::cout << "ASCII Art:" << std::endl;
    for (const auto& line : asciiArt) {
        std::cout << line << std::endl;
    }


    return 0;
}

Image downsample(Image& img, int pixelSize) {
    Image downsampled(img.width / pixelSize, img.height / pixelSize, img.channels);

    for (int y = 0; y < downsampled.height * pixelSize; y += pixelSize) {
        for (int x = 0; x < downsampled.width * pixelSize; x += pixelSize) {
            int r = 0, g = 0, b = 0;
            int count = 0;

            for (int j = 0; j < pixelSize && (y + j) < img.height; ++j) {
                for (int i = 0; i < pixelSize && (x + i) < img.width; ++i) {
                    int index = ((y + j) * img.width + (x + i)) * img.channels;
                    r += img.data[index];
                    g += img.data[index + 1];
                    b += img.data[index + 2];
                    count++;
                }
            }

            int downsampledIndex = ((y / pixelSize) * downsampled.width + (x / pixelSize)) * downsampled.channels;
            downsampled.data[downsampledIndex] = r / count;
            downsampled.data[downsampledIndex + 1] = g / count;
            downsampled.data[downsampledIndex + 2] = b / count;
        }
    }
    return downsampled;
}

std::vector<std::string> convertToASCII(Image& img, int pixelSize, bool onlyEdges) {
    // .:-=+*#% ■
    const char* asciiChars[] = {" ", ".", ":", "-", "=", "+", "*", "#", "%", "■"};
    std::vector<std::string> asciiArt;
    std::vector<int> brightnessValues;
    
    img.grayscale();

    Image preparedImg = downsample(img, pixelSize);
    std::vector<int> angles;

    Image edgeImg = preparedImg.sobelEdgeDetection(angles, 100);

    if (onlyEdges) {
        preparedImg = edgeImg;
    }

    edgeImg.write("../images/output_plus_edge.jpg");

    int maxVal = highestValue(preparedImg.data, preparedImg.size, preparedImg.channels);

    for (int i = 0; i < preparedImg.width * preparedImg.height * preparedImg.channels; i += preparedImg.channels) {
        int charIndex = (preparedImg.data[i] * (sizeof(asciiChars) / sizeof(asciiChars[0]))) / (maxVal + 1);
        
        brightnessValues.push_back(charIndex);
    }


    for (int y = 0; y < preparedImg.height; ++y) {
        std::string line;
        for (int x = 0; x < preparedImg.width; ++x) {
            int index = (y * preparedImg.width + x);
            
            // 1. Check the angle for THIS specific pixel
            int angle = angles[index];

            // 2. If it's an edge, draw the structural character
            if (angle != -1) {
                switch (angle / 45) {
                    case 0: case 4: line += "|"; break; 
                    case 1: case 5: line += "\\"; break; 
                    case 2: case 6: line += "_"; break; 
                    case 3: case 7: line += "/"; break; 
                }
            } 
            // 3. If it's not an edge, draw the brightness character
            else {
                int charIndex = static_cast<int>(brightnessValues[index]);
                line += asciiChars[charIndex];
            }
        }
        asciiArt.push_back(line);
    }

    //free(edgeData);
    return asciiArt;
}

uint8_t highestValue(uint8_t* data, int size, int channels) {
    uint8_t maxVal = 0;
    for (int i = 0; i < size; i += channels) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}
uint8_t lowestValue(uint8_t* data, int size, int channels) {
    uint8_t minVal = 255;
    for (int i = 0; i < size; i += channels) {
        if (data[i] < minVal) {
            minVal = data[i];
        }
    }
    return minVal;
}

void printToFile(const std::vector<std::string>& asciiArt, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& line : asciiArt) {
        outFile << line << std::endl;
    }

    outFile.close();
}