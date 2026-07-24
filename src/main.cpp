#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Image.h"
#include <cmath>
#include <fstream>
#include <array>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

std::vector<std::array<uint8_t, 3>> colors = {
    {30, 30, 46}, //Base
    {245, 194, 231}, // Pink
    {203, 166, 247},// Mauve
    {243, 139, 168}, // Red
    {249, 226, 175}, //Yellow
    {146, 226, 213}, //Teal
    {180, 190, 254}, //Lavender
    {245, 224, 220} //White
};

Image downsample(Image& img, int pixelSize);

std::vector<std::string> convertToASCII(Image& img, int pixelSize, bool onlyEdges);

extern uint8_t highestValue(uint8_t* data, int size, int channels);
extern uint8_t lowestValue(uint8_t* data, int size, int channels);

int sobelFilter(uint8_t* data, int width, int height, int channels, int x, int y);

void printToFile(const std::vector<std::string>& asciiArt, const std::string& filename);

std::vector<unsigned char> loadFont(const std::string& fontFilename);

void renderTextToImage(const std::vector<std::string>& asciiArt, const stbtt_fontinfo& font, int pixelSize, Image& img, int accentColors);

int main() {
    std::string inputFilename;
    std::string outputFilename = "../images/output_ascii.txt";
    std::string fontFilename = "../BigBlue_TerminalPlus.TTF";

    std::vector<unsigned char> fontBuffer = loadFont(fontFilename);
    stbtt_fontinfo font;
    stbtt_InitFont(&font, fontBuffer.data(), 0);

    int pixelSize = 8;
    int accentColor = 7;
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

    std::cout << "Choose accent color(1 - 7, default white):" << std::endl << " [1] - Pink\n [2] - Mauve\n [3] - Red\n [4] - Yellow\n [5] - Teal\n [6] - Lavender\n [7] - White" << std::endl;
    std::cin >> accentColor;
    if(accentColor > 7 || accentColor < 1) accentColor = 7;

    Image img(inputFilename.c_str());
    if (invertImage) {
        img.invert();
    }

    std::vector<std::string> asciiArt = convertToASCII(img, pixelSize, onlyEdges);
    printToFile(asciiArt, outputFilename);

    std::cout << "Rendering ASCII to image..." << std::endl;
    renderTextToImage(asciiArt, font, pixelSize, img, accentColor);

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
    //.',-:=+*o%&#@M
    const char* asciiChars[] = {" ", ".", "'", ",", "-", ":", ";", "=", "+", "*", "o", "%", "&", "#", "@", "M"};
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

std::vector<unsigned char> loadFont(const std::string& fontFilename) {
    std::ifstream file(fontFilename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open font file.\n";
        return {};
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> fontBuffer(size);
    if (!file.read(reinterpret_cast<char*>(fontBuffer.data()), size)) {
        std::cerr << "Failed to read font file.\n";
        return {};
    }
    return fontBuffer;
}

void renderTextToImage(const std::vector<std::string>& asciiArt, const stbtt_fontinfo& font, int pixelSize, Image& img, int accentColor) {
    float scale = stbtt_ScaleForPixelHeight(&font, pixelSize);
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    int baseline_y = std::round(ascent * scale);

    std::array<uint8_t, 3> accent = colors.at(accentColor);
    std::array<uint8_t, 3> base = colors.at(0);

    Image out_img(img.width, img.height, 3);
    
    // PRE-FILL ENTIRE CANVAS WITH BASE COLOR
    for (int i = 0; i < out_img.width * out_img.height; ++i) {
        out_img.data[i * 3]     = base[0];
        out_img.data[i * 3 + 1] = base[1];
        out_img.data[i * 3 + 2] = base[2];
    }

    for (size_t row = 0; row < asciiArt.size(); ++row) {
        for (size_t col = 0; col < asciiArt[row].size(); ++col) {
            
            char c = asciiArt[row][col];
            if (c == ' ') continue;

            int cell_x = col * pixelSize;
            int cell_y = row * pixelSize;

            int c_x1, c_y1, c_x2, c_y2;
            stbtt_GetCodepointBitmapBox(&font, c, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
            
            int char_w = c_x2 - c_x1;
            int char_h = c_y2 - c_y1;

            if (char_w <= 0 || char_h <= 0) continue; 

            std::vector<unsigned char> char_bitmap(char_w * char_h, 0);
            stbtt_MakeCodepointBitmap(&font, char_bitmap.data(), char_w, char_h, char_w, scale, scale, c);

            int draw_start_x = cell_x + c_x1;
            int draw_start_y = cell_y + baseline_y + c_y1;

            for (int cy = 0; cy < char_h; ++cy) {
                for (int cx = 0; cx < char_w; ++cx) {
                    
                    int out_x = draw_start_x + cx;
                    int out_y = draw_start_y + cy;

                    if (out_x >= 0 && out_x < img.width && out_y >= 0 && out_y < img.height) {
                        
                        unsigned char alpha = char_bitmap[cy * char_w + cx];
                        
                        // RESTORE ANTI-ALIASING BLENDING
                        if (alpha > 0) {
                            int out_idx = (out_y * img.width + out_x) * 3;
                            
                            out_img.data[out_idx]     = (accent[0] * alpha + base[0] * (255 - alpha)) / 255;
                            out_img.data[out_idx + 1] = (accent[1] * alpha + base[1] * (255 - alpha)) / 255;
                            out_img.data[out_idx + 2] = (accent[2] * alpha + base[2] * (255 - alpha)) / 255;
                        }
                    }
                }
            }
        }
    }

    out_img.write("../images/ascii_output.png");
}