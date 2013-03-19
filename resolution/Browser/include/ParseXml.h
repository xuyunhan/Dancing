#ifndef __ParseXml_h_
#define __ParseXml_h_
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
using namespace std;
class ParseXml
{
public:
    ParseXml(void);
    ~ParseXml(void);
    bool readRolesFile();
    bool inputRolesFile();

    bool readHousesFile();
    bool inputHousesFile();
};

#endif