#pragma once
#include <msclr/marshal_cppstd.h>
#include "lsb.h"  
#include "cripto.h"

#include <string>

#include <msclr/marshal_cppstd.h>


using namespace System;
using namespace System::Windows::Forms;

namespace P {
    public ref class LsbWrapper
    {
    private:
        
    public:
        static String^ current_pub_key;
        static String^ current_priv_key;
        static std::string GetCurrentPublicKey() {
            std::string pubKey = get_current_pub_key();
            current_pub_key = msclr::interop::marshal_as<String^>(pubKey);
            return  pubKey;
        }

        static std::string GetCurrentPrivateKey() {
            std::string privKey = get_current_priv_key();
            current_priv_key = msclr::interop::marshal_as<String^>(privKey);
            return privKey;
        }


        static void ShowCurrentKeys()
        {
            try {
                // Obtener las claves actuales
                std::string pubKey = get_current_pub_key();
                std::string privKey = get_current_priv_key();

                // Mostrar en MessageBox
                MessageBox::Show("Clave Pública Actual:\n" +
                    msclr::interop::marshal_as<String^>(pubKey),
                    "Claves RSA");

                MessageBox::Show("Clave Privada Actual:\n" +
                    msclr::interop::marshal_as<String^>(privKey),
                    "Claves RSA");
            }
            catch (Exception^ e) {
                MessageBox::Show("Error mostrando claves: " + e->Message);
            }
        }





        static void GenerateAndShowKeys()
        {
            try {
                // Generar y mostrar claves RSA
                EVP_PKEY* pkey = generate_rsa_key();

                // Convertir claves a strings PEM
                std::string pubKey = evp_pubkey_to_string(pkey);
                std::string privKey = evp_pubkey_to_string(pkey); // Esto necesita ajuste para clave privada

                // Mostrar en MessageBox
                //MessageBox::Show("Clave Pública:\n" + msclr::interop::marshal_as<String^>(pubKey));
                //MessageBox::Show("Clave Privada:\n" + msclr::interop::marshal_as<String^>(privKey));
                
                EVP_PKEY_free(pkey);
            }
            catch (Exception^ e) {
                MessageBox::Show("Error generando claves: " + e->Message);
            }
        }





        static void HideFileInImage(String^ imagePath, String^ fileToHide, String^ outputImagePath)
        {
            try {
                // Primero generar claves (opcional)
                GenerateAndShowKeys();

                std::string imgPath = msclr::interop::marshal_as<std::string>(imagePath);
                std::string filePath = msclr::interop::marshal_as<std::string>(fileToHide);
                std::string outPath = msclr::interop::marshal_as<std::string>(outputImagePath);

                MessageBox::Show((imagePath + " /n hide " + fileToHide));
                hideFileInImage(imgPath.c_str(), filePath.c_str(), outPath.c_str(), "");

                MessageBox::Show("¡Archivo ocultado con éxito!");
            }
            catch (Exception^ e) {
                MessageBox::Show("Error: " + e->Message);
            }
        }








        static void HideFileHybrid(String^ imagePath,
            String^ fileToHide,
            String^ outputImagePath,
            String^ rsaPubKeyStr) {  // Ahora recibe string
            std::string img = msclr::interop::marshal_as<std::string>(imagePath);
            std::string file = msclr::interop::marshal_as<std::string>(fileToHide);
            std::string output = msclr::interop::marshal_as<std::string>(outputImagePath);
            std::string pubKey = msclr::interop::marshal_as<std::string>(rsaPubKeyStr);

            hideFileHybrid(img, file, output, pubKey);
        }

        static void ExtractFileHybrid(String^ imagePath,
            String^ outputFilePath,
            String^ rsaPrivKeyStr) {  // String de clave privada
            std::string img = msclr::interop::marshal_as<std::string>(imagePath);
            std::string output = msclr::interop::marshal_as<std::string>(outputFilePath);
            std::string privKey = msclr::interop::marshal_as<std::string>(rsaPrivKeyStr);
            MessageBox::Show("ddd");
            extractFileHybrid(img, output, privKey);
        }









    };
}