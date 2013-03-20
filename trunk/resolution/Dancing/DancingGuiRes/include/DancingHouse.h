#if !defined(_DancingHouse_H)
#define _DancingHouse_H

#include "DancingRole.h"
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
    //void setterHouseName (DancingRole *, int);
    DancingRole *getterRole (int);
    //这两个函数是不是有带斟酌，考虑只给角色指针，然后自行在函数体中处理,再就是函数名
    void setterRole (DancingRole *, int);
    void deleteRole (DancingRole *, int temp = 1);





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