#include"libptc.hpp"

#ifndef _CODER_MODEL_
#define _CODER_MODEL_

class ExtractorModel {
private:
    const std::string fileName;
    std::vector<std::string> inputDataTokens;
    bool isValidFileExtension(const std::string& extension) const;

public:
    explicit ExtractorModel(const std::string& file) : fileName(file) {}
    void loadData();
};

void ExtractorModel::loadData() {
    if (fileName.empty()) {
        throw std::runtime_error("No input file name provided.");
    }

    if (!std::filesystem::exists(fileName)) {
        throw std::runtime_error("File does not exist: " + fileName);
    }

    if (!isValidFileExtension(INPUT_FORMAT)) { 
        throw std::runtime_error("File format is incorrect: " + fileName);
    }

    std::ifstream l_stream(fileName);
    if (!l_stream) {
        throw std::runtime_error("Cannot open file: " + fileName);
    }

    for (std::string token; l_stream >> token; ) {
        inputDataTokens.push_back(token);
    }
}

bool ExtractorModel::isValidFileExtension(const std::string& extension) const {
    auto dotPos = fileName.rfind('.');
    if (dotPos == std::string::npos) {
        return false;
    }
    return fileName.substr(dotPos) == extension;
}

#endif