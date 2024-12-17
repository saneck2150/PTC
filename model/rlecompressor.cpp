#include "extractor.cpp"

#ifndef _COMPRESSOR_MODEL_
#define _COMPRESSOR_MODEL_

class PTC::RLECompressorModel : protected PTC::ExtractorModel
{
private:
    std::vector<std::string> rleCompressedTokens;
    void compressVectorParallel (const std::vector<std::string>& input, int numThreads);
    static void compressVector(const std::vector<std::string>& input, std::vector<std::string>& result, int start, int end);
    static std::string rleCompress(const std::string& str); 
public:
    void rleCompressor (PTC::ExtractorModel& tokenisedText);
    std::vector<std::string>& getRLETokens ();
    RLECompressorModel() {};
};

void PTC::RLECompressorModel::rleCompressor(PTC::ExtractorModel& tokenisedText)
{
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 1;
    std::cout << std::to_string(numThreads) + " thread's are used" << std::endl;
    compressVectorParallel(tokenisedText.getInputDataTokens(), numThreads);
}

void PTC::RLECompressorModel::compressVectorParallel(const std::vector<std::string>& input, int numThreads)
{
    int n = input.size();
    rleCompressedTokens.resize(n); 
    std::vector<std::thread> threads;

    int blockSize = (n + numThreads - 1) / numThreads;
    for (int t = 0; t < numThreads; ++t) 
    {
        int start = t * blockSize;
        int end = std::min(start + blockSize, n);
        threads.emplace_back([this, &input, start, end]() {
            compressVector(input, rleCompressedTokens, start, end);
        });
    }

    for (auto& thread : threads) 
    {
        if (thread.joinable()) 
        {
            thread.join();
        }
    }
}
void PTC::RLECompressorModel::compressVector(const std::vector<std::string>& input, std::vector<std::string>& result, int start, int end)
{
    for (int i = start; i < end; ++i) 
    {
        result[i] = rleCompress(input[i]);
    }
}

std::string PTC::RLECompressorModel::rleCompress(const std::string& str)
{
    if (str.empty()) return "";
    
    std::string compressed;
    compressed.reserve(str.size());
    
    int n = str.size();
    for (int i = 0; i < n; )
    {
        char currentChar = str[i];
        int count = 1;
        while (i + count < n && str[i + count] == currentChar)
        {
            ++count;
        }

        std::string escapedChar;
        if (currentChar == ':' || currentChar == '|' || currentChar == '\\')
        {
            escapedChar = "\\"; 
        }
        escapedChar += currentChar;

        compressed += std::to_string(count) + ":" + escapedChar + "|";
        i += count;
    }
    
    if (!compressed.empty())
    {
        compressed.pop_back();
    }

    return compressed;
}


std::vector<std::string>& PTC::RLECompressorModel::getRLETokens()
{
    return rleCompressedTokens;
}

#endif




