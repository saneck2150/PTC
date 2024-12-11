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

namespace PTC
{
    const std::string INPUT_FORMAT = ".txt";

    class ExtractorModel;
    class RLECompressorModel;
    class HuffmanCompressorModel;
};

#endif