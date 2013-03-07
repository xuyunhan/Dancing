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
using namespace std;
using namespace OgreBites;

enum WidgetType
{
    BaseState,
    CreateRole,
    GameSet,
    CreateHouse,
    Housed,
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
    DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager);
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
    void setWidgetHoused();


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

    void ConfigGuiInfo();
private:

    WidgetType mCurrentWidgetType;
    OgreBites::SdkTrayManager *mTrayMgr;

    std::pair<WidgetType, string> mPair;
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    std::vector<OgreBites::Widget *> mWidget_vec;

    Button *mButton;
    Ogre::OverlayElement *mOverlayElement;



};
#endif
