#include "model/compressor.cpp"
#include "model/extractor.cpp"
#include "model/modellib.hpp"

//future cmake flags for compiler
bool NO_GUI = true;
bool TEST = false;

int main ()
{
    if (NO_GUI)
    {
        std::cout << "File Uploading" << std::endl;
        PTC::ExtractorModel model ("test.txt");
        try
        {
            std::cout << "File status -> ";
            model.loadData();
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "OK" << std::endl;
        std::cout << "Program is alive" << std::endl;
    }
    
}