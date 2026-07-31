#pragma once

#include "colorSchemes.h"
// #include "mainwindow.h"

#include "Image.h"
#include "stb_truetype.h"

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

struct RGB{
    int r, g, b;
};

RGB hexToRGB(std::string hexColor);
RGB returnColorFromScheme(int scheme, int index);

void renderTextToImageGUI(const std::vector<std::string>& asciiArt, const stbtt_fontinfo& font, int pixelSize, Image& img, RGB bgColor, RGB accentColor, std::string outputPath);

Image downsample(Image& img, int pixelSize);

std::vector<std::string> convertToASCII(Image& img, int pixelSize, bool onlyEdges);

uint8_t highestValue(uint8_t* data, int size, int channels);
uint8_t lowestValue(uint8_t* data, int size, int channels);

int sobelFilter(uint8_t* data, int width, int height, int channels, int x, int y);

void printToFile(const std::vector<std::string>& asciiArt, const std::string& filename);

std::vector<unsigned char> loadFont(const std::string& fontFilename);