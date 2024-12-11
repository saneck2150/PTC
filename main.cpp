#include "model/rlecompressor.cpp"
#include "model/extractor.cpp"
#include "model/modellib.hpp"

//future cmake flags for compiler
bool NO_GUI = true;
bool TEST = false;

int main()
{
    if (NO_GUI)
    {
        std::cout << "Uploading File" << std::endl;
        PTC::ExtractorModel extrModel("test.txt");
        try
        {
            std::cout << "File status -> ";
            extrModel.loadData(); 
            std::cout << "OK" << std::endl;
            for (const auto& token : extrModel.getInputDataTokens())
            {
                std::cout << token << std::endl;
            }
        }
        catch (std::runtime_error& e)
        {
            std::cerr << "Error: " << e.what() << std::endl; 
            return 0;
        }

        std::cout << "Program is alive" << std::endl;

        PTC::RLECompressorModel comprModel;
        comprModel.rleCompressor(extrModel); 

        std::cout << "Compressed Data:" << std::endl;
        for (const auto& token : comprModel.getRLETokens())
        {
            std::cout << token << std::endl; 
        }
    }
    return 0;
}