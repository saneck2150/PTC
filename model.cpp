#include"libptc.hpp"

#ifndef _CODER_MODEL_
#define _CODER_MODEL_
class CoderModel
{
private:     
    bool okFile = false;
    std::string fileName = "none";
public:
    void getFile (std::string filename);
    static std::string getText();
};
#endif

void CoderModel::getFile (std::string filename)
{
    std::fstream stream (filename);

}

std::string CoderModel::getText ()
{
    return 0;
}