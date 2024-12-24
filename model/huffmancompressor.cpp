#ifndef _HUFFMAN_COMPRESSOR_
#define _HUFFMAN_COMPRESSOR_
#include "modellib.hpp"

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

class Compare {
public:
    bool operator()(HuffmanNode* a, HuffmanNode* b) 
    {
        return a->frequency > b->frequency;
    }
};

class HuffmanCompressor {
private:
    std::unordered_map<char, int> calculateFrequency(const std::vector<std::string>& text);
    HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequency_map);
    void generateCodes(HuffmanNode* node, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes);
    std::string encodeText(const std::vector<std::string>& text, const std::unordered_map<char, std::string>& huffmanCodes);
public:
    HuffmanCompressor() {};
    std::string compress(const std::vector<std::string>& text);

};

std::unordered_map<char, int> HuffmanCompressor::calculateFrequency(const std::vector<std::string>& text)
{
    std::unordered_map<char, int> frequency_map;
    if (text.empty()) 
        return frequency_map;
    size_t chunk_size = text.size() / PTC::AVAILABLE_THREADS;
    std::vector<std::unordered_map<char, int>> partial_maps(PTC::AVAILABLE_THREADS);
    std::mutex mtx;
    auto worker = [&](size_t start, size_t end, size_t index)
    {
        for (size_t i = start; i < end; ++i)
        {
            for (char c : text[i])
            {
                partial_maps[index][c]++;
            }
        }
    };
    std::vector<std::thread> threads;
    threads.reserve(PTC::AVAILABLE_THREADS);

    for (size_t i = 0; i < PTC::AVAILABLE_THREADS; ++i)
    {
        size_t start = i * chunk_size;
        size_t end = (i == PTC::AVAILABLE_THREADS - 1) ? text.size() : (start + chunk_size);
        threads.emplace_back(worker, start, end, i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    for (auto& local_map : partial_maps)
    {
        for (auto& pair : local_map)
        {
            frequency_map[pair.first] += pair.second;
        }
    }

    return frequency_map;
}

HuffmanNode* HuffmanCompressor::buildHuffmanTree(const std::unordered_map<char, int>& frequency_map)
{
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
    for (const auto& pair : frequency_map) 
    {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) 
    {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }

    return minHeap.top();
}

void HuffmanCompressor::generateCodes(HuffmanNode* node, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes)
{
    if (!node) 
        return;

    if (node->character != '\0') 
    {
        huffmanCodes[node->character] = code;
    }

    generateCodes(node->left,  code + "0", huffmanCodes);
    generateCodes(node->right, code + "1", huffmanCodes);
}

std::string HuffmanCompressor::encodeText(const std::vector<std::string>& text, const std::unordered_map<char, std::string>& huffmanCodes)
{
    if (text.empty()) 
        return "";
    
    const size_t num_threads = std::thread::hardware_concurrency() ? 
                               std::thread::hardware_concurrency() : 2;
    size_t chunk_size = text.size() / num_threads;
    std::vector<std::string> partial_encodings(text.size());

    auto encoder = [&](size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            for (char c : text[i])
            {
                partial_encodings[i] += huffmanCodes.at(c);
            }
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    for (size_t i = 0; i < num_threads; ++i)
    {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? text.size() : (start + chunk_size);

        threads.emplace_back(encoder, start, end);
    }
    for (auto& t : threads)
    {
        t.join();
    }
    std::string encodedResult;
    encodedResult.reserve(text.size() * 100 ); 

    for (auto& part : partial_encodings)
    {
        encodedResult += part;
    }

    return encodedResult;
}

std::string HuffmanCompressor::compress(const std::vector<std::string>& text)
{
    auto frequency_map = calculateFrequency(text);
    HuffmanNode* root = buildHuffmanTree(frequency_map);
    std::unordered_map<char, std::string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    return encodeText(text, huffmanCodes);
}


#endif