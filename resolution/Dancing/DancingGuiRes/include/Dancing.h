#include "BasicApplication.h"
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

    //父类的虚函数
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

};
