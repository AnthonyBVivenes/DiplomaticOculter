#pragma once
#include <string>
#include <string.h>




// Declaraciones para compatibilidad C
#ifdef __cplusplus
extern "C" {
#endif

    // Oculta un archivo en una imagen con cifrado AES-256
    void hideFileInImage(const std::string imagePath,
        const std::string fileToHide,
        const std::string outputImagePath,
        const std::string password);

    // Extrae un archivo de una imagen con descifrado AES-256
    void extractFileFromImage(const char* imagePath,
        const char* outputFilePath,
        const char* password);


    void hideFileHybrid(const std::string& imagePath,
        const std::string& fileToHide,
        const std::string& outputImagePath,
        const std::string& rsaPubKeyPath);

    void extractFileHybrid(const std::string& imagePath,
        const std::string& outputFilePath,
        const std::string& rsaPrivKeyPath);


#ifdef __cplusplus
} // extern "C"
#endif