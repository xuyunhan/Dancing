#ifndef __ParseXml_h_
#define __ParseXml_h_
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
using namespace std;

/*******************************************************************
* 说    明：此类目前用处不多，只用了clearConfigFile函数，用于开始游戏时清理所有的XML文件信息
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
class ParseXml
{
public:
    ParseXml(void);
    ~ParseXml(void);
    bool readRolesFile();
    bool inputRolesFile();

    bool readHousesFile();
    bool inputHousesFile();

    void clearConfigFile();
};

#endif