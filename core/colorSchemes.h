#ifndef COLORSCHEMES_H
#define COLORSCHEMES_H

#include <vector>
#include <string>

// Gruvbox, Catppuccin, Everforest, Kanagawa, Nord, Dracula

inline std::vector<std::vector<std::string>> colorSchemes{
    { // Gruvbox
    "#282828", // BG
    "#fb4934", //Red
    "#b8bb26", //Green
    "#fabd2f", //Yellow
    "#83a598", //Blue
    "#d3869b", //Purple
    "#ebdbb2" //White
    },

    { //Catppuccin
    "#1e1e2e", // BG
    "#f38ba8", // Red
    "#a6e3a1", // Green
    "#f9e2af", // Yellow
    "#89b4fa", // Blue
    "#cba6f7", // Mauve
    "#f5e0dc" // White
    },
    
    { // Everforest
    "#272E33", // BG
    "#E67E80", // Red
    "#A7C080", // Green
    "#DBBC7F", // Yellow
    "#7FBBB3", // Blue
    "#D699B6", // Purple
    "#D3C6AA" // White
    },

    { // Kanagawa
    "#16161D", // BG
    "#E82424", // Red
    "#76946A", // Green
    "#658594", // Blue
    "#FF9E3B", // Yellow
    "#957FB8", // Violet
    "#DCD7BA" //White
    }, 

    { // Nord
    "#2e3440", // BG
    "#bf616a", // Red
    "#a3be8c", // Green
    "#81a1c1", // Blue
    "#ebcb8b", // Yellow
    "#b48ead", // Purple
    "#eceff4" // White
    }, 

    { // Dracula
    "#282A36", // BG
    "#FF5555", // Red
    "#50FA7B", // Green
    "#6272A4", // Blue
    "#F1FA8C", // Yellow
    "#BD93F9", // Purple
    "#F8F8F2" //White
    }
};

/*
vector<std::string> Gruvbox{
    "#282828", // BG
    "#fb4934" //Red
    "#b8bb26" //Green
    "#fabd2f" //Yellow
    "#83a598" //Blue
    "#d3869b" //Purple
    "#ebdbb2" //White
};

vector<std::string> Catppuccin{
    "#1e1e2e" // BG
    "#f38ba8" // Red
    "#a6e3a1" // Green
    "#f9e2af" // Yellow
    "#89b4fa" // Blue
    "#cba6f7" // Mauve
    "#f5e0dc" // White
};

vector<std::string> Everforest{
    "#272E33" // BG
    "#E67E80" // Red
    "#A7C080" // Green
    "#DBBC7F" // Yellow
    "#7FBBB3" // Blue
    "#D699B6" // Purple
    "#D3C6AA" // White
};

vector<std::string> Kanagawa{
    "#16161D" // BG
    "#E82424" // Red
    "#76946A" // Green
    "#658594" // Blue
    "#FF9E3B" // Yellow
    "#957FB8" // Violet
    "#DCD7BA" //White
};

vector<std::string> Nord {
    "#2e3440" // BG
    "#bf616a" // Red
    "#a3be8c" // Green
    "#81a1c1" // Blue
    "#ebcb8b" // Yellow
    "#b48ead" // Purple
    "#eceff4" // White
};

vector<std::string> Dracula {
    "#282A36" // BG
    "#FF5555" // Red
    "#50FA7B" // Green
    "#6272A4" // Blue
    "#F1FA8C" // Yellow
    "#BD93F9" // Purple
    "#F8F8F2" //White
};
*/
#endif // COLORSCHEMES_H
