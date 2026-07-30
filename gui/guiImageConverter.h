#include "colorSchemes.h"
#include "mainwindow.h"

struct RGBcolor{
    int r, g, b;
};

RGBcolor hexToRGB(std::string hex color);
RGBcolor returnColorFromScheme(QString scheme, int index);

