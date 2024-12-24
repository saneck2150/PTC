#include "model/extractor.cpp"
#include "model/modellib.hpp"
#include "model/huffmancompressor.cpp"

//future cmake flags for compiler
bool NO_GUI = true;
bool TEST = false;

int main()
{
    if (1)
    {
        std::cout << "Uploading File" << std::endl;
        PTC::ExtractorModel extrModel("test.txt");
        try
        {
            std::cout << "File status -> ";
            int symbNumb = 0;
            extrModel.loadData(); 
            std::cout << "OK" << std::endl;
            for (const auto& token : extrModel.getInputDataTokens())
            {
                symbNumb += token.size();
            }
            std::cout << "Symbols to compress -> " << symbNumb << std::endl;
            std::cout << std::endl;
            HuffmanCompressor compressor;
            std::string compressed = compressor.compress (extrModel.getInputDataTokens());
            std::cout << "Compressed text: " << compressed << std::endl;
        }
        catch (std::runtime_error& e)
        {
            std::cerr << "Error: " << e.what() << std::endl; 
            return 0;
        }

        std::cout << "Program is alive" << std::endl;
    }

    
    return 0;
}