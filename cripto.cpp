#include "cripto.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <vector>
#include <iostream>

#include <stdexcept>
#include <openssl/err.h>

#include <msclr/marshal_cppstd.h>
#include <Windows.h> // Para MessageBox


using namespace std;


using namespace System;
using namespace System::Windows::Forms;


#define AES_KEY_SIZE 256
#define RSA_KEY_SIZE 2048
#define BUFFER_SIZE 1024
#define OPENSSL_API_COMPAT 10100
#define OPENSSL_NO_DEPRECATED 1


#define AES_BLOCK_SIZE 16  // Tamaño de bloque AES (128 bits)
#define AES_KEY_SIZE 256   // Tamaño de clave AES (256 bits)
#define RSA_KEY_SIZE 2048  // Tamaño de clave RSA (2048 bits)
#define BUFFER_SIZE 1024 

// Genera par de claves RSA


void ShowMessage(const char* message) {
    MessageBox::Show(gcnew String(message));
}


static EVP_PKEY* current_rsa_key = nullptr;
static std::string current_pub_key_str;
static std::string current_priv_key_str;


EVP_PKEY* generate_rsa_key() {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        ShowMessage("Error al crear contexto RSA");
        return nullptr;
    }

    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        ShowMessage("Error al inicializar generación de clave RSA");
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEY_SIZE) <= 0) {
        ShowMessage("Error al establecer tamaño de clave RSA");
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        ShowMessage("Error al generar clave RSA");
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY_CTX_free(ctx);

    // Mostrar y almacenar las claves generadas
    BIO* bio_pub = BIO_new(BIO_s_mem());
    BIO* bio_priv = BIO_new(BIO_s_mem());

    PEM_write_bio_PUBKEY(bio_pub, pkey);
    PEM_write_bio_PrivateKey(bio_priv, pkey, NULL, NULL, 0, NULL, NULL);

    char* pub_key;
    long pub_len = BIO_get_mem_data(bio_pub, &pub_key);
    std::string pub_str(pub_key, pub_len);

    char* priv_key;
    long priv_len = BIO_get_mem_data(bio_priv, &priv_key);
    std::string priv_str(priv_key, priv_len);

    /* Mostrar en MessageBox
    MessageBox::Show("Clave Pública Generada:\n" +
        msclr::interop::marshal_as<String^>(pub_str),
        "Información de Claves");

    MessageBox::Show("Clave Privada Generada:\n" +
        msclr::interop::marshal_as<String^>(priv_str),
        "Información de Claves");

    */ 
    //Almacenar las claves para acceso posterior
    current_rsa_key = pkey;
    current_pub_key_str = pub_str;
    current_priv_key_str = priv_str;

    BIO_free(bio_pub);
    BIO_free(bio_priv);

    return pkey;
}

// Añade estas nuevas funciones
EVP_PKEY* get_current_rsa_key() {
    return current_rsa_key;
}

std::string get_current_pub_key() {
    return current_pub_key_str;
}

std::string get_current_priv_key() {
    return current_priv_key_str;
}


// Serializa clave pública a string
std::string evp_pubkey_to_string(EVP_PKEY* pkey) {
    if (!pkey) return "";

    BIO* bio = BIO_new(BIO_s_mem());
    if (!PEM_write_bio_PUBKEY(bio, pkey)) {
        BIO_free(bio);
        return "";
    }

    char* data;
    long len = BIO_get_mem_data(bio, &data);
    std::string result(data, len);
    BIO_free(bio);
    return result;
}

// Carga clave pública desde string
EVP_PKEY* string_to_evp_pubkey(const std::string& str) {
    BIO* bio = BIO_new_mem_buf(str.c_str(), str.length());
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);
    return pkey;
}

// Cifrado RSA
std::vector<unsigned char> rsa_encrypt(EVP_PKEY* pkey, const unsigned char* data, size_t data_len) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) return {};

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, data, data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    std::vector<unsigned char> result(outlen);
    if (EVP_PKEY_encrypt(ctx, result.data(), &outlen, data, data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    result.resize(outlen);
    EVP_PKEY_CTX_free(ctx);
    return result;
}

// Descifrado RSA
std::vector<unsigned char> rsa_decrypt(EVP_PKEY* pkey, const unsigned char* data, size_t data_len) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) return {};

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    size_t outlen;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen, data, data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    std::vector<unsigned char> result(outlen);
    if (EVP_PKEY_decrypt(ctx, result.data(), &outlen, data, data_len) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return {};
    }

    result.resize(outlen);
    EVP_PKEY_CTX_free(ctx);
    return result;
}




vector<unsigned char> aes_encrypt(const unsigned char* key, const unsigned char* iv,
    const unsigned char* data, size_t data_len) {

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw runtime_error("Error al crear contexto de cifrado");

    try {
        // Configurar cifrado AES-256-CBC con padding explícito
        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            throw runtime_error("Error al inicializar cifrado AES");
        }

        // Deshabilitar padding (lo manejaremos nosotros)
        EVP_CIPHER_CTX_set_padding(ctx, 0);

        // Calcular tamaño de buffer necesario (redondeado al bloque más cercano)
        size_t blocks = (data_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
        vector<unsigned char> ciphertext(blocks * AES_BLOCK_SIZE);

        int len;
        if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, data, data_len)) {
            throw runtime_error("Error durante el cifrado");
        }

        // Aplicar padding manual PKCS#7 si es necesario
        int pad_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
        if (pad_len < AES_BLOCK_SIZE) {
            unsigned char pad = static_cast<unsigned char>(pad_len);
            vector<unsigned char> padding(pad_len, pad);
            if (1 != EVP_EncryptUpdate(ctx, ciphertext.data() + len, &len,
                padding.data(), pad_len)) {
                throw runtime_error("Error aplicando padding");
            }
        }

        EVP_CIPHER_CTX_free(ctx);
        return ciphertext;
    }
    catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
}





vector<unsigned char> aes_decryp88988ht(const unsigned char* key, const unsigned char* iv,
    const unsigned char* data, size_t data_len) {

    // 1. Inicializar OpenSSL (si no se ha hecho)
    static bool openssl_initialized = false;
    if (!openssl_initialized) {
        OpenSSL_add_all_algorithms();
        ERR_load_crypto_strings();
        openssl_initialized = true;
    }

    // 2. Validar parámetros de entrada
    if (!key || !iv || !data || data_len == 0) {
        throw runtime_error("Parámetros de descifrado inválidos");
    }

    // 3. Crear y configurar contexto de descifrado
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw runtime_error("Error al crear contexto de descifrado");
    }

    try {
        // 4. Inicializar descifrado AES-256-CBC
        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            throw runtime_error("Fallo al inicializar descifrado AES");
        }

        // 5. Preparar buffer para datos descifrados
        vector<unsigned char> plaintext(data_len + AES_BLOCK_SIZE);
        int len;
        int plaintext_len = 0;

        // 6. Descifrar datos
        if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, data, data_len)) {
            throw runtime_error("Error durante el descifrado");
        }
        plaintext_len = len;

        // 7. Finalizar descifrado
        if (1 != EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len)) {
            // Obtener error detallado de OpenSSL
            char err_buf[256];
            ERR_error_string_n(ERR_get_error(), err_buf, sizeof(err_buf));
            throw runtime_error(string("Error final en descifrado: ") + err_buf);
        }
        plaintext_len += len;

        // 8. Ajustar tamaño del resultado
        plaintext.resize(plaintext_len);

        // 9. Liberar recursos
        EVP_CIPHER_CTX_free(ctx);

        return plaintext;
    }
    catch (...) {
        // Asegurarse de liberar recursos en caso de error
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
}



vector<unsigned char> aes_decrypt(const unsigned char* key, const unsigned char* iv,
    const unsigned char* data, size_t data_len) {

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw runtime_error("Error al crear contexto de descifrado");

    try {
        // Configurar descifrado AES-256-CBC con padding explícito
        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            throw runtime_error("Error al inicializar descifrado AES");
        }

        // Deshabilitar padding (lo manejaremos nosotros)
        EVP_CIPHER_CTX_set_padding(ctx, 0);

        vector<unsigned char> plaintext(data_len);
        int len;

        if (1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, data, data_len)) {
            throw runtime_error("Error durante el descifrado");
        }

        // Verificar y remover padding PKCS#7 manualmente
        if (len > 0) {
            unsigned char pad_value = plaintext[len - 1];
            if (pad_value <= AES_BLOCK_SIZE) {
                len -= pad_value; // Remover padding
            }
            plaintext.resize(len);
        }

        EVP_CIPHER_CTX_free(ctx);
        return plaintext;
    }
    catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
}

