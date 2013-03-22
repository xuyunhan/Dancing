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
	GamePractise,
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
	DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *mRoot,Ogre::RenderWindow *mWindow);
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
	//licorice
	void setWidgetGameReady();
	void setWidgetGamePractise();
	void setWidgetPlayVideo();
	void setWidgetCreateNewHouse();

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

	void changgeScene(string widgetName);

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

protected:
	/*******************************************************************
    * 函数名称：createPreviewImage
    * 功    能：在选择形象的时候创造预览人物形象
    * 参    数：4个，选择的形象部件名称
    * 返 回 值： void
    * 作    者： xuyunhan
    * 电子邮箱：271147505@qq.com
    * 日    期：2013年3月20日
    *******************************************************************/
	void createPreviewImage(Ogre::String hairName,Ogre::String upName,Ogre::String downName,Ogre::String shoesName);

	/*******************************************************************
    * 函数名称：createPreviewImage
    * 功    能：在选择形象的时候创造预览人物形象
    * 参    数：2个，选择的形象部件类型和名称
    * 返 回 值： void
    * 作    者： xuyunhan
    * 电子邮箱：271147505@qq.com
    * 日    期：2013年3月21日
    *******************************************************************/
	void createPreviewImage(Ogre::String widgetName,Ogre::String selectedName);

	/*******************************************************************
    * 函数名称：replaceEntity
    * 功    能：替换实体对象的模型
    * 参    数：2个，被替换的实体指针，新实体对象的模型名字
    * 返 回 值： void
    * 作    者： xuyunhan
    * 电子邮箱：271147505@qq.com
    * 日    期：2013年3月22日
    *******************************************************************/
	void replaceEntity(Ogre::Entity *&entyReplaced,Ogre::String newEntyName);

private:

    //当前界面的状态，即处于哪一个界面
    WidgetType mCurrentWidgetType;

    OgreBites::SdkTrayManager *mTrayMgr;

    Ogre::Root *mRoot;

	//licorice得到窗口指针
	Ogre::RenderWindow *mWindow;

    //根据（界面、按钮）对决定响应函数的关联
    std::pair<WidgetType, string> mPair;
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //界面原件容器
    std::vector<OgreBites::Widget *> mWidget_vec;

    //游戏模式：单人/局域网对战   1-单人  2-局域网
    int  m_gameStyle;

	//licorice
	//游戏时采用卡通形象还是实时建模的形象 1-卡通 2-实时建模
	int  m_roleStyle;

	//设置变量是否创建了一个新房间
	bool isNewHouse;

    //OgreBites::Button* mButton;
    //只为在OgreNone中设置位置所用，避免每次重新申请的麻烦
    //Ogre::OverlayElement *mOverlayElement;

    //把局域网和单人模式的控件设为成员变量，控制界面跳转方式
    CheckBox  *singleBox;
    CheckBox  *multiBox;

    //男生角色，还是女生角色，决定游戏服装的选择
    CheckBox  *maleBox;
    CheckBox  *femaleBox;

	//卡通形象、实时建模的复选框
	CheckBox *role_cartoon;
	CheckBox *role_real;

    //无奈的变量
    OgreBites::TextBox *mTextBox;

    //xml
    ParseXml *mParseXml;

	//xuyunhan
	//身体各部分实体的指针,这样方便换装
	Ogre::Entity *entyHair;
	Ogre::Entity *entyForWomanLongHair;
	Ogre::Entity *entyUp;
	Ogre::Entity *entyDown;
	Ogre::Entity *entyShoes_L;
	Ogre::Entity * entyShoes_R;

};
#endif
