#include "BasicApplication.h"
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

    //������麯��
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

};
