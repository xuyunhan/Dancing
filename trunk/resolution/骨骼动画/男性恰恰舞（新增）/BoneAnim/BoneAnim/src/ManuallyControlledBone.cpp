#include "ManuallyControlledBone.h"

ManuallyControlledBone::ManuallyControlledBone(void)
{
}

ManuallyControlledBone::ManuallyControlledBone(Ogre::String boneName,Ogre::Entity *dstEnty)//��������dstEntyʵ�����ΪbonaName�Ĺ����ֶ����ƵĹ���,��createScene�����
{
	Ogre::SkeletonInstance *skel = dstEnty->getSkeleton();//�õ�ʵ��Ǽ�
	ControlledBone = skel->getBone(boneName);//�������ֵõ�����
}

ManuallyControlledBone::~ManuallyControlledBone(void)
{
}

void ManuallyControlledBone::setBoneControlled(bool state)
{
	ControlledBone->setManuallyControlled(state);//���ֶ�����״̬Ϊstate
}

void ManuallyControlledBone::setBonePos(Ogre::Vector3 dstPos)
{
	ControlledBone->setPosition(dstPos);//�趨����λ��
}

Ogre::Vector3 ManuallyControlledBone::getBonePos(void)
{
	return ControlledBone->getPosition();//���ع���λ��
}