#include "lsb.h"        
#include <fstream>
#include <vector>
#include <bitset>

#include <openssl/rand.h>    // Para RAND_bytes
#include <openssl/evp.h>     // Para EVP_PKEY
#include <openssl/pem.h>     // Para PEM_read_bio_*
#include <openssl/rsa.h>     // Para funciones RSA

#include <msclr/marshal_cppstd.h>

#include "cripto.h"

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

#include <iostream>




void hideFileInImage(const string imagePath,
    const string fileToHide,
    const string outputImagePath,
    const string password) {

    // Mostrar la contraseña que se está usando
    MessageBox::Show("Contraseña utilizada: " + msclr::interop::marshal_as<String^>(password),
        "Información de Cifrado");

    // Mostrar los primeros bytes de la clave derivada (en tu caso usas password.data() directamente)
    String^ keyInfo = "Clave AES derivada (primeros 16 bytes): ";
    for (int i = 0; i < 16 && i < password.size(); i++) {
        keyInfo += password[i].ToString("X2") + " ";
    }
    MessageBox::Show(keyInfo, "Información de Cifrado");

    // Resto del código original...
    ifstream imageFile(imagePath, ios::binary);
    if (!imageFile) MessageBox::Show("No se pudo abrir la imagen");

    ifstream secretFile(fileToHide, ios::binary);
    if (!secretFile) MessageBox::Show("No se pudo abrir el archivo secreto");

    vector<char> secretData((istreambuf_iterator<char>(secretFile)),
        (istreambuf_iterator<char>()));

    // Mostrar información sobre los datos a cifrar
    MessageBox::Show("Tamaño del archivo a ocultar: " + secretData.size().ToString() + " bytes",
        "Información de Datos");

    // 1. Cifrar los datos con AES-256
    vector<unsigned char> encryptedData = aes_encrypt(
        reinterpret_cast<const unsigned char*>(password.data()),
        nullptr,  // IV
        reinterpret_cast<const unsigned char*>(secretData.data()),
        secretData.size()
    );

    // Mostrar información sobre los datos cifrados
    MessageBox::Show("Tamaño después de cifrado: " + encryptedData.size().ToString() + " bytes",
        "Información de Cifrado");

    // Resto del código original...
}



void extractFileFromImage(const string& imagePath,
    const string& outputFilePath,
    const string& password) {  // Contraseña para AES
    // Leer la imagen
    ifstream imageFile(imagePath, ios::binary);
    if (!imageFile) throw runtime_error("No se pudo abrir la imagen");

    vector<char> imageData((istreambuf_iterator<char>(imageFile)),
        (istreambuf_iterator<char>()));

    // Extraer bytes ocultos (LSB)
    vector<unsigned char> encryptedData;
    size_t imageIndex = 54;  // Saltar encabezado BMP
    char currentByte = 0;
    int bitCount = 0;

    // Extraer hasta el final de la imagen (o hasta un marcador de fin)
    while (imageIndex < imageData.size()) {
        bool bit = imageData[imageIndex] & 1;
        currentByte = (currentByte << 1) | bit;
        bitCount++;
        imageIndex++;

        if (bitCount == 8) {
            encryptedData.push_back(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }

    // 2. Descifrar los datos con AES-256 (usando tu función de cripto.h)
    vector<unsigned char> decryptedData = aes_decrypt(
        reinterpret_cast<const unsigned char*>(password.data()),
        nullptr,  // IV (debe ser el mismo usado en cifrado)
        encryptedData.data(),
        encryptedData.size()
    );

    // Guardar el archivo descifrado
    ofstream outputFile(outputFilePath, ios::binary);
    if (!outputFile) throw runtime_error("No se pudo guardar el archivo extraído");
    outputFile.write(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size());
}













void hideFileHybrid(const string& imagePath,
    const string& fileToHide,
    const string& outputImagePath,
    const string& rsaPubKeyStr) {
    try {
        // 1. Generar clave AES y IV aleatorios
        unsigned char aes_key[32];
        unsigned char iv[16];
        if (RAND_bytes(aes_key, sizeof(aes_key)) != 1 || RAND_bytes(iv, sizeof(iv)) != 1) {
            throw runtime_error("Error generando clave/IV aleatorios");
        }

        // 2. Cargar clave pública RSA
        BIO* bio_pub = BIO_new_mem_buf(rsaPubKeyStr.data(), rsaPubKeyStr.size());
        if (!bio_pub) throw runtime_error("Error al crear buffer de memoria");

        EVP_PKEY* pubkey = PEM_read_bio_PUBKEY(bio_pub, NULL, NULL, NULL);
        BIO_free(bio_pub);
        if (!pubkey) throw runtime_error("Clave pública RSA inválida");

        // 3. Cifrar clave AES con RSA
        vector<unsigned char> encryptedKey = rsa_encrypt(pubkey, aes_key, sizeof(aes_key));
        EVP_PKEY_free(pubkey);

        // 4. Leer archivo a ocultar
        ifstream secretFile(fileToHide, ios::binary);
        if (!secretFile) throw runtime_error("Error al abrir archivo a ocultar");

        vector<unsigned char> secretData((istreambuf_iterator<char>(secretFile)),
            istreambuf_iterator<char>());

        // 5. Cifrar datos con AES
        vector<unsigned char> encryptedData = aes_encrypt(aes_key, iv,
            secretData.data(), secretData.size());

        // 6. Preparar metadatos para ocultar
        vector<unsigned char> payload;

        // Marca mágica "STEG" (4 bytes)
        const uint32_t MAGIC_NUMBER = 0x53544547;
        payload.insert(payload.end(), (unsigned char*)&MAGIC_NUMBER,
            (unsigned char*)&MAGIC_NUMBER + sizeof(MAGIC_NUMBER));

        // Tamaño de clave cifrada (4 bytes)
        uint32_t key_size = encryptedKey.size();
        payload.insert(payload.end(), (unsigned char*)&key_size,
            (unsigned char*)&key_size + sizeof(key_size));

        // Clave cifrada
        payload.insert(payload.end(), encryptedKey.begin(), encryptedKey.end());

        // IV (16 bytes)
        payload.insert(payload.end(), iv, iv + sizeof(iv));

        // Tamaño de datos originales (4 bytes)
        uint32_t data_size = secretData.size();
        payload.insert(payload.end(), (unsigned char*)&data_size,
            (unsigned char*)&data_size + sizeof(data_size));

        // Datos cifrados
        payload.insert(payload.end(), encryptedData.begin(), encryptedData.end());

        // 7. Verificar capacidad de la imagen
        ifstream imageFile(imagePath, ios::binary);
        if (!imageFile) throw runtime_error("Error al abrir imagen");

        vector<char> imageData((istreambuf_iterator<char>(imageFile)),
            istreambuf_iterator<char>());

        // Necesitamos 8 bits por byte de payload + 54 bytes de header BMP
        size_t requiredBits = payload.size() * 8;
        size_t availableBits = imageData.size() - 54; // Restar header BMP

        if (requiredBits > availableBits) {
            throw runtime_error("Imagen demasiado pequeña para los datos. Se necesitan " +
                to_string(requiredBits / 8) + " bytes, disponibles " +
                to_string(availableBits / 8));
        }

        // 8. Ocultar datos en LSBs
        size_t imageIndex = 54; // Saltar header BMP
        for (size_t i = 0; i < payload.size(); ++i) {
            unsigned char secretByte = payload[i];
            for (int j = 7; j >= 0; --j) {
                bool bit = (secretByte >> j) & 1;
                imageData[imageIndex] = (imageData[imageIndex] & 0xFE) | bit;
                imageIndex++;
                if (imageIndex >= imageData.size()) break;
            }
        }

        // 9. Guardar imagen modificada
        ofstream outputImage(outputImagePath, ios::binary);
        if (!outputImage) throw runtime_error("Error al crear imagen de salida");
        outputImage.write(imageData.data(), imageData.size());

        cout << "Archivo ocultado correctamente en " << outputImagePath << endl;
    }
    catch (const exception& e) {
        cerr << "ERROR en hideFileHybrid: " << e.what() << endl;
        throw;
    }
}








void extractFileHybrid(const string& imagePath,
    const string& outputFilePath,
    const string& rsaPrivKeyStr) {
    try {
        // 1. Extraer payload de la imagen
        ifstream imageFile(imagePath, ios::binary);
        if (!imageFile) throw runtime_error("Error al abrir imagen");

        vector<char> imageData((istreambuf_iterator<char>(imageFile)),
            istreambuf_iterator<char>());

        vector<unsigned char> payload;
        size_t imageIndex = 54; // Saltar header BMP
        unsigned char currentByte = 0;
        int bitCount = 0;

        // Leer hasta encontrar el marcador de fin o fin de imagen
        while (imageIndex < imageData.size()) {
            bool bit = imageData[imageIndex] & 1;
            currentByte = (currentByte << 1) | bit;
            bitCount++;
            imageIndex++;

            if (bitCount == 8) {
                payload.push_back(currentByte);
                currentByte = 0;
                bitCount = 0;
            }
        }

        // 2. Parsear metadatos
        size_t pos = 0;

        // Verificar marca mágica "STEG" (4 bytes)
        if (payload.size() < 4) throw runtime_error("Datos insuficientes para marca STEG");
        uint32_t magic_number;
        memcpy(&magic_number, payload.data() + pos, sizeof(magic_number));
        pos += sizeof(magic_number);

        if (magic_number != 0x53544547) { // "STEG"
            throw runtime_error("Formato de datos inválido (falta marca STEG)");
        }

        // Leer tamaño de clave cifrada (4 bytes)
        if (pos + 4 > payload.size()) throw runtime_error("Datos corruptos: tamaño de clave faltante");
        uint32_t key_size;
        memcpy(&key_size, payload.data() + pos, sizeof(key_size));
        pos += sizeof(key_size);

        // Leer clave cifrada
        if (pos + key_size > payload.size()) throw runtime_error("Datos corruptos: clave cifrada faltante");
        vector<unsigned char> encryptedKey(payload.begin() + pos, payload.begin() + pos + key_size);
        pos += key_size;

        // Leer IV (16 bytes)
        if (pos + 16 > payload.size()) throw runtime_error("Datos corruptos: IV faltante");
        unsigned char iv[16];
        memcpy(iv, payload.data() + pos, sizeof(iv));
        pos += sizeof(iv);

        // Leer tamaño de datos originales (4 bytes)
        if (pos + 4 > payload.size()) throw runtime_error("Datos corruptos: tamaño de datos faltante");
        uint32_t original_size;
        memcpy(&original_size, payload.data() + pos, sizeof(original_size));
        pos += sizeof(original_size);

        // Leer datos cifrados
        vector<unsigned char> encryptedData(payload.begin() + pos, payload.end());

        // 3. Cargar clave privada RSA
        BIO* bio_priv = BIO_new_mem_buf(rsaPrivKeyStr.data(), rsaPrivKeyStr.size());
        if (!bio_priv) throw runtime_error("Error al crear buffer de memoria");

        EVP_PKEY* privkey = PEM_read_bio_PrivateKey(bio_priv, NULL, NULL, NULL);
        BIO_free(bio_priv);
        if (!privkey) throw runtime_error("Clave privada RSA inválida");

        // 4. Descifrar clave AES con RSA
        vector<unsigned char> decryptedKey = rsa_decrypt(privkey, encryptedKey.data(), encryptedKey.size());
        EVP_PKEY_free(privkey);

        if (decryptedKey.size() != 32) { // 256 bits = 32 bytes
            throw runtime_error("Tamaño de clave AES incorrecto después de descifrar");
        }

        // 5. Descifrar datos con AES
        vector<unsigned char> decryptedData = aes_decrypt(decryptedKey.data(), iv,
            encryptedData.data(), encryptedData.size());

        // Verificar tamaño de datos descifrados
        if (decryptedData.size() < original_size) {
            throw runtime_error("Datos descifrados más pequeños que el tamaño original");
        }

        // 6. Guardar archivo descifrado (solo los bytes originales)
        ofstream outputFile(outputFilePath, ios::binary);
        if (!outputFile) throw runtime_error("Error al crear archivo de salida");
        outputFile.write(reinterpret_cast<const char*>(decryptedData.data()), original_size);

        cout << "Extracción completada correctamente en " << outputFilePath << endl;
    }
    catch (const exception& e) {
        cerr << "ERROR en extractFileHybrid: " << e.what() << endl;
        throw;
    }
}





