#if !defined(_DancingRole_H)
#define _DancingRole_H
#include <string>
#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "RakSleep.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "Kbhit.h"
#include <stdio.h>
#include <string.h>
#include "Gets.h"

#include "NetworkIDObject.h"

#include <vector>
#include "OgreSingleton.h"
using namespace std;

/*******************************************************************
* ˵    ����ά����ʼ��Ϸ���ɫ����Ϣ�Ķ���Ӧ�����߼���Ϣ����ɫ���Ƶȣ�����Ⱦ��Ϣ���ĸ�ģ�ͣ��ȵ�
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
*******************************************************************/
class DancingRole
{
public:
    DancingRole(void);
    DancingRole(string , bool, string, string, string, string, string, RakNet::RakNetGUID);
    DancingRole(string , bool, string, string, string, string, string);
    ~DancingRole(void);
private:
    string mRoleName;
    bool   mRoleSex;
    string mRoleHire;
    string mRoleDecorate;
    string mRoleUpware;
    string mRoleDownware;
    string mRoleShoe;

    //manager msg�ñ�����Ҫ���ڷ������ˣ��ͻ������衤��
    RakNet::RakNetGUID mGuid;

public:
    //8��getter��setter
    void setterGuid(RakNet::RakNetGUID temp)
    {
        mGuid = temp;
    }
    RakNet::RakNetGUID getterGuid()
    {
        return  mGuid;
    }
    string getterRoleName()
    {
        return  mRoleName;
    }
    bool getterRoleSex()
    {
        return mRoleSex ;
    }
    string getterRoleHire()
    {
        return mRoleHire ;
    }
    string getterRoleDecorate()
    {
        return  mRoleDecorate;
    }
    string getterRoleUpware()
    {
        return  mRoleUpware;
    }
    string getterRoleDownware()
    {
        return  mRoleDownware;
    }
    string getterRoleShoe()
    {
        return  mRoleShoe;
    }

    void setterRoleName(string temp)
    {
        mRoleName = temp;
    }
    void setterRoleSex(bool temp)
    {
        mRoleSex = temp;
    }
    void setterRoleHire(string temp)
    {
        mRoleHire = temp;
    }
    void setterRoleDecorate(string temp)
    {
        mRoleDecorate = temp;
    }
    void setterRoleUpware(string temp)
    {
        mRoleUpware = temp;
    }
    void setterRoleDownware(string temp)
    {
        mRoleDownware = temp;
    }
    void setterRoleShoe(string temp)
    {
        mRoleShoe = temp;
    }

};
#endif

