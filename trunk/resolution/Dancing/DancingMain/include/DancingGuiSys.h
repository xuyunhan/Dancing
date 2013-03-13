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
//��������   ��Ӧ�ó����м�������
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
    * �������ƣ�
    * ��    �ܣ����ι���
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��7��
    *******************************************************************/
    DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager);
    ~DancingGuiSys(void);
    /*******************************************************************
    * �������ƣ�setWidget***
    * ��    �ܣ�ÿ��set������Ӧһ�����������
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��7��
    *******************************************************************/
    void setWidgetBaseState();
    void setWidgetCreateRole();
    void setWidgetGameSet();
    void setWidgetCreateHouse();
    void setWidgetHoused();


    /*******************************************************************
    * �������ƣ�
    * ��    �ܣ�Handle  Gui��s  Event
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��7��
    *******************************************************************/
    void buttonHit(Button *button) ;
    void itemSelected(SelectMenu *menu) ;
    void labelHit(Label *label) ;
    void sliderMoved(Slider *slider) ;
    void checkBoxToggled(CheckBox *box) ;
    void okDialogClosed(const Ogre::DisplayString &message) ;
    void yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit) ;


    /*******************************************************************
    * �������ƣ�
    * ��    �ܣ�mCurrentWidgetType��gettere��setter
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��7��
    *******************************************************************/
    WidgetType getCurrentWidgetType();
    void setCurrentWidgetType();

  

	/*******************************************************************
	* �������ƣ�
	* ��    �ܣ����ã����桢��ť������Ӧ�����Ĺ���
	* ��    ����
	* �� �� ֵ��
	* ��    �ߣ� fux
	* �������䣺10809148@qq.com
	* ��    �ڣ�2013��3��7��
	*******************************************************************/
    void ConfigGuiInfo();
private:

    //��ǰ�����״̬����������һ������
    WidgetType mCurrentWidgetType;

    OgreBites::SdkTrayManager *mTrayMgr;


    //���ݣ����桢��ť���Ծ�����Ӧ�����Ĺ���
    std::pair<WidgetType, string> mPair;
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //����ԭ������
    std::vector<OgreBites::Widget *> mWidget_vec;


	//OgreBites::Button* mButton;
    //ֻΪ��OgreNone������λ�����ã�����ÿ������������鷳
    //Ogre::OverlayElement *mOverlayElement;



};
#endif