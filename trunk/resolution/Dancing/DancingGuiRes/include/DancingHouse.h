#if !defined(_DancingHouse_H)
#define _DancingHouse_H

#include "DancingRole.h"

/*******************************************************************
* 说    明：维护开始游戏后房间的信息的对象，应包含逻辑信息（房间名称等）、渲染信息（哪个模型）等等
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
class DancingHouse
{
public:

    DancingHouse(void);
    DancingHouse(string, string, string, string);
    ~DancingHouse();

private:
    string mHouseName;
    string mHouseDancestyle;
    string mHouseDancemusic;
    string mHouseDancescene;
    int mHouseSite;

    DancingRole *mHouseRole[2];
public:
    /*******************************************************************
    * 说    明：因为服务器也用这个文件，这三个函数主要是服务器用的，客户端无需多做关心
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
    //void setterHouseName (DancingRole *, int);
    DancingRole *getterRole (int);
    //这两个函数是不是有带斟酌，考虑只给角色指针，然后自行在函数体中处理,再就是函数名
    void setterRole (DancingRole *, int);
    void deleteRole (DancingRole *, int temp = 1);



    //前五个成员变量的getter和setter
    void setterHouseName (string temp)
    {
        mHouseName  = temp;
    }
    void setterHouseDancestyle (string temp)
    {
        mHouseDancestyle = temp;
    }
    void setterHouseDancemusic (string temp)
    {
        mHouseDancemusic = temp;
    }
    void setterHouseDancescene (string temp)
    {
        mHouseDancescene  = temp;
    }
    void setterHouseSite (int temp)
    {
        mHouseSite = temp;
    }


    string getterHouseName()
    {
        return mHouseName ;
    }
    string getterHouseDancestyle()
    {
        return mHouseDancestyle  ;
    }
    string getterHouseDancemusic ()
    {
        return mHouseDancemusic ;
    }
    string getterHouseDancescene()
    {
        return  mHouseDancescene;
    }
    int getterHouseSite()
    {
        return  mHouseSite;
    }

};
#endif