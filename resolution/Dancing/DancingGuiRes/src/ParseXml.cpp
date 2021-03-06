#include "ParseXml.h"
/*******************************************************************
* 说    明：目前只用到了clearConfigFile函数
* 作    者： grius
* 日    期：2013年3月22日
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
    //创建xml文件,szFilePath为文件保存的路径,若创建成功返回true,否则false

    //创建一个XML的文档对象。
    TiXmlDocument myDocument ;//= new TiXmlDocument();
    //创建一个根元素并连接。
    TiXmlElement *RootElement = new TiXmlElement("roles");
    myDocument.LinkEndChild(RootElement);
    //创建一个Person元素并连接。
    TiXmlElement *PersonElement = new TiXmlElement("role");
    RootElement->LinkEndChild(PersonElement);
    //设置Person元素的属性。
    PersonElement->SetAttribute("name", "1");
    PersonElement->SetAttribute("sex", "男");
    PersonElement->SetAttribute("hire", "1");
    PersonElement->SetAttribute("decorate", "1");
    PersonElement->SetAttribute("upware", "1");
    PersonElement->SetAttribute("downware", "1");
    PersonElement->SetAttribute("shoe", "1");
    //创建name元素、age元素并连接。

    myDocument.SaveFile("test.xml");//保存到文件

    return true;
}

bool ParseXml::readRolesFile()
{
    //读取Xml文件，并遍历

    //CString appPath = GetAppPath();
    //string seperator = "\\";
    //string fullPath = appPath.GetBuffer(0) + seperator + szFileName;
    //创建一个XML的文档对象。
    TiXmlDocument  myDocument ;//= new TiXmlDocument();
    myDocument.LoadFile("test.xml");
    //获得根元素，即Persons。
    TiXmlElement *RootElement = myDocument.RootElement();
    //输出根元素名称，即输出Persons。
    //		std::cout << RootElement->Value() << endl;
    //获得第一个Person节点。
    TiXmlElement *FirstPerson = RootElement->FirstChildElement();

    TiXmlElement *SecondPerson = FirstPerson->NextSiblingElement();
    //获得第一个Person的name节点和age节点和ID属性。



    string a = SecondPerson->Attribute("name");
    FirstPerson->Attribute("name");
    //输出第一个Person的name内容，即周星星；age内容，即；ID属性，即。

    //  cout << IDAttribute->Value() << endl;


    return true;
}
bool ParseXml::inputHousesFile()
{

    //创建一个XML的文档对象。
    TiXmlDocument  myDocument ;//= new TiXmlDocument();
    //创建一个根元素并连接。
    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    //创建一个Person元素并连接。
    TiXmlElement *PersonElement = new TiXmlElement("house");
    RootElement->LinkEndChild(PersonElement);
    //设置Person元素的属性。
    PersonElement->SetAttribute("dancestyle", "1");
    PersonElement->SetAttribute("dancemusic", "男");
    PersonElement->SetAttribute("dancescene", "1");

    //创建name元素、age元素并连接。

    myDocument.SaveFile("houses.xml");//保存到文件


    return true;
}
bool ParseXml::readHousesFile()
{
    TiXmlDocument  myDocument;// = new TiXmlDocument();
    myDocument.LoadFile("houses.xml");
    //获得根元素，即Persons。
    TiXmlElement *RootElement = myDocument.RootElement();
    //输出根元素名称，即输出Persons。
    //		std::cout << RootElement->Value() << endl;
    //获得第一个Person节点。
    TiXmlElement *FirstPerson = RootElement->FirstChildElement();
    //获得第一个Person的name节点和age节点和ID属性。

    TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
    //输出第一个Person的name内容，即周星星；age内容，即；ID属性，即。

    //  cout << IDAttribute->Value() << endl;
    return true;
}