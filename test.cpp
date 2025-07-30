#include <iostream>
#include <fstream>
#include <vector>
#include "cripto.h"
#include "lsb.h"
#include <openssl/rand.h>  // Necesario para RAND_bytes

using namespace std;

// Función para leer un archivo en un vector de bytes
vector<unsigned char> leerArchivo(const string& nombre) {
    ifstream file(nombre, ios::binary);
    return vector<unsigned char>((istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>());
}

// Función para guardar datos en un archivo
void guardarArchivo(const string& nombre, const vector<unsigned char>& datos) {
    ofstream file(nombre, ios::binary);
    file.write(reinterpret_cast<const char*>(datos.data()), datos.size());
}

int main() {
    cout << "=== PRUEBA COMPLETA DE FUNCIONALIDAD CRIPTOGRAFICA ===" << endl;

    // 1. Generación de claves RSA
    cout << "\n1. Generando claves RSA..." << endl;
    EVP_PKEY* pkey = generate_rsa_key();
    if (!pkey) {
        cerr << "Error al generar claves RSA" << endl;
        return 1;
    }

    string pubKey = get_current_pub_key();
    string privKey = get_current_priv_key();
    cout << "Claves generadas correctamente." << endl;

    // 2. Prueba de cifrado/descifrado RSA
    cout << "\n2. Probando cifrado RSA..." << endl;
    string mensajeOriginal = "123456789";
    vector<unsigned char> datosOriginales(mensajeOriginal.begin(), mensajeOriginal.end());

    vector<unsigned char> cifradoRSA = rsa_encrypt(pkey, datosOriginales.data(), datosOriginales.size());
    cout << "Mensaje cifrado con RSA (" << cifradoRSA.size() << " bytes)" << endl;

    vector<unsigned char> descifradoRSA = rsa_decrypt(pkey, cifradoRSA.data(), cifradoRSA.size());
    string resultadoRSA(descifradoRSA.begin(), descifradoRSA.end());
    cout << "Mensaje descifrado: " << resultadoRSA << endl;

    // 3. Prueba de cifrado/descifrado AES
    cout << "\n3. Probando cifrado AES..." << endl;
    unsigned char claveAES[32]; // Clave AES de 256 bits (32 bytes)
    unsigned char iv[16];       // IV de 16 bytes

    // Generar valores aleatorios para clave e IV
    if (RAND_bytes(claveAES, sizeof(claveAES)) != 1) {
        cerr << "Error generando clave AES aleatoria" << endl;
        return 1;
    }

    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        cerr << "Error generando IV aleatorio" << endl;
        return 1;
    }

    vector<unsigned char> cifradoAES = aes_encrypt(claveAES, iv, datosOriginales.data(), datosOriginales.size());
    cout << "Mensaje cifrado con AES (" << cifradoAES.size() << " bytes)" << endl;

    vector<unsigned char> descifradoAES = aes_decrypt(claveAES, iv, cifradoAES.data(), cifradoAES.size());
    string resultadoAES(descifradoAES.begin(), descifradoAES.end());
    cout << "Mensaje descifrado: " << resultadoAES << endl;

    // 4. Prueba de cifrado híbrido (RSA + AES)
    cout << "\n4. Probando cifrado hibrido..." << endl;

    // Cifrar clave AES con RSA
    vector<unsigned char> claveAESCifrada = rsa_encrypt(pkey, claveAES, sizeof(claveAES));

    // Descifrar clave AES
    vector<unsigned char> claveAESDescifrada = rsa_decrypt(pkey, claveAESCifrada.data(), claveAESCifrada.size());

    if (memcmp(claveAES, claveAESDescifrada.data(), sizeof(claveAES)) == 0) {
        cout << "Cifrado hibrido funcionando correctamente" << endl;
    }
    else {
        cerr << "Error en cifrado hibrido" << endl;
    }

    // 5. Prueba de ocultamiento en imagen (LSB)
    cout << "\n5. Probando ocultamiento en imagen..." << endl;
    try {
        // Crear archivo de prueba
        //ofstream prueba("prueba.txt");
        //prueba << "1902";
        //prueba.close();

        // Ocultar archivo
        hideFileHybrid("imagen.bmp", "prueba.txt", "imagen_con_mensaje.bmp", pubKey);
        cout << "Archivo oculto en imagen correctamente" << endl;

        // Extraer archivo
        extractFileHybrid("imagen_con_mensaje.bmp", "mensaje_extraido.txt", privKey);
        cout << "Archivo extraido de imagen" << endl;

        // Mostrar contenido extraído
        ifstream extraido("mensaje_extraido.txt");
        string linea;
        cout << "Contenido extraido: ";
        while (getline(extraido, linea)) {
            cout << linea << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error en ocultamiento LSB: " << e.what() << endl;
    }

    // Liberar recursos
    EVP_PKEY_free(pkey);
    cout << "\n=== PRUEBA COMPLETADA ===" << endl;
    return 0;
}