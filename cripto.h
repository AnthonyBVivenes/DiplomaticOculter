#pragma once
#include <openssl/evp.h>
#include <string>
#include <vector>

#define AES_KEY_SIZE 256
#define RSA_KEY_SIZE 2048
#define AES_BLOCK_SIZE 16

// Generación de claves
EVP_PKEY* generate_rsa_key();
std::string evp_pubkey_to_string(EVP_PKEY* pkey);
EVP_PKEY* string_to_evp_pubkey(const std::string& str);

// Cifrado/descifrado
std::vector<unsigned char> rsa_encrypt(EVP_PKEY* pkey, const unsigned char* data, size_t data_len);
std::vector<unsigned char> rsa_decrypt(EVP_PKEY* pkey, const unsigned char* data, size_t data_len);
std::vector<unsigned char> aes_encrypt(const unsigned char* key, const unsigned char* iv,
    const unsigned char* data, size_t data_len);
std::vector<unsigned char> aes_decrypt(const unsigned char* key, const unsigned char* iv,
    const unsigned char* data, size_t data_len);



EVP_PKEY* get_current_rsa_key();  // Obtener la clave actual
std::string get_current_pub_key(); // Obtener clave pública como string
std::string get_current_priv_key(); // Obtener clave privada como string