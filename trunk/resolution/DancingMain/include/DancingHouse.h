#if !defined(_DancingHouse_H)
#define _DancingHouse_H

#include "DancingRole.h"

/*******************************************************************
* ˵    ����ά����ʼ��Ϸ�󷿼����Ϣ�Ķ���Ӧ�����߼���Ϣ���������Ƶȣ�����Ⱦ��Ϣ���ĸ�ģ�ͣ��ȵ�
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
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
    * ˵    ������Ϊ������Ҳ������ļ���������������Ҫ�Ƿ������õģ��ͻ��������������
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
    //void setterHouseName (DancingRole *, int);
    DancingRole *getterRole (int);
    //�����������ǲ����д����ã�����ֻ����ɫָ�룬Ȼ�������ں������д���,�پ��Ǻ�����
    void setterRole (DancingRole *, int);
    void deleteRole (DancingRole *, int temp = 1);



    //ǰ�����Ա������getter��setter
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