#include "ManuallyControlledBone.h"

ManuallyControlledBone::ManuallyControlledBone(void)
{
}

ManuallyControlledBone::ManuallyControlledBone(Ogre::String boneName,Ogre::Entity *dstEnty)//创建来自dstEnty实体的名为bonaName的骨骼手动控制的骨骼,在createScene里调用
{
	Ogre::SkeletonInstance *skel = dstEnty->getSkeleton();//得到实体骨架
	ControlledBone = skel->getBone(boneName);//根据名字得到骨骼
}

ManuallyControlledBone::~ManuallyControlledBone(void)
{
}

void ManuallyControlledBone::setBoneControlled(bool state)
{
	ControlledBone->setManuallyControlled(state);//设手动控制状态为state
}

void ManuallyControlledBone::setBonePos(Ogre::Vector3 dstPos)
{
	ControlledBone->setPosition(dstPos);//设定骨骼位置
}

Ogre::Vector3 ManuallyControlledBone::getBonePos(void)
{
	return ControlledBone->getPosition();//返回骨骼位置
}