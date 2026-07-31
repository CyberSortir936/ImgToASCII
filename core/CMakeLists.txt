# core/CMakeLists.txt

# Create a static library named 'core'
add_library(core STATIC
    Image.cpp
    guiImageConverter.cpp
)

# Expose this directory so other modules can just #include "Image.h"
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})