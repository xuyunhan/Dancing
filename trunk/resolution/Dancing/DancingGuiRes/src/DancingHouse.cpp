#include "DancingHouse.h"

DancingHouse::DancingHouse(void)
{
    mHouseName = "0";
    mHouseDancestyle = "0";
    mHouseDancemusic = "0";
    mHouseDancescene = "0";
    mHouseSite = 0;
    mHouseRole[0] = 0;
    mHouseRole[1] = 0;
}
DancingHouse::DancingHouse(string temp1, string temp2, string temp3, string temp4)
{
    mHouseName = temp1;
    mHouseDancestyle = temp2;
    mHouseDancemusic = temp3;
    mHouseDancescene = temp4;
    mHouseSite = 1;//由于有创建者，故新建房间时剩余座位为1

}

DancingHouse::~DancingHouse(void)
{
}

DancingRole *DancingHouse::getterRole (int temp)
{
    return mHouseRole[temp];
}
void DancingHouse::setterRole (DancingRole *temp1, int temp2)
{
    mHouseRole[temp2] = temp1;
    this->mHouseSite -= 1;
}
void DancingHouse::deleteRole (DancingRole *temp1, int temp2)//fux add temp2参数考虑存在性
{
    delete temp1;
    this->mHouseSite += 1;


}