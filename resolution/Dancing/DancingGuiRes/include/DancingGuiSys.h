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

using namespace std;
using namespace OgreBites;
//窗口类型   即应用程序有几个界面
enum WidgetType
{
    BaseState,
    CreateRole,
    GameSet,
    CreateHouse,
    // Housed,
    GameStart,
    GameOver,
};
class DancingGuiSys;
typedef void(DancingGuiSys::*functionPoint)();
class DancingGuiSys
{
public:
    DancingGuiSys(void);

    /*******************************************************************
    * 函数名称：
    * 功    能：带参构造
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月7日
    *******************************************************************/
    DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *mRoot, Ogre::RenderWindow *mWindow);
    ~DancingGuiSys(void);
    /*******************************************************************
    * 函数名称：setWidget***
    * 功    能：每个set函数对应一个界面的设置
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月7日
    *******************************************************************/
    void setWidgetBaseState();
    void setWidgetCreateRole();
    void setWidgetGameSet();
    void setWidgetCreateHouse();
    // void setWidgetHoused();
    void setWidgetGameStart();
    void setWidgetGameOver();
    void setWidgetAboutMe();

    void nothing();



    /*******************************************************************
    * 函数名称：
    * 功    能：Handle  Gui·s  Event
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月7日
    *******************************************************************/
    void buttonHit(Button *button) ;
    void itemSelected(SelectMenu *menu) ;
    void labelHit(Label *label) ;
    void sliderMoved(Slider *slider) ;
    void checkBoxToggled(CheckBox *box) ;
    void okDialogClosed(const Ogre::DisplayString &message) ;
    void yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit) ;

    void changgeScene(string);


    /*******************************************************************
    * 函数名称：
    * 功    能：mCurrentWidgetType的gettere和setter
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月7日
    *******************************************************************/
    WidgetType getCurrentWidgetType();
    void setCurrentWidgetType();



    /*******************************************************************
    * 函数名称：
    * 功    能：设置（界面、按钮）与响应函数的关联
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月7日
    *******************************************************************/
    void ConfigGuiInfo();


    /*******************************************************************
    * 函数名称：
    * 功    能：监听鼠标键盘  用于文字输入
    * 参    数：
    * 返 回 值：
    * 作    者： fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月11日
    *******************************************************************/
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );

private:

    //当前界面的状态，即处于哪一个界面
    WidgetType mCurrentWidgetType;

    OgreBites::SdkTrayManager *mTrayMgr;

    Ogre::Root *mRoot;
    Ogre::RenderWindow *mWindow;    // render window

    //根据（界面、按钮）对决定响应函数的关联
    std::pair<WidgetType, string> mPair;
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //界面原件容器
    std::vector<OgreBites::Widget *> mWidget_vec;

    //游戏模式：单人/局域网对战   1-单人  2-局域网
    int  m_gameStyle;

    //OgreBites::Button* mButton;
    //只为在OgreNone中设置位置所用，避免每次重新申请的麻烦
    //Ogre::OverlayElement *mOverlayElement;

    //把局域网和单人模式的控件设为成员变量，控制界面跳转方式
    CheckBox  *singleBox;
    CheckBox  *multiBox;

    //男生角色，还是女生角色，决定游戏服装的选择
    CheckBox  *maleBox;
    CheckBox  *femaleBox;

    //无奈的变量
    OgreBites::TextBox *mTextBox;

    //xml
    ParseXml *mParseXml;

    //
    string mWillHouseLabelName;
    string mWillHouse;



};
#endif
