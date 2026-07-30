cmake_minimum_required(VERSION 3.16)
project(UnifiedApp VERSION 1.0)

# Global settings, C++ standard, etc.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(cli)
add_subdirectory(gui)
add_subdirectory(core)