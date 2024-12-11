#include "extractor.cpp"

#ifndef _COMPRESSOR_MODEL_
#define _COMPRESSOR_MODEL_

class PTC::CompressorModel : protected PTC::ExtractorModel
{
public:
    void rleCompressor (PTC::ExtractorModel& tokenisedText);
    void haffmanCompressor ();
};

void PTC::CompressorModel::rleCompressor(PTC::ExtractorModel& tokenisedText)
{
    for (auto i : getInputDataTokens())
    {
        
    }
}
#endif



