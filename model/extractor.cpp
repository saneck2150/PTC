#ifndef _EXTRACTOR_MODEL_
#define _EXTRACTOR_MODEL_
#include "modellib.hpp"

class PTC::ExtractorModel 
{
private:
    const std::string fileName;
    std::vector<std::string> inputDataTokens;
    bool isValidFileExtension(const std::string& extension) const;
public:
    explicit ExtractorModel(const std::string& file) : fileName(file) {}
    ExtractorModel() : fileName("") {}
    void loadData();
    std::vector<std::string>& getInputDataTokens();  
};

void PTC::ExtractorModel::loadData() 
{
    if (fileName.empty()) 
    {
        throw std::runtime_error("No input file name provided.");
    }

    if (!std::filesystem::exists(fileName)) 
    {
        throw std::runtime_error("File does not exist: " + fileName);
    }

    if (!isValidFileExtension(INPUT_FORMAT)) 
    { 
        throw std::runtime_error("File format is incorrect or usupported: " + fileName + " | (supported formats: .txt)");
    }

    std::ifstream l_stream(fileName);
    if (!l_stream) 
    {
        throw std::runtime_error("Cannot open file: " + fileName);
    }

    if (l_stream.peek() == std::ifstream::traits_type::eof()) 
    {
        throw std::runtime_error("File is empty: " + fileName);
    }

    for (std::string token; l_stream >> token; ) 
    {
        inputDataTokens.push_back(token);
    }
}

bool PTC::ExtractorModel::isValidFileExtension(const std::string& extension) const 
{
    auto dotPos = fileName.rfind('.');
    if (dotPos == std::string::npos) 
    {
        return false;
    }
    return fileName.substr(dotPos) == extension;
}

std::vector<std::string>& PTC::ExtractorModel::getInputDataTokens()  
{
    return inputDataTokens;
}


#endif