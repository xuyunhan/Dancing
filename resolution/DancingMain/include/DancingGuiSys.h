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
#include "DancingGuiLisener.h"

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
                           CreateHouse����������ȡ���������еķ����б���Ȼ��д�ڱ��ص�houses.xml�ļ���
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
    WidgetType getCurrentWidgetType()
    {
        return this->mCurrentWidgetType;
    }
    void setCurrentWidgetType() {}


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
    DancingGuiLisener *getDancingGuiLisener()
    {
        return mDancingGuiLisener;
    }

    void setCurrentTypeChanged(bool paraBool)
    {
        isCurrentTypeChanged = paraBool;
    }
    bool getCurrentTypeChanged()
    {
        return isCurrentTypeChanged;
    }

    /*******************************************************************
        * �������ƣ�createPreviewImage
        * ��    �ܣ���ѡ�������ʱ����Ԥ����������
        * ��    ����4����ѡ������󲿼�����
        * �� �� ֵ�� void
        * ��    �ߣ� xuyunhan
        * �������䣺271147505@qq.com
        * ��    �ڣ�2013��3��20��
        *******************************************************************/
    void createPreviewImage(Ogre::String hairName, Ogre::String upName, Ogre::String downName, Ogre::String shoesName);

    /*******************************************************************
    * �������ƣ�createPreviewImage
    * ��    �ܣ���ѡ�������ʱ����Ԥ����������
    * ��    ����2����ѡ������󲿼����ͺ�����
    * �� �� ֵ�� void
    * ��    �ߣ� xuyunhan
    * �������䣺271147505@qq.com
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
    void createPreviewImage(Ogre::String widgetName, Ogre::String selectedName);

    /*******************************************************************
    * �������ƣ�replaceEntity
    * ��    �ܣ��滻ʵ������ģ��
    * ��    ����2�������滻��ʵ��ָ�룬��ʵ������ģ������
    * �� �� ֵ�� void
    * ��    �ߣ� xuyunhan
    * �������䣺271147505@qq.com
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    void replaceEntity(Ogre::Entity *&entyReplaced, Ogre::String newEntyName);

    void clearEntityPoint();

    bool getIsSingleReady()
    {
        return this->isSingleReady;
    }
    void  setIsSingleReady(bool tempBool)
    {
        this->isSingleReady = tempBool;
    }
    bool getIsOnGame()
    {
        return this->isOnGame;
    }
    void  setIsOnGame(bool tempBool)
    {
        this->isOnGame = tempBool;
    }

    bool getIsMutiReady()
    {
        return this->isMutiReady;
    }
    void  setIsMutiReady(bool tempBool)
    {
        this->isMutiReady = tempBool;
    }
    bool getIsMutiOtherReady()
    {
        return this->isMutiOtherReady;
    }
    void  setIsMutiOtherReady(bool tempBool)
    {
        this->isMutiOtherReady = tempBool;
    }

    bool getIsHaveOtherRole()
    {
        return this->isHaveOtherRole;
    }
    void  setIsHaveOtherRole(bool tempBool)
    {
        this->isHaveOtherRole = tempBool;
    }




private:

    //����renderwindow���е����꣬���Ե�������ؼ���ʾλ��
    int mVerticalCenter;
    int mHorizontalCenter;


    //OgreSDKTray�ļ�����������buttonhit����Ϣ���ڴ�
    DancingGuiLisener *mDancingGuiLisener;


    //��ǰ�����״̬����������һ������
    WidgetType mCurrentWidgetType;

    bool isCurrentTypeChanged;


    //��OGRE�����򴫹����ı���
    OgreBites::SdkTrayManager *mTrayMgr;//���ڹ�������
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

    //xuyunhan
    //���������ʵ���ָ��,�������㻻װ
    Ogre::Entity *entyHair;
    Ogre::Entity *entyForWomanLongHair;
    Ogre::Entity *entyUp;
    Ogre::Entity *entyDown;
    Ogre::Entity *entyShoes_L;
    Ogre::Entity *entyShoes_R;

    bool isSingleReady;
    bool isOnGame;
    bool isMutiReady;
    bool isMutiOtherReady;
    bool isHaveOtherRole;

};
#endif