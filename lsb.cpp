#include "lsb.h"        
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

void hideFileInImage(const string& imagePath,
    const string& fileToHide,
    const string& outputImagePath)
{
    

    ifstream imageFile(imagePath, ios::binary);
    if (!imageFile) return;

    ifstream secretFile(fileToHide, ios::binary);
    if (!secretFile) return;

    secretFile.seekg(0, ios::end);
    size_t fileSize = secretFile.tellg();
    secretFile.seekg(0, ios::beg);

    imageFile.seekg(0, ios::end);
    size_t imageSize = imageFile.tellg();
    imageFile.seekg(0, ios::beg);

    if (fileSize > (imageSize - 54) / 8) return;

    vector<char> imageData((istreambuf_iterator<char>(imageFile)),
        (istreambuf_iterator<char>()));
    vector<char> secretData((istreambuf_iterator<char>(secretFile)),
        (istreambuf_iterator<char>()));

    size_t imageIndex = 54;
    for (size_t i = 0; i < secretData.size(); ++i) {
        char secretByte = secretData[i];
        for (int j = 7; j >= 0; --j) {
            bool secretBit = (secretByte >> j) & 1;
            imageData[imageIndex] = (imageData[imageIndex] & 0xFE) | secretBit;
            imageIndex++;
        }
    }

    ofstream outputImage(outputImagePath, ios::binary);
    if (!outputImage) return;
    outputImage.write(imageData.data(), imageData.size());
}



void extractFileFromImage(const string& imagePath, const string& outputFilePath, size_t hiddenFileSize)
{
    // Abrir la imagen que contiene el archivo oculto
    ifstream imageFile(imagePath, ios::binary);
    if (!imageFile) {
        throw runtime_error("No se pudo abrir la imagen de entrada");
    }

    // Verificar el tamaño de la imagen
    imageFile.seekg(0, ios::end);
    size_t imageSize = imageFile.tellg();
    imageFile.seekg(0, ios::beg);

    // Leer los datos de la imagen
    vector<char> imageData((istreambuf_iterator<char>(imageFile)),
        (istreambuf_iterator<char>()));

    // Preparar el buffer para el archivo oculto
    vector<char> hiddenData;
    hiddenData.reserve(hiddenFileSize);

    // Extraer los bits menos significativos
    size_t imageIndex = 54; // Saltar el encabezado BMP (asumiendo formato BMP)
    char currentByte = 0;
    int bitCount = 0;

    for (size_t i = 0; i < hiddenFileSize * 8; ++i) {
        // Obtener el bit menos significativo
        bool bit = imageData[imageIndex] & 1;

        // Construir el byte
        currentByte = (currentByte << 1) | bit;
        bitCount++;

        // Cuando tenemos un byte completo, guardarlo
        if (bitCount == 8) {
            hiddenData.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }

        imageIndex++;
    }

    // Escribir el archivo extraído
    ofstream outputFile(outputFilePath, ios::binary);
    if (!outputFile) {
        throw runtime_error("No se pudo crear el archivo de salida");
    }

    outputFile.write(hiddenData.data(), hiddenData.size());
}
