#include "DancingGuiSys.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

int print_result_cb(void *data, int n_columns, char **column_values, char **column_names);
void print_row(int n_values, char **values);
DancingGuiSys::DancingGuiSys(void)
{
}

DancingGuiSys::~DancingGuiSys(void)
{
}

//���ﴫ�������������ڶ���������Ϊ�˿�����Ϸ�˳�
DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *mRoot,Ogre::RenderWindow *mWindow)
{

    mParseXml = new ParseXml();
    // mParseXml->inputRolesFile();
    //mParseXml->readRolesFile();


    this->mTrayMgr = sdktraymanager;
    this->mRoot = mRoot;
	this->mWindow = mWindow;
    //Ĭ�ϵ���ģʽ
    m_gameStyle = 1;
	//Ĭ�Ͽ�ͨ����
	m_roleStyle = 1;

	//Ĭ��û���ķ���
	isNewHouse = false;
    //Ĭ��״̬
    mCurrentWidgetType = BaseState;
   // this->ConfigGuiInfo();

//xuyunhan
	//��ʼ��ʵ�����ָ��
	entyHair = NULL;
	entyForWomanLongHair = NULL;
	entyUp = NULL;
	entyDown = NULL;
	entyShoes_R = NULL;
	entyShoes_L = NULL;
}
void DancingGuiSys::setWidgetGameStart()
{
    this->mCurrentWidgetType = GameStart;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

    //��ʼ��һ�±���Ŀؼ�
	Ogre::Real left = 900;
	Ogre::Real top =  450;

	if(this->mWindow->isFullScreen())
	{  
		left = mWindow->getWidth()-100;
		top = mWindow->getHeight()-300;

		Ogre::Quaternion str;
		str.w = left + 100;
		str.x = top + 300;
		str.y = str.z = 0;

		Ogre::StringConverter temp;
		temp.toString(str);

		Label *test = mTrayMgr->createLabel(OgreBites::TL_NONE,"teststr",temp.toString(str),150);
		test->getOverlayElement()->setPosition(900,300);
	}
	//licorice
	//׼����ť
	Button *readyGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Ready",Ogre::DisplayString(L"׼��"),100);
	readyGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(readyGame);
	top += 50;

	//��ϰ��ť���貽��ѧ��
	Button *studyGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Practise",Ogre::DisplayString(L"��ϰ"),100);
	studyGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(studyGame);
	top += 50;

    //�˳���ť
    Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Quit", Ogre::DisplayString(L"�˳���Ϸ"), 100);
    quitGame->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(quitGame);
	top += 50;

    //��������������Ϸ����(�����ťֻ�����ڵ���ģʽ�в���)
    if(this->m_gameStyle == 1)
    {
        Button *setGame = mTrayMgr->createButton(OgreBites::TL_NONE, "SetGame", Ogre::DisplayString(L"����"), 100);
        setGame->getOverlayElement()->setPosition(left, top);
        this->mWidget_vec.push_back(setGame);
    }

    //��������ѡ�񷿼����(�����ťֻ�����ھ������в���)
    if(this->m_gameStyle == 2)
    {
        Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "SelectHouse", Ogre::DisplayString(L"����"), 100);
        selectHouse->getOverlayElement()->setPosition(left, top);
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
//licorice
void DancingGuiSys::setWidgetPlayVideo()
{
	//������Ƶ
}
//licorice
void DancingGuiSys::setWidgetGameReady()
{   
	mTrayMgr->showOkDialog(Ogre::DisplayString(L"����ʱ��ʼ"),Ogre::DisplayString("5"));
	//����ʱ
}
//licorice
void DancingGuiSys::setWidgetGamePractise()
{
	//�貽��ϰ�ĳ���
	this->mCurrentWidgetType = GamePractise;
    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

	Ogre::Real left = 900;
	Ogre::Real top = 550;

	//��ʼ��һЩ����İ�ť
	//������Ƶ
	Button *playVideo = this->mTrayMgr->createButton(OgreBites::TL_NONE,"PlayVideo",Ogre::DisplayString(L"������Ƶ"),100);
	playVideo->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(playVideo);
	top += 50;
	//���ذ�ť
	Button *returnGame = mTrayMgr->createButton(OgreBites::TL_NONE,"ReturnGame",Ogre::DisplayString(L"������Ϸ"),100);
	returnGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(returnGame);
}
void DancingGuiSys::setWidgetBaseState()
{
    this->mCurrentWidgetType = BaseState;
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
    startGame->getOverlayElement()->setPosition(450, 350);
    this->mWidget_vec.push_back(startGame);


    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(120, 50);
    quitGame->getOverlayElement()->setPosition(450, 410);
    this->mWidget_vec.push_back(quitGame);

    //�������� ��ť
    OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE, "AboutUs", Ogre::DisplayString(L"��������"), 100);
    aboutUs->getOverlayElement()->setDimensions(120, 50);
    aboutUs->getOverlayElement()->setPosition(450, 470);
    this->mWidget_vec.push_back(aboutUs);
}
void DancingGuiSys::setWidgetCreateNewHouse()
{
	isNewHouse = true;
	  //������¼λ�õı���
    Ogre::Real left, top;
    left = 600;
    top = 180;

    //�������Ʊ�ǩ
    Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_RoomName", Ogre::DisplayString(L"��������"), 120);
    l_roomName->getOverlayElement()->setDimensions(120, 30);
    l_roomName->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_roomName);
    top -= 10;
    left += 120;//left 670,top 130
    //�������������
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName",  Ogre::DisplayString(L"�����뷿������"), 200, 100);
    mTextBox->getOverlayElement()->setPosition(left, top - 50 );
    // mTextBox->setText( Ogre::DisplayString(L"riririirirllllllll"));
    this->mWidget_vec.push_back(mTextBox);
    //mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName", Ogre::DisplayString(L"�����뷿������"), 200, 70);
    //mTextBox->getOverlayElement()->setPosition(left, top-20);
    //this->mWidget_vec.push_back(mTextBox);
    left -= 120;
    top  += 70;//left 550,top 180

    //����
    //��ǩ
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceStyle->getOverlayElement()->setDimensions(120, 30);
    l_danceStyle->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceStyle);
    left += 120;
    top -= 10;//left 670,top 170

    //�����б�
    Ogre::StringVector v_danceStyle;
    v_danceStyle.push_back("Latin");
    v_danceStyle.push_back("QiaQia");
    OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(200, 50);
    s_danceStyle->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceStyle);
    left -= 120;
    top  += 70;//left 550,top 220

    //����
    //��ǩ
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceSong->getOverlayElement()->setDimensions(120, 30);
    l_danceSong->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceSong);
    left += 120;
    top  -= 10;//left 670,top 210

    //�����б�
    Ogre::StringVector v_danceSong;
    v_danceSong.push_back("pretty");
    v_danceSong.push_back("lalala");
    OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceSong);
    s_danceSong->getOverlayElement()->setDimensions(200, 50);
    s_danceSong->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceSong);
    left -= 120;
    top  += 70;//left 550,top 260

    //����
    //��ǩ
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"����ѡ��"), 120);
    l_danceScence->getOverlayElement()->setDimensions(120, 30);
    l_danceScence->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceScence);
    left += 120;
    top  -= 10;//left 670,top 250

    //�����б�
    Ogre::StringVector v_danceScence;
    v_danceScence.push_back("seaside");
    v_danceScence.push_back("roadway");
    OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"����ѡ��"), 200, 5, v_danceScence);
    s_danceScence->getOverlayElement()->setDimensions(200, 50);
    s_danceScence->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceScence);

    top  += 50;//left 670,top 300
    //����Ԥ��
    OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceImage", "");
    l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    l_danceimage->getOverlayElement()->setDimensions(200, 200);
    l_danceimage->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceimage);
	left -= 120;
	top += 150;

	//ȷ��������ť
	//��ע���ˣ��о����Բ�Ҫ����Ϊ��ʼ��Ϸ���൱��ȷ�������һ�����
	/*Button *create = mTrayMgr->createButton(OgreBites::TL_NONE,"CertainCreate",Ogre::DisplayString(L"ȷ��"),100);
	create->getOverlayElement()->setDimensions(100,50);
	create->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(create);*/
}

void DancingGuiSys::setWidgetGameSet()
{
    this->mCurrentWidgetType = GameSet;
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
    l_danceStyle->getOverlayElement()->setPosition(400, 120);
    this->mWidget_vec.push_back(l_danceStyle);

    Ogre::StringVector danceStyle;
    danceStyle.push_back(Ogre::DisplayString(L"Latin"));
    danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
    SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(180, 50);
    s_danceStyle->getOverlayElement()->setPosition(505, 110);
    this->mWidget_vec.push_back(s_danceStyle);

    //���⿪ʼ������������б���û��Ӧ�ˣ�
    //����
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"����"));
    l_danceSong->getOverlayElement()->setDimensions(100, 50);
    l_danceSong->getOverlayElement()->setPosition(400, 200);
    this->mWidget_vec.push_back(l_danceSong);

    Ogre::StringVector danceSong;
    danceSong.push_back(Ogre::DisplayString("SanFrancisco"));
    danceSong.push_back(Ogre::DisplayString("Young For You"));
    danceSong.push_back(Ogre::DisplayString(L"��Q"));
    SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceSong);
    s_danceSong->getOverlayElement()->setDimensions(180, 50);
    s_danceSong->getOverlayElement()->setPosition(505, 190);
    this->mWidget_vec.push_back(s_danceSong);

    //����
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"����"));
    l_danceScence->getOverlayElement()->setDimensions(100, 50);
    l_danceScence->getOverlayElement()->setPosition(400, 280);
    this->mWidget_vec.push_back(l_danceScence);

    Ogre::StringVector danceScence;
    danceScence.push_back(Ogre::DisplayString("Sea"));
    danceScence.push_back(Ogre::DisplayString("Road"));
    danceScence.push_back(Ogre::DisplayString(L"���"));
    SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"��ѡ��"), 180, 10, danceScence);
    s_danceScence->getOverlayElement()->setDimensions(180, 50);
    s_danceScence->getOverlayElement()->setPosition(505, 270);
    this->mWidget_vec.push_back(s_danceScence);

    //����Ԥ��
    Label *l_danceView = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceView", Ogre::DisplayString(L"����Ԥ��"));
    l_danceView->getOverlayElement()->setDimensions(100, 50);
    l_danceView->getOverlayElement()->setPosition(502, 350);
    this->mWidget_vec.push_back(l_danceView);

    OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceImage", "");
    l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    l_danceimage->getOverlayElement()->setDimensions(200, 200);
    l_danceimage->getOverlayElement()->setPosition(450, 400);
    l_danceimage->show();
    this->mWidget_vec.push_back(l_danceimage);


    //�޸Ľ�ɫ��ť
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_GameSet", Ogre::DisplayString(L"�޸Ľ�ɫ"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(370, 620);
    this->mWidget_vec.push_back(corectRole);

    //ֱ�ӿ�ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_GameSet", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(490, 620);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_GameSet", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(610, 620);
    this->mWidget_vec.push_back(quitGame);



}
void DancingGuiSys::setWidgetCreateHouse()
{

    this->mCurrentWidgetType = CreateHouse;

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
    houseName->getOverlayElement()->setPosition(90, 140);

    //��������
    Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceStyle", Ogre::DisplayString(L"��Ϸ����"), 100);
    this->mWidget_vec.push_back(danceStyle);
    danceStyle->getOverlayElement()->setDimensions(120, 30);
    danceStyle->getOverlayElement()->setPosition(210, 140);

    //ʣ����λ
    Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE, "LeftSeats", Ogre::DisplayString(L"ʣ����λ"), 100);
    this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120, 30);
    leftSeats->getOverlayElement()->setPosition(330, 140);

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
    TiXmlDocument *myDocument = new TiXmlDocument("houses.xml");
    myDocument->LoadFile();
    //��ø�Ԫ�أ���Persons��
    TiXmlElement *RootElement = myDocument->RootElement();//roles

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
        mLabel_vec[i]->getOverlayElement()->setPosition(90, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }







    /*for(int i = 0; i < 14; i++)
    {
        //��14����ǩ������ʾ�������Ϣ
        mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE, labelString[i], "", 360));
        mLabel_vec[i]->getOverlayElement()->setDimensions(360, 30);
        mLabel_vec[i]->getOverlayElement()->setPosition(90, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }*/

    //��ֱ�߻�������
    OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE, "Se_Cut", 3);
    cutSeparator->getOverlayElement()->setHeight(450);
    cutSeparator->getOverlayElement()->setPosition(500, 140);
    this->mWidget_vec.push_back(cutSeparator);


    //�����µķ���
    //��ǩ
    Button *creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse", Ogre::DisplayString(L"�����·���"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(550, 140);
    this->mWidget_vec.push_back(creatNew);
	
	if(isNewHouse)
	{
		setWidgetCreateNewHouse();
	}
    //�޸Ľ�ɫ��ť
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_CreateHouse", Ogre::DisplayString(L"�޸Ľ�ɫ"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(370, 620);
    this->mWidget_vec.push_back(corectRole);

    //ֱ�ӿ�ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_CreateHouse", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(490, 620);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_CreateHouse", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(610, 620);
    this->mWidget_vec.push_back(quitGame);

}//startgame createhouse createrole gameset housed



WidgetType DancingGuiSys::getCurrentWidgetType()
{
    return this->mCurrentWidgetType;
}
void DancingGuiSys::setCurrentWidgetType()
{
}


void DancingGuiSys::buttonHit(Button *button)
{


    if(button == NULL)
        return;

	//licoriceÿ����Ӧ��ť��configһ�Σ��Է������ظ��İ�ť
	this->mMap.clear();
	this->ConfigGuiInfo();

	//////////////////////////////////////////////////////
    mPair.first = this->mCurrentWidgetType;
    mPair.second = button->getName();
    functionPoint temp = this->mMap[mPair];
    (this->*temp)();

}

int print_result_cb(void *data, int n_columns, char **column_values, char **column_names)
{
    static int column_names_printed = 0;
    if (!column_names_printed)
    {
        print_row(n_columns, column_names);
        column_names_printed = 1;
    }
    print_row(n_columns, column_values);
    return 0;
}
void print_row(int n_values, char **values)
{
    int i;
    for (i = 0; i < n_values; ++i)
    {
        if (i > 0)
        {
            printf("\t");
        }
        printf("%s", values[i]);
    }
    printf("\n");
}
void DancingGuiSys::itemSelected(SelectMenu *menu)
{
	 /*S_Hair
    S_Rings
    S_Shangzhuang
    S_Xiazhuang
    S_Shoes*/
    if (menu->getName() == "S_Hair"  ||
            menu->getName() == "S_Rings" ||
            menu->getName() == "S_Shangzhuang" ||
            menu->getName() == "S_Xiazhuang" ||
            menu->getName() == "S_Shoes" )
    {
        this->changgeScene(menu->getName() );
    }
}
void DancingGuiSys::labelHit(Label *label)
{
}
void DancingGuiSys::sliderMoved(Slider *slider)
{
}
void DancingGuiSys::checkBoxToggled(CheckBox *box)
{
    if(box == NULL)
		return;
	
	Ogre::String boxName = box->getName();	

	//box->setChecked(true);
	//��checkbox�����жϣ�ʵ��������ֻ�ܵ��һ���Լ�������һ����ѡ��
	if(boxName == Ogre::String("Box_Single"))
	{   
		//����Ϊ����ģʽ
		this->m_gameStyle = 1;
		
		//licorice
		//ת��������ʾ�ĸ�������ɫ��ť,��������ʾ�����Ĵ�����ɫ��ť
		for(unsigned int i = 0;i < this->mWidget_vec.size();i++)
		{
			if(this->mWidget_vec.at(i)->getName() == "createRole_sig")
			{	
				this->mWidget_vec.at(i+1)->hide();
				this->mWidget_vec.at(i)->show();
			}
		}

		this->multiBox->setChecked(false,false);
		this->singleBox->setChecked(true,false);
	}
	else if(boxName == Ogre::String("Box_Multi"))
	{  
		//����Ϊ������ģʽ
		this->m_gameStyle = 2;
		
		//licorice
		//ת��������ʾ�ĸ�������ɫ��ť
		for(unsigned int i = 0;i < this->mWidget_vec.size();i++)
		{
			if(this->mWidget_vec.at(i)->getName() == "createRole_mut")
			{	
				this->mWidget_vec.at(i-1)->hide();
				this->mWidget_vec.at(i)->show();
			}
		}

		this->singleBox->setChecked(false,false);
		this->multiBox->setChecked(true,false);
	}
	else if(boxName == Ogre::String("C_SexM"))
	{
		//������
		//������ʾ�������󣬺�����δ���
					
		this->femaleBox->setChecked(false,false);
		this->maleBox->setChecked(true,false);
		this->changgeScene(box->getName() );
		
		
	}
	else if(boxName == Ogre::String("C_SexF"))
	{
		//������
		//������ʾŮ�����󣬺�����δ���
		
			this->maleBox->setChecked(false,false);
			this->femaleBox->setChecked(true,false);
			this->changgeScene(box->getName() );
			
	
	}
	else if(boxName == Ogre::String("Cartoon_Role"))
	{   
		this->m_roleStyle = 1;
		//����ͨ����
		this->role_real->setChecked(false,false);
		this->role_cartoon->setChecked(true,false);
		
		//��Ӧ�Ĳ���
		
	}
	else if(boxName == Ogre::String("Real_Role"))
	{   
		this->m_roleStyle = 2;
		//����ʵʱ��ģ
		
			//��Ӧ�Ĳ���
			//this->setRealRoleValue();
		
		this->role_cartoon->setChecked(false,false);
		this->role_real->setChecked(true,false);
	}	

}
void DancingGuiSys::okDialogClosed(const Ogre::DisplayString &message)
{
}
void DancingGuiSys::yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit)
{
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
	this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;
    
    mPair.first =  CreateRole;
    mPair.second = "createRole_mut";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;

	//licorice ��Ҫ��ʼ��ť����Ӧ
    /*mPair.first =  CreateRole;
    mPair.second = "StartGame_role";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;*/

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
    mPair.second = "QuitGame_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;

	//licorice ���Ѿ������˺󣬲����ٴ���
	mPair.first = CreateHouse;
	mPair.second = "CreatNewHouse";
	if(!isNewHouse)//�Ѿ�����˴����·��䰴ť��û�оʹ���
	{	
	    this->mMap[mPair] = &DancingGuiSys::setWidgetCreateNewHouse;
	}
	else
	{
		this->mMap[mPair] = &DancingGuiSys::setWidgetCreateHouse;
	}
	

    //GameStart,
    //Quit                    GameOver
    //SetGame  1             GameSet
    //SelectHouse 2         CreateHouse
	//Reay                   GameStart
	mPair.first = GameStart;
	mPair.second = "Ready";
	this->mMap[mPair] = &DancingGuiSys::setWidgetGameReady;

	//licorice
	mPair.first = GameStart;
	mPair.second = "Practise";
	this->mMap[mPair] = &DancingGuiSys::setWidgetGamePractise;

    mPair.first =  GameStart;
    mPair.second = "Quit";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;
    mPair.first =  GameStart;
    mPair.second = "SetGame";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;
    mPair.first =  GameStart;
    mPair.second = "SelectHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;

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


bool DancingGuiSys::mouseMoved( const OIS::MouseEvent &arg )
{
    return true;
}
bool DancingGuiSys::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if (this->mTextBox->i_cursorPressed())
    {
        int i = 1;
        i += 1;

    }
    return true;
}
bool DancingGuiSys::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    return true;
}

bool DancingGuiSys::keyPressed( const OIS::KeyEvent &arg )
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



    return true;
}
bool DancingGuiSys::keyReleased( const OIS::KeyEvent &arg )
{
    return true;
}


