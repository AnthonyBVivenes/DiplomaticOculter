#pragma once
#include <string>

// Dec función extern 
extern "C" {
    void hideFileInImage(const std::string& imagePath,
        const std::string& fileToHide,
        const std::string& outputImagePath);
}