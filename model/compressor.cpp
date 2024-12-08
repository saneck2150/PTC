#include "extractor.cpp"

#ifndef _COMPRESSOR_MODEL_
#define _COMPRESSOR_MODEL_

class PTC::CompressorModel : private PTC::ExtractorModel
{
public:
    void rleCompressor ();
    void haffmanCompressor ();
};

#endif



