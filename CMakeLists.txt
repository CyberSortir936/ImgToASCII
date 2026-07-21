# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(AsciiImageConverter)

# Enforce C++17 standard (good practice for modern C++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the executable and tell CMake which source files to compile
add_executable(main 
    src/main.cpp 
    src/Image.cpp
)

# Tell the compiler where to find your header files (.h)
target_include_directories(main PRIVATE src)
target_compile_options(main PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
target_link_options(main PRIVATE -fsanitize=address)