#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
class DancingActionList
{
public:
	DancingActionList(void);
	~DancingActionList(void);
protected:
	Ogre::String *actionnames;//放动作动画名称们的数组
	int actNum;//动画总数
	int presentActNum;//当前动画序号
public:
/*	bool setActNum(int num)
	{
		if (num >=0)
		{
			actNum = num;
			return true;
		}
		else
			return false;
	}
*/
	int getActNum(){ return actNum; }//得到动画总数
	int getPresentActNum(){return presentActNum;}//得到当前动画序号
	Ogre::String getActName(int num) { return actionnames[num]; }//通过动作序号返回动作名称
	void jumpToNextAct();//跳到下一个动作
};
