#ifndef __ParseXml_h_
#define __ParseXml_h_
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
using namespace std;

/*******************************************************************
* ˵    ��������Ŀǰ�ô����ֻ࣬����clearConfigFile���������ڿ�ʼ��Ϸʱ�������е�XML�ļ���Ϣ
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
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