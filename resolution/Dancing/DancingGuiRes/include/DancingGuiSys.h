#ifndef __DancingGuiSys_h_
#define __DancingGuiSys_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkCameraMan.h>
#include <SdkTrays.h>
#include <map>
#include <string>
#include <vector>
#include "ParseXml.h"
#include "GuiLisener.h"

using namespace std;
using namespace OgreBites;
/*******************************************************************
* 说    明：窗口类型标志
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
enum WidgetType
{
    BaseState,
    CreateRole,
    GameSet,
    CreateHouse,
    GameStart,
    GamePractise,
    GameOver,
};
class DancingGuiSys;//前向声明
//
typedef void(DancingGuiSys::*functionPoint)();

/*******************************************************************
* 说    明：此类为单例模式
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
class DancingGuiSys
{
    //for singleton
private:
    DancingGuiSys(void);
    ~DancingGuiSys(void);
    static DancingGuiSys *instance;
public:
    static DancingGuiSys *GetInstance();//get the singleton pointer

public:
    /*******************************************************************
    * 说    明：设置界面函数，理论上一个界面对应一个函数
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
    void setWidgetBaseState();
    void setWidgetCreateRole();
    void setWidgetGameSet();
    void setWidgetCreateHouse();
    void setWidgetGameStart();
    void setWidgetGameOver();
    void setWidgetAboutMe();
    void setWidgetCreateNewHouse();
    void setWidgetGameReady();
    void setWidgetGamePractise();
    void setWidgetPlayVideo();

    /*******************************************************************
    * 说    明：进入局域网模式中创建房间界面CreateHouse的跳转函数
                           CreateHouse界面会请求获取网络上已有的房间列表，然后写在本地的houses.xml文件，
    					   然后到CreateHouse界面进行从houses.xml读取信息进行创建
    					   因为网络会有延迟，故此处需要一个中转函数进行协助
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
    void nothing();


    //跳转函数，mPair中存储了（按钮、跳转界面）的对应关系，故点击某界面后通过响应会调用到此函数进行界面跳转
    void executeFunction( string paraString)
    {
        mPair.first = this->mCurrentWidgetType;
        mPair.second = paraString;
        functionPoint temp = this->mMap[mPair];
        (this->*temp)();
    }

    //设置mMap
    void ConfigGuiInfo();

    //当前出处于局域网或是单机模式的变量的设置
    void setGameStyle( int paraInt)
    {
        m_gameStyle = paraInt;
    }

    /*******************************************************************
    * 说    明：未开始游戏前的界面操作中会有角色预览、场景预览等信息，在此处理显示模型
                           sceneManager可以通过mRoot得到
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
    void changgeScene(string);

    //some setter
    void setTrayMgr(SdkTrayManager *mTrayMgr);
    void setRoot(Ogre::Root *mRoot);


    //mCurrentWidgetType的gettere和setter
    WidgetType getCurrentWidgetType();
    void setCurrentWidgetType();

    //key event callback
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );

    //some getter or setter
    void setVerticalCenter(int parVerticalCenter)
    {
        mVerticalCenter = parVerticalCenter;
    }
    void setHorizontalCenter(int parHorizontalCenter)
    {
        mHorizontalCenter = parHorizontalCenter;
    }
    GuiLisener *getGuiLisener()
    {
        return mGuiLisener;
    }


private:

    //保存renderwindow的中点坐标，用以调整界面控件显示位置
    int mVerticalCenter;
    int mHorizontalCenter;


    //OgreSDKTray的监听器，处理buttonhit等信息皆在此
    GuiLisener *mGuiLisener;


    //当前界面的状态，即处于哪一个界面
    WidgetType mCurrentWidgetType;


    //从OGRE主程序传过来的变量
    OgreBites::SdkTrayManager *mTrayMgr;//用于管理界面
    Ogre::Root *mRoot;//用于管理应用程序停止


    //根据（界面、按钮）对决定响应函数的关联
    std::pair<WidgetType, string> mPair;//mMap的辅助
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //界面原件容器
    std::vector<OgreBites::Widget *> mWidget_vec;

    //游戏模式：单人/局域网对战   1-单人  2-局域网
    int  m_gameStyle;

    //无奈的变量 为了那个角色名和房间名的输入
    OgreBites::TextBox *mTextBox;

    //xml
    ParseXml *mParseXml;
};
#endif
