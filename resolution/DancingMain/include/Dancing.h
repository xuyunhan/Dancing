#ifndef __Dancing_H__
#define __Dancing_H__
#include "BasicApplication.h"
#include "MoveableText.h"
#include "libOpenAl.h"
/*******************************************************************
* 说    明：一个与具体实现相关的类
* 作    者： grius
* 日    期：2013年3月22日
*******************************************************************/

class Dancing: public BasicApplication
{
public:
    Dancing(void);
    ~Dancing(void);

    //
    void createSceneForCreateRole();
    void createSceneForCreateHouse();
    void createSceneForGameSet();
    void createSceneForGameStart();
    void createSceneForGamePractise();
    virtual void createSceneForWelcome();

    //父类的虚函数
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    Ogre::MovableText *mTextForReady;

    SoundManager *mSoundMgr;
    unsigned int mAudioId;

	Ogre::AnimationState *mAnimState[5];//动画对象




};
#endif
