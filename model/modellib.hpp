#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <condition_variable>
#include <functional>
#include <future>

namespace PTC
{
    const std::string INPUT_FORMAT = ".txt";
    const int AVAILABLE_THREADS = std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 1;
    class ExtractorModel;
    class HuffmanCompressorModel;
};

#endif