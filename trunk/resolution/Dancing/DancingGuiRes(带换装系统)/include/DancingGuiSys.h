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
//��������   ��Ӧ�ó����м�������
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
    * �������ƣ�
    * ��    �ܣ����ι���
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��7��
    *******************************************************************/
	DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *mRoot,Ogre::RenderWindow *mWindow);
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

	void changgeScene(string widgetName);

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


    /*******************************************************************
    * �������ƣ�
    * ��    �ܣ�����������  ������������
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ� fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��11��
    *******************************************************************/




    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );

protected:
	/*******************************************************************
    * �������ƣ�createPreviewImage
    * ��    �ܣ���ѡ�������ʱ����Ԥ����������
    * ��    ����4����ѡ������󲿼�����
    * �� �� ֵ�� void
    * ��    �ߣ� xuyunhan
    * �������䣺271147505@qq.com
    * ��    �ڣ�2013��3��20��
    *******************************************************************/
	void createPreviewImage(Ogre::String hairName,Ogre::String upName,Ogre::String downName,Ogre::String shoesName);

	/*******************************************************************
    * �������ƣ�createPreviewImage
    * ��    �ܣ���ѡ�������ʱ����Ԥ����������
    * ��    ����2����ѡ������󲿼����ͺ�����
    * �� �� ֵ�� void
    * ��    �ߣ� xuyunhan
    * �������䣺271147505@qq.com
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
	void createPreviewImage(Ogre::String widgetName,Ogre::String selectedName);

	/*******************************************************************
    * �������ƣ�replaceEntity
    * ��    �ܣ��滻ʵ������ģ��
    * ��    ����2�������滻��ʵ��ָ�룬��ʵ������ģ������
    * �� �� ֵ�� void
    * ��    �ߣ� xuyunhan
    * �������䣺271147505@qq.com
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
	void replaceEntity(Ogre::Entity *&entyReplaced,Ogre::String newEntyName);

private:

    //��ǰ�����״̬����������һ������
    WidgetType mCurrentWidgetType;

    OgreBites::SdkTrayManager *mTrayMgr;

    Ogre::Root *mRoot;

	//licorice�õ�����ָ��
	Ogre::RenderWindow *mWindow;

    //���ݣ����桢��ť���Ծ�����Ӧ�����Ĺ���
    std::pair<WidgetType, string> mPair;
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //����ԭ������
    std::vector<OgreBites::Widget *> mWidget_vec;

    //��Ϸģʽ������/��������ս   1-����  2-������
    int  m_gameStyle;

	//licorice
	//��Ϸʱ���ÿ�ͨ������ʵʱ��ģ������ 1-��ͨ 2-ʵʱ��ģ
	int  m_roleStyle;

	//���ñ����Ƿ񴴽���һ���·���
	bool isNewHouse;

    //OgreBites::Button* mButton;
    //ֻΪ��OgreNone������λ�����ã�����ÿ������������鷳
    //Ogre::OverlayElement *mOverlayElement;

    //�Ѿ������͵���ģʽ�Ŀؼ���Ϊ��Ա���������ƽ�����ת��ʽ
    CheckBox  *singleBox;
    CheckBox  *multiBox;

    //������ɫ������Ů����ɫ��������Ϸ��װ��ѡ��
    CheckBox  *maleBox;
    CheckBox  *femaleBox;

	//��ͨ����ʵʱ��ģ�ĸ�ѡ��
	CheckBox *role_cartoon;
	CheckBox *role_real;

    //���εı���
    OgreBites::TextBox *mTextBox;

    //xml
    ParseXml *mParseXml;

	//xuyunhan
	//���������ʵ���ָ��,�������㻻װ
	Ogre::Entity *entyHair;
	Ogre::Entity *entyForWomanLongHair;
	Ogre::Entity *entyUp;
	Ogre::Entity *entyDown;
	Ogre::Entity *entyShoes_L;
	Ogre::Entity * entyShoes_R;

};
#endif
