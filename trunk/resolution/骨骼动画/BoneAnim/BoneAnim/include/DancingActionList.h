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
	Ogre::String *actionnames;//�Ŷ������������ǵ�����
	int actNum;//��������
	int presentActNum;//��ǰ�������
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
	int getActNum(){ return actNum; }//�õ���������
	int getPresentActNum(){return presentActNum;}//�õ���ǰ�������
	Ogre::String getActName(int num) { return actionnames[num]; }//ͨ��������ŷ��ض�������
	void jumpToNextAct();//������һ������
};
