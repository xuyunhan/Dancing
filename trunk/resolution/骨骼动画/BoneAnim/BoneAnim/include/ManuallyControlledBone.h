#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

class ManuallyControlledBone
{
public:
	ManuallyControlledBone(void);
	ManuallyControlledBone(Ogre::String boneName,Ogre::Entity *dstEnty);//���ι���,��������dstEntyʵ�����ΪbonaName�Ĺ����ֶ����ƵĹ���,��createScene�����
	~ManuallyControlledBone(void);
protected:
	Ogre::Bone *ControlledBone;//�ֶ����ƵĹ���

public:
	void setBoneControlled(bool state);//�趨�����ֶ�����״̬Ϊstate
	void setBonePos(Ogre::Vector3 dstPos);//�趨����λ��
	Ogre::Vector3 getBonePos(void);//��ȡ����λ��
};
