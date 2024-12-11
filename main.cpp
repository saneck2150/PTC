#include "model/compressor.cpp"
#include "model/extractor.cpp"
#include "model/modellib.hpp"

int main ()
{
    PTC::ExtractorModel model ("test.txt");
    
    try
    {
        model.loadData();
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Program is alive" << std::endl;
}