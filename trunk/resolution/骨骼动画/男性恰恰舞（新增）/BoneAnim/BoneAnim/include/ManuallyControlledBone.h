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
	ManuallyControlledBone(Ogre::String boneName,Ogre::Entity *dstEnty);//带参构造,创建来自dstEnty实体的名为bonaName的骨骼手动控制的骨骼,在createScene里调用
	~ManuallyControlledBone(void);
protected:
	Ogre::Bone *ControlledBone;//手动控制的骨骼

public:
	void setBoneControlled(bool state);//设定骨骼手动控制状态为state
	void setBonePos(Ogre::Vector3 dstPos);//设定骨骼位置
	Ogre::Vector3 getBonePos(void);//获取骨骼位置
};
