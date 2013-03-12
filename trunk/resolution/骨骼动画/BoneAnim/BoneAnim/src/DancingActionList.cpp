#include "DancingActionList.h"

DancingActionList::DancingActionList(void)
	{
		
		actNum=10;//初始化动作数为10个
		actionnames=new Ogre::String[actNum];//动态分配空间
		
		actionnames[0]="zuojiaodengdi";//左脚蹬地
		actionnames[1]="ceshen";//侧身
		actionnames[2]="zuojiaoqiluo";//左脚起落
		actionnames[3]= "huizuoshou";//挥左手
		actionnames[4]="xiadun";//下蹲
		actionnames[5]="youtuihoushen";//右腿后伸
		actionnames[6]="qitiaoluodi";//起跳落地
		actionnames[7]="qianhoubu";//前后歩
		actionnames[8]="mabuyaobai";//马步摇摆
		actionnames[9]="youjiaoqiluo";//右脚起落

		presentActNum = 0;//初始化当前动作为第一个
	}

DancingActionList::~DancingActionList(void)
{
	if (actionnames)
		delete[] actionnames;
}

void DancingActionList::jumpToNextAct()
{
	++presentActNum;//跳到下一个动作
	if(presentActNum == actNum)//若当前动作越界,则跳到第一个动作
	{
		presentActNum = 0;
	}
}