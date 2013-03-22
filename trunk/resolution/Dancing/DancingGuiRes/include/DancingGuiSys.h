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
* ˵    �����������ͱ�־
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
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
class DancingGuiSys;//ǰ������
//
typedef void(DancingGuiSys::*functionPoint)();

/*******************************************************************
* ˵    ��������Ϊ����ģʽ
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
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
    * ˵    �������ý��溯����������һ�������Ӧһ������
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��21��
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
    * ˵    �������������ģʽ�д����������CreateHouse����ת����
                           CreateHouse����������ȡ���������еķ����б�Ȼ��д�ڱ��ص�houses.xml�ļ���
    					   Ȼ��CreateHouse������д�houses.xml��ȡ��Ϣ���д���
    					   ��Ϊ��������ӳ٣��ʴ˴���Ҫһ����ת��������Э��
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
    void nothing();


    //��ת������mPair�д洢�ˣ���ť����ת���棩�Ķ�Ӧ��ϵ���ʵ��ĳ�����ͨ����Ӧ����õ��˺������н�����ת
    void executeFunction( string paraString)
    {
        mPair.first = this->mCurrentWidgetType;
        mPair.second = paraString;
        functionPoint temp = this->mMap[mPair];
        (this->*temp)();
    }

    //����mMap
    void ConfigGuiInfo();

    //��ǰ�����ھ��������ǵ���ģʽ�ı���������
    void setGameStyle( int paraInt)
    {
        m_gameStyle = paraInt;
    }

    /*******************************************************************
    * ˵    ����δ��ʼ��Ϸǰ�Ľ�������л��н�ɫԤ��������Ԥ������Ϣ���ڴ˴�����ʾģ��
                           sceneManager����ͨ��mRoot�õ�
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
    void changgeScene(string);

    //some setter
    void setTrayMgr(SdkTrayManager *mTrayMgr);
    void setRoot(Ogre::Root *mRoot);


    //mCurrentWidgetType��gettere��setter
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

    //����renderwindow���е����꣬���Ե�������ؼ���ʾλ��
    int mVerticalCenter;
    int mHorizontalCenter;


    //OgreSDKTray�ļ�����������buttonhit����Ϣ���ڴ�
    GuiLisener *mGuiLisener;


    //��ǰ�����״̬����������һ������
    WidgetType mCurrentWidgetType;


    //��OGRE�����򴫹����ı���
    OgreBites::SdkTrayManager *mTrayMgr;//���ڹ������
    Ogre::Root *mRoot;//���ڹ���Ӧ�ó���ֹͣ


    //���ݣ����桢��ť���Ծ�����Ӧ�����Ĺ���
    std::pair<WidgetType, string> mPair;//mMap�ĸ���
    std::map <std::pair<WidgetType, string>, functionPoint> mMap;

    //����ԭ������
    std::vector<OgreBites::Widget *> mWidget_vec;

    //��Ϸģʽ������/��������ս   1-����  2-������
    int  m_gameStyle;

    //���εı��� Ϊ���Ǹ���ɫ���ͷ�����������
    OgreBites::TextBox *mTextBox;

    //xml
    ParseXml *mParseXml;
};
#endif
