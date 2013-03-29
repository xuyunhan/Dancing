#ifndef __Dancing_H__
#define __Dancing_H__
#include "BasicApplication.h"
#include "MoveableText.h"
#include "libOpenAl.h"
/*******************************************************************
* ˵    ����һ�������ʵ����ص���
* ��    �ߣ� grius
* ��    �ڣ�2013��3��22��
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

    //������麯��
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    Ogre::MovableText *mTextForReady;

    SoundManager *mSoundMgr;
    unsigned int mAudioId;

	Ogre::AnimationState *mAnimState[5];//��������




};
#endif
