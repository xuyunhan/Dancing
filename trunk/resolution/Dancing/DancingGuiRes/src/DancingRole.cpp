#include "DancingRole.h"

DancingRole::DancingRole(void)
{
    mRoleName = "0";
    mRoleSex = 0;
    mRoleHire = "0";
    mRoleDecorate = "0";
    mRoleUpware = "0";
    mRoleDownware = "0";
    mRoleShoe = "0";
}

DancingRole::~DancingRole(void)
{
}
DancingRole::DancingRole(string temp1, bool temp2, string temp3, string temp4, string temp5, string temp6, string temp7, RakNet::RakNetGUID temp8)
{
    mRoleName =  temp1;
    mRoleSex =  temp2;
    mRoleHire =  temp3;
    mRoleDecorate =  temp4;
    mRoleUpware =  temp5;
    mRoleDownware =  temp6;
    mRoleShoe =  temp7;
    mGuid = temp8;
}
DancingRole::DancingRole(string temp1, bool temp2, string temp3, string temp4, string temp5, string temp6, string temp7)
{
    mRoleName =  temp1;
    mRoleSex =  temp2;
    mRoleHire =  temp3;
    mRoleDecorate =  temp4;
    mRoleUpware =  temp5;
    mRoleDownware =  temp6;
    mRoleShoe =  temp7;
   // mGuid = temp8;
}
