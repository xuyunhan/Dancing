//#include "Dancing.h"
#include "DancingGuiSys.h"
#include "ClientConnect.h"
#include "Ogre.h"
#include "OgrePlugin.h"



int print_result_cb(void *data, int n_columns, char **column_values, char **column_names);
void print_row(int n_values, char **values);
DancingGuiSys::DancingGuiSys(void)
{
    mParseXml = new ParseXml();
    mParseXml->clearConfigFile();

    m_gameStyle = 1;//Ĭ�ϵ���ģʽ

    mCurrentWidgetType = BaseState;//Ĭ�Ͻ���״̬
    this->isCurrentTypeChanged = true;

    this->ConfigGuiInfo();//����mMap

    this->mDancingGuiLisener = new DancingGuiLisener();

    //xuyunhan
    //��ʼ��ʵ�����ָ��
    entyHair = NULL;
    entyForWomanLongHair = NULL;
    entyUp = NULL;
    entyDown = NULL;
    entyShoes_R = NULL;
    entyShoes_L = NULL;

    isSingleReady = false;
    isOnGame = false;


    isMutiReady = false;
    isMutiOtherReady = false;
    isHaveOtherRole = false;
}
//for singleton
DancingGuiSys *DancingGuiSys::instance = NULL;
DancingGuiSys *DancingGuiSys::GetInstance()
{
    if(instance == NULL)
    {
        instance = new DancingGuiSys();
    }
    return instance;
}
//end for singleton
DancingGuiSys::~DancingGuiSys(void)
{
}
void DancingGuiSys::setWidgetGameStart()
{

    this->mCurrentWidgetType = GameStart;
	if (this->m_gameStyle == 2)
	{
		this->isCurrentTypeChanged = true;
	}
    //this->isCurrentTypeChanged = true;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

    //��ʼ��һ�±���Ŀؼ�

    //licorice
    //׼����ť
    Button *readyGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Ready", Ogre::DisplayString(L"׼��"), 100);
    readyGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 105);
    this->mWidget_vec.push_back(readyGame);


    //��ϰ��ť���貽��ѧ��
    Button *studyGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Practise", Ogre::DisplayString(L"��ϰ"), 100);
    studyGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 155);
    this->mWidget_vec.push_back(studyGame);


    //�˳���ť
    Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Quit", Ogre::DisplayString(L"�˳���Ϸ"), 100);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 205);
    this->mWidget_vec.push_back(quitGame);


    //��������������Ϸ����(�����ťֻ�����ڵ���ģʽ�в���)
    if(this->m_gameStyle == 1)
    {
        Button *setGame = mTrayMgr->createButton(OgreBites::TL_NONE, "SetGame", Ogre::DisplayString(L"����"), 100);
        setGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 255);
        this->mWidget_vec.push_back(setGame);
    }

    //��������ѡ�񷿼����(�����ťֻ�����ھ������в���)
    if(this->m_gameStyle == 2)
    {
        Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "SelectHouse", Ogre::DisplayString(L"����"), 100);
        selectHouse->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 255);
        this->mWidget_vec.push_back(selectHouse);
    }


    //��Ϸ�ж�������������Ʒ���DancingHandleSys���У�����DancingHandleSys�Ķ���
    //DancingHandleSys *temp = new DancingHandleSys();
    //������
}
void DancingGuiSys::setWidgetAboutMe()
{
    mTrayMgr->showOkDialog(Ogre::DisplayString(L"��������"), Ogre::DisplayString("tell me about you"));
}
void DancingGuiSys::setWidgetGameOver()
{
    mRoot->queueEndRendering();
}
void DancingGuiSys::setWidgetBaseState()
{
    this->mCurrentWidgetType = BaseState;
    this->isCurrentTypeChanged = true;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

    //��ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(120, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(startGame);


    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(120, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 65);
    this->mWidget_vec.push_back(quitGame);

    //�������� ��ť
    OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE, "AboutUs", Ogre::DisplayString(L"��������"), 100);
    aboutUs->getOverlayElement()->setDimensions(120, 50);
    aboutUs->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 125);
    this->mWidget_vec.push_back(aboutUs);


}

void DancingGuiSys::setWidgetGameSet()
{
    this->mCurrentWidgetType = GameSet;
    this->isCurrentTypeChanged = true;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

    //����
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"����"));
    l_danceStyle->getOverlayElement()->setDimensions(100, 50);
    l_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 225);
    this->mWidget_vec.push_back(l_danceStyle);

    Ogre::StringVector danceStyle;
    //danceStyle.push_back(Ogre::DisplayString(L"Latin"));
    danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
    SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(180, 50);
    s_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 235);
    this->mWidget_vec.push_back(s_danceStyle);

    //���⿪ʼ������������б���û��Ӧ�ˣ�
    //����
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"����"));
    l_danceSong->getOverlayElement()->setDimensions(100, 50);
    l_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 145);
    this->mWidget_vec.push_back(l_danceSong);

    Ogre::StringVector danceSong;
    danceSong.push_back(Ogre::DisplayString("pretty"));
    //danceSong.push_back(Ogre::DisplayString("Young For You"));
    //danceSong.push_back(Ogre::DisplayString(L"��Q"));
    SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceSong);
    s_danceSong->getOverlayElement()->setDimensions(180, 50);
    s_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 155);
    this->mWidget_vec.push_back(s_danceSong);

    //����
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"����"));
    l_danceScence->getOverlayElement()->setDimensions(100, 50);
    l_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 65);
    this->mWidget_vec.push_back(l_danceScence);

    Ogre::StringVector danceScence;
    danceScence.push_back(Ogre::DisplayString("Street"));
    danceScence.push_back(Ogre::DisplayString("HG"));
    //danceScence.push_back(Ogre::DisplayString(L"���"));
    SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceScence);
    s_danceScence->getOverlayElement()->setDimensions(180, 50);
    s_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 75);
    this->mWidget_vec.push_back(s_danceScence);

    //����Ԥ��
    Label *l_danceView = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceView", Ogre::DisplayString(L"����Ԥ��"));
    l_danceView->getOverlayElement()->setDimensions(100, 50);
    l_danceView->getOverlayElement()->setPosition(this->mHorizontalCenter - 10, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(l_danceView);

    OgreBites::DecorWidget *tempSceneView = mTrayMgr->createDecorWidget(OgreBites::TL_NONE, "temp", "SdkTrays/Street");
    tempSceneView->getOverlayElement()->setPosition(this->mHorizontalCenter - 122, this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(tempSceneView);


    //�޸Ľ�ɫ��ť
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_GameSet", Ogre::DisplayString(L"�޸Ľ�ɫ"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(this->mHorizontalCenter - 142, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(corectRole);

    //ֱ�ӿ�ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_GameSet", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 22, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_GameSet", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter + 98, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(quitGame);

}
void DancingGuiSys::nothing()
{
    //����������󷿼��б�

    TiXmlDocument  myDocument ;

    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    myDocument.SaveFile("houses.xml");


    ConnectManager::GetInstance()->Send("houselist");
}
void DancingGuiSys::setWidgetCreateHouse()
{
    //���������ѡ����ļ�¼
    this->mDancingGuiLisener->clearInfo();


    this->mCurrentWidgetType = CreateHouse;
    this->isCurrentTypeChanged = true;

    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    mWidget_vec.clear();

    //������
    Label  *houseName = mTrayMgr->createLabel(OgreBites::TL_NONE, "HouseName", Ogre::DisplayString(L"��������"), 100);
    this->mWidget_vec.push_back(houseName);
    houseName->getOverlayElement()->setDimensions(120, 30);
    houseName->getOverlayElement()->setPosition(this->mHorizontalCenter - 422, this->mVerticalCenter - 205);

    //��������
    Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceStyle", Ogre::DisplayString(L"��Ϸ����"), 100);
    this->mWidget_vec.push_back(danceStyle);
    danceStyle->getOverlayElement()->setDimensions(120, 30);
    danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 302, this->mVerticalCenter - 205);

    //ʣ����λ
    Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE, "LeftSeats", Ogre::DisplayString(L"ʣ����λ"), 100);
    this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120, 30);
    leftSeats->getOverlayElement()->setPosition(this->mHorizontalCenter - 182, this->mVerticalCenter - 205);

    /**///14����ʾ����ı�ǩ������
    Ogre::StringVector labelString;
    labelString.push_back("house_1");
    labelString.push_back("house_2");
    labelString.push_back("house_3");
    labelString.push_back("house_4");
    labelString.push_back("house_5");
    labelString.push_back("house_6");
    labelString.push_back("house_7");
    labelString.push_back("house_8");
    labelString.push_back("house_9");
    labelString.push_back("house_10");
    labelString.push_back("house_11");
    labelString.push_back("house_12");
    labelString.push_back("house_13");
    labelString.push_back("house_14");


    /*******************************************************************
    * ��    �ܣ�����houses.xml�ļ���̬���ɷ����б����б�����Ӧ������ʾ�������ƻ�����һ�㡿
    * ��    ����
    * �� �� ֵ��
    * ��    �ߣ�fux
    * �������䣺10809148@qq.com
    * ��    �ڣ�2013��3��14��
    *******************************************************************/
    TiXmlDocument myDocument ;//= new TiXmlDocument();
    myDocument.LoadFile("houses.xml");
    //��ø�Ԫ�أ���Persons��
    TiXmlElement *RootElement = myDocument.RootElement();//roles

    TiXmlElement *Person = RootElement->FirstChildElement();

    //��ʱ��vector���������洢14����ʾ����ı�ǩ
    std::vector<OgreBites::Label *> mLabel_vec;
    Ogre::Real pTop = 170;

    for(int i = 0; Person != 0 && i < 14; ++i, Person = Person->NextSiblingElement())
    {

        string temp_str = "  ";
        temp_str += Person->Attribute("name");//+Person->Attribute("dancestyle")+"                "+j;
        temp_str += "              ";
        temp_str += Person->Attribute("dancestyle");
        temp_str += "               ";
        temp_str += Person->Attribute("site");
        //��14����ǩ������ʾ�������Ϣ
        mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE, labelString[i], temp_str, 360));
        mLabel_vec[i]->getOverlayElement()->setDimensions(360, 30);
        mLabel_vec[i]->getOverlayElement()->setPosition(this->mHorizontalCenter - 422, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }



    //��ֱ�߻�������
    OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE, "Se_Cut", 3);
    cutSeparator->getOverlayElement()->setHeight(450);
    cutSeparator->getOverlayElement()->setPosition(this->mHorizontalCenter - 12, this->mVerticalCenter - 205);
    this->mWidget_vec.push_back(cutSeparator);

    //�����µķ���
    //��ǩ
    Button *creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse_hide", Ogre::DisplayString(L"�����·���"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(this->mHorizontalCenter + 38, this->mVerticalCenter - 205);
    this->mWidget_vec.push_back(creatNew);

    //�޸Ľ�ɫ��ť
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_CreateHouse", Ogre::DisplayString(L"�޸Ľ�ɫ"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(this->mHorizontalCenter - 142, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(corectRole);

    //ֱ�ӿ�ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_CreateHouse", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 22, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(startGame);

    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_CreateHouse", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter + 98, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(quitGame);

}
void DancingGuiSys::setWidgetCreateNewHouse()//һ��û��״̬�����ý��溯��
{
    Button *creatNew =  (Button *)mTrayMgr->getWidget("CreatNewHouse_hide");
    creatNew->hide();
    creatNew =  (Button *)mTrayMgr->getWidget("StartGame_CreateHouse");
    creatNew->hide();

    creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse_show", Ogre::DisplayString(L"�����·���"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(this->mHorizontalCenter + 38, 140);
    this->mWidget_vec.push_back(creatNew);


    //�������Ʊ�ǩ
    Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_RoomName", Ogre::DisplayString(L"��������"), 120);
    l_roomName->getOverlayElement()->setDimensions(120, 30);
    l_roomName->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter  - 165);
    this->mWidget_vec.push_back(l_roomName);

    //�������������
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName",  Ogre::DisplayString(L"�����뷿������"), 200, 100);
    mTextBox->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 225 );
    this->mWidget_vec.push_back(mTextBox);


    //����
    //��ǩ
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceStyle->getOverlayElement()->setDimensions(120, 30);
    l_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter - 105);
    this->mWidget_vec.push_back(l_danceStyle);


    //�����б�
    Ogre::StringVector v_danceStyle;
    //v_danceStyle.push_back("Latin");
    v_danceStyle.push_back("QiaQia");
    OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(200, 50);
    s_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 115);
    this->mWidget_vec.push_back(s_danceStyle);


    //����
    //��ǩ
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceSong->getOverlayElement()->setDimensions(120, 30);
    l_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter - 45);
    this->mWidget_vec.push_back(l_danceSong);


    //�����б�
    Ogre::StringVector v_danceSong;
    v_danceSong.push_back("pretty");
    //v_danceSong.push_back("lalala");
    OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceSong);
    s_danceSong->getOverlayElement()->setDimensions(200, 50);
    s_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 55);
    this->mWidget_vec.push_back(s_danceSong);


    //����
    //��ǩ
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceScence->getOverlayElement()->setDimensions(120, 30);
    l_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter + 15);
    this->mWidget_vec.push_back(l_danceScence);


    //�����б�
    Ogre::StringVector v_danceScence;
    v_danceScence.push_back("Street");
    v_danceScence.push_back("HG");
    OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceScence);
    s_danceScence->getOverlayElement()->setDimensions(200, 50);
    s_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(s_danceScence);


    OgreBites::DecorWidget *tempSceneView = mTrayMgr->createDecorWidget(OgreBites::TL_NONE, "temp", "SdkTrays/Street");
    tempSceneView->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 55);
    //����Ԥ��
    // OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceImage", "");
    // l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    // l_danceimage->getOverlayElement()->setDimensions(200, 200);
    //l_danceimage->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(tempSceneView);


    //ȷ��������ť
    Button *create = mTrayMgr->createButton(OgreBites::TL_NONE, "CreateHouse", Ogre::DisplayString(L"ȷ�ϴ���"), 100);
    create->getOverlayElement()->setDimensions(100, 50);
    create->getOverlayElement()->setPosition(this->mHorizontalCenter - 22 , this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(create);
}

void DancingGuiSys::setWidgetPlayVideo()
{
    //������Ƶ
}

//licorice
void DancingGuiSys::setWidgetGamePractise()
{
    //�貽��ϰ�ĳ���
    this->mCurrentWidgetType = GamePractise;
    this->isCurrentTypeChanged = true;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();


    //��ʼ��һЩ����İ�ť
    //������Ƶ
    Button *playVideo = this->mTrayMgr->createButton(OgreBites::TL_NONE, "PlayVideo", Ogre::DisplayString(L"������Ƶ"), 100);
    playVideo->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 205);
    this->mWidget_vec.push_back(playVideo);
    //���ذ�ť
    Button *returnGame = mTrayMgr->createButton(OgreBites::TL_NONE, "ReturnGame", Ogre::DisplayString(L"������Ϸ"), 100);
    returnGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 255);
    this->mWidget_vec.push_back(returnGame);
}



void DancingGuiSys::ConfigGuiInfo()
{
    //BaseState,
    //StartGame  CreateRole
    //QuitGame   GameOver
    //AboutUs
    mPair.first =  BaseState;
    mPair.second = "StartGame";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;
    mPair.first =  BaseState;
    mPair.second = "QuitGame";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;
    mPair.first =  BaseState;
    mPair.second = "AboutUs";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetAboutMe;

    //CreateRole,
    //createRole_sig   CreateHouse
    //createRole_mut   GameSet
    //StartGame_role  GameStart
    // QuitGame_role   GameOver
    mPair.first =  CreateRole;
    mPair.second = "createRole_sig";
    //this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;
    this->mMap[mPair]  = &DancingGuiSys::nothing;
    mPair.first =  CreateRole;
    mPair.second = "createRole_mut";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;

    mPair.first =  CreateRole;
    mPair.second = "QuitGame_role";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;

    //GameSet,
    //CorectRole_GameSet  CreateRole
    //StartGame_GameSet  GameStart
    //QuitGame_GameSet   GameOver
    mPair.first =  GameSet;
    mPair.second = "CorectRole_GameSet";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;
    mPair.first =  GameSet;
    mPair.second = "StartGame_GameSet";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
    mPair.first =  GameSet;
    mPair.second = "QuitGame_GameSet";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;



    //CreateHouse,
    //CorectRole_CreateHouse  CreateRole
    //StartGame_CreateHouse  GameStart
    //QuitGame_CreateHouse   GameOver
    mPair.first =  CreateHouse;
    mPair.second = "CorectRole_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;
    mPair.first =  CreateHouse;
    mPair.second = "StartGame_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
    mPair.first =  CreateHouse;
    mPair.second = "CreateHouse";//ȷ�ϴ������䰴ť
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
    mPair.first =  CreateHouse;
    mPair.second = "QuitGame_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;
    mPair.first =  CreateHouse;
    mPair.second = "CreatNewHouse_hide";//����������Ϣ����ʱ�İ�ť
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateNewHouse;
    mPair.first =  CreateHouse;
    mPair.second = "CreatNewHouse_show";
    this->mMap[mPair]  = &DancingGuiSys::nothing;

    //GameStart,
    //Quit                    GameOver
    //SetGame  1             GameSet
    //SelectHouse 2         CreateHouse
    mPair.first =  GameStart;
    mPair.second = "Quit";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;
    mPair.first =  GameStart;
    mPair.second = "SetGame";
    //this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;
    this->mMap[mPair]  = &DancingGuiSys::nothing;
    mPair.first =  GameStart;
    mPair.second = "SelectHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;

    mPair.first = GameStart;
    mPair.second = "Ready";
    this->mMap[mPair] = &DancingGuiSys::setWidgetGameReady;

    //licorice
    mPair.first = GameStart;
    mPair.second = "Practise";
    this->mMap[mPair] = &DancingGuiSys::setWidgetGamePractise;
    //GameOver,

    //licorice
    //GamePractise
    mPair.first = GamePractise;
    mPair.second = "ReturnGame";
    this->mMap[mPair] = &DancingGuiSys::setWidgetGameStart;

    mPair.first = GamePractise;
    mPair.second = "PlayVideo";
    this->mMap[mPair] = &DancingGuiSys::setWidgetPlayVideo;
    //GameOver,

}

void DancingGuiSys::setTrayMgr(SdkTrayManager *tempTrayMgr)
{
    this->mTrayMgr = tempTrayMgr;
    //����
    this->mDancingGuiLisener->setTrayMgr(mTrayMgr);
}
void DancingGuiSys::setRoot(Ogre::Root *tempRoot)
{
    this->mRoot = tempRoot;
}

bool DancingGuiSys::keyPressed( const OIS::KeyEvent &arg )
{
    if (this->mCurrentWidgetType == CreateRole || this->mCurrentWidgetType == CreateHouse)
    {
        if(arg.key == OIS::KC_A) mTextBox->setText(mTextBox->getText() + "a");
        if(arg.key == OIS::KC_B) mTextBox->setText(mTextBox->getText() + "b");
        if(arg.key == OIS::KC_C) mTextBox->setText(mTextBox->getText() + "c");
        if(arg.key == OIS::KC_D) mTextBox->setText(mTextBox->getText() + "d");
        if(arg.key == OIS::KC_E) mTextBox->setText(mTextBox->getText() + "e");
        if(arg.key == OIS::KC_F) mTextBox->setText(mTextBox->getText() + "f");
        if(arg.key == OIS::KC_G) mTextBox->setText(mTextBox->getText() + "g");
        if(arg.key == OIS::KC_H) mTextBox->setText(mTextBox->getText() + "h");
        if(arg.key == OIS::KC_I) mTextBox->setText(mTextBox->getText() + "i");
        if(arg.key == OIS::KC_J) mTextBox->setText(mTextBox->getText() + "j");
        if(arg.key == OIS::KC_K) mTextBox->setText(mTextBox->getText() + "k");
        if(arg.key == OIS::KC_L) mTextBox->setText(mTextBox->getText() + "l");
        if(arg.key == OIS::KC_M) mTextBox->setText(mTextBox->getText() + "m");
        if(arg.key == OIS::KC_N) mTextBox->setText(mTextBox->getText() + "n");
        if(arg.key == OIS::KC_O) mTextBox->setText(mTextBox->getText() + "o");
        if(arg.key == OIS::KC_P) mTextBox->setText(mTextBox->getText() + "p");
        if(arg.key == OIS::KC_Q) mTextBox->setText(mTextBox->getText() + "q");
        if(arg.key == OIS::KC_R) mTextBox->setText(mTextBox->getText() + "r");
        if(arg.key == OIS::KC_S) mTextBox->setText(mTextBox->getText() + "s");
        if(arg.key == OIS::KC_T) mTextBox->setText(mTextBox->getText() + "t");
        if(arg.key == OIS::KC_U) mTextBox->setText(mTextBox->getText() + "u");
        if(arg.key == OIS::KC_V) mTextBox->setText(mTextBox->getText() + "v");
        if(arg.key == OIS::KC_W) mTextBox->setText(mTextBox->getText() + "w");
        if(arg.key == OIS::KC_X) mTextBox->setText(mTextBox->getText() + "x");
        if(arg.key == OIS::KC_Y) mTextBox->setText(mTextBox->getText() + "y");
        if(arg.key == OIS::KC_Z) mTextBox->setText(mTextBox->getText() + "z");
    }
    return true;
}
bool DancingGuiSys::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}


