#include "ParseXml.h"
/*******************************************************************
* ˵    ����Ŀǰֻ�õ���clearConfigFile����
* ��    �ߣ� grius
* ��    �ڣ�2013��3��22��
*******************************************************************/
ParseXml::ParseXml(void)
{
}

ParseXml::~ParseXml(void)
{
}
void ParseXml::clearConfigFile()
{
    TiXmlDocument  myDocument ;//= new TiXmlDocument();


    myDocument.SaveFile("newhouse.xml");
    myDocument.SaveFile("myhouse.xml");
    myDocument.SaveFile("otherrole.xml");
    myDocument.SaveFile("myrole.xml");

    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    myDocument.SaveFile("houses.xml");    /**/
}
bool ParseXml::inputRolesFile()
{
    //����xml�ļ�,szFilePathΪ�ļ������·��,�������ɹ�����true,����false

    //����һ��XML���ĵ�����
    TiXmlDocument myDocument ;//= new TiXmlDocument();
    //����һ����Ԫ�ز����ӡ�
    TiXmlElement *RootElement = new TiXmlElement("roles");
    myDocument.LinkEndChild(RootElement);
    //����һ��PersonԪ�ز����ӡ�
    TiXmlElement *PersonElement = new TiXmlElement("role");
    RootElement->LinkEndChild(PersonElement);
    //����PersonԪ�ص����ԡ�
    PersonElement->SetAttribute("name", "1");
    PersonElement->SetAttribute("sex", "��");
    PersonElement->SetAttribute("hire", "1");
    PersonElement->SetAttribute("decorate", "1");
    PersonElement->SetAttribute("upware", "1");
    PersonElement->SetAttribute("downware", "1");
    PersonElement->SetAttribute("shoe", "1");
    //����nameԪ�ء�ageԪ�ز����ӡ�

    myDocument.SaveFile("test.xml");//���浽�ļ�

    return true;
}

bool ParseXml::readRolesFile()
{
    //��ȡXml�ļ���������

    //CString appPath = GetAppPath();
    //string seperator = "\\";
    //string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
    //����һ��XML���ĵ�����
    TiXmlDocument  myDocument ;//= new TiXmlDocument();
    myDocument.LoadFile("test.xml");
    //��ø�Ԫ�أ���Persons��
    TiXmlElement *RootElement = myDocument.RootElement();
    //�����Ԫ�����ƣ������Persons��
    //		std::cout << RootElement->Value() << endl;
    //��õ�һ��Person�ڵ㡣
    TiXmlElement *FirstPerson = RootElement->FirstChildElement();

    TiXmlElement *SecondPerson = FirstPerson->NextSiblingElement();
    //��õ�һ��Person��name�ڵ��age�ڵ��ID���ԡ�



    string a = SecondPerson->Attribute("name");
    FirstPerson->Attribute("name");
    //�����һ��Person��name���ݣ��������ǣ�age���ݣ�����ID���ԣ�����

    //  cout << IDAttribute->Value() << endl;


    return true;
}
bool ParseXml::inputHousesFile()
{

    //����һ��XML���ĵ�����
    TiXmlDocument  myDocument ;//= new TiXmlDocument();
    //����һ����Ԫ�ز����ӡ�
    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    //����һ��PersonԪ�ز����ӡ�
    TiXmlElement *PersonElement = new TiXmlElement("house");
    RootElement->LinkEndChild(PersonElement);
    //����PersonԪ�ص����ԡ�
    PersonElement->SetAttribute("dancestyle", "1");
    PersonElement->SetAttribute("dancemusic", "��");
    PersonElement->SetAttribute("dancescene", "1");

    //����nameԪ�ء�ageԪ�ز����ӡ�

    myDocument.SaveFile("houses.xml");//���浽�ļ�


    return true;
}
bool ParseXml::readHousesFile()
{
    TiXmlDocument  myDocument;// = new TiXmlDocument();
    myDocument.LoadFile("houses.xml");
    //��ø�Ԫ�أ���Persons��
    TiXmlElement *RootElement = myDocument.RootElement();
    //�����Ԫ�����ƣ������Persons��
    //		std::cout << RootElement->Value() << endl;
    //��õ�һ��Person�ڵ㡣
    TiXmlElement *FirstPerson = RootElement->FirstChildElement();
    //��õ�һ��Person��name�ڵ��age�ڵ��ID���ԡ�

    TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
    //�����һ��Person��name���ݣ��������ǣ�age���ݣ�����ID���ԣ�����

    //  cout << IDAttribute->Value() << endl;
    return true;
}