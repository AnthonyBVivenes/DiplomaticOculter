#pragma once
#include <msclr/marshal_cppstd.h>

#include "lsb.h"  
using namespace System;
using namespace System::Windows::Forms;

namespace P {
    public ref class LsbWrapper
    {
    public:
        static void HideFileInImage(String^ imagePath, String^ fileToHide, String^ outputImagePath)
        {
            try {
                
                std::string imgPath = msclr::interop::marshal_as<std::string>(imagePath);
                std::string filePath = msclr::interop::marshal_as<std::string>(fileToHide);
                std::string outPath = msclr::interop::marshal_as<std::string>(outputImagePath);

                
                hideFileInImage(imgPath, filePath, outPath);

                MessageBox::Show("¡Archivo ocultado con éxito!");
            }
            catch (Exception^ e) {
                MessageBox::Show("Error: " + e->Message);
            }
        }
    };
}