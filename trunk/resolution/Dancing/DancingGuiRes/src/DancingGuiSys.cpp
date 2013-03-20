#include "DancingGuiSys.h"
#include "ClientConnect.h"
#include "Ogre.h"
#include "OgrePlugin.h"
int print_result_cb(void *data, int n_columns, char **column_values, char **column_names);
void print_row(int n_values, char **values);
DancingGuiSys::DancingGuiSys(void)
{
}

DancingGuiSys::~DancingGuiSys(void)
{
}

//���ﴫ�������������ڶ���������Ϊ�˿�����Ϸ�˳�
DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *temproot, Ogre::RenderWindow *tempindow)
{

    mParseXml = new ParseXml();
    mParseXml->clearConfigFile();

    // mParseXml->inputRolesFile();
    //mParseXml->readRolesFile();


    this->mTrayMgr = sdktraymanager;
    this->mRoot = temproot;
    this->mWindow = tempindow;
    //Ĭ�ϵ���ģʽ
    m_gameStyle = 1;
    //Ĭ��״̬
    mCurrentWidgetType = BaseState;
    mWillHouse = "";
    this->ConfigGuiInfo();

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
    //�˳���ť
    Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Quit", Ogre::DisplayString(L"�˳���Ϸ"), 100);
    quitGame->getOverlayElement()->setPosition(900, 550);
    this->mWidget_vec.push_back(quitGame);

    //��������������Ϸ����(�����ťֻ�����ڵ���ģʽ�в���)
    if(this->m_gameStyle == 1)
    {
        Button *setGame = mTrayMgr->createButton(OgreBites::TL_NONE, "SetGame", Ogre::DisplayString(L"����"), 100);
        setGame->getOverlayElement()->setPosition(900, 600);
        this->mWidget_vec.push_back(setGame);
    }

    //��������ѡ�񷿼����(�����ťֻ�����ھ������в���)
    if(this->m_gameStyle == 2)
    {
        Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "SelectHouse", Ogre::DisplayString(L"����"), 100);
        selectHouse->getOverlayElement()->setPosition(900, 600);
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
void DancingGuiSys::nothing()
{
    //����������󷿼��б�

    TiXmlDocument  myDocument ;

    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    myDocument.SaveFile("houses.xml");

    //Sleep(3000);

    ConnectManager::GetInstance()->Send("houselist");


}
void DancingGuiSys::setWidgetCreateHouse()
{

    mWillHouse = "";//��ѡ����Ϊ��
    mWillHouseLabelName = "";


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
    Label *creatNew = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_CreatNew", Ogre::DisplayString(L"�����·���"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(550, 140);
    this->mWidget_vec.push_back(creatNew);

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

    //fux add
    OgreBites::Button *creatHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "CreateHouse", Ogre::DisplayString(L"��������"), 100);
    creatHouse->getOverlayElement()->setDimensions(100, 50);
    creatHouse->getOverlayElement()->setPosition(730, 620);
    this->mWidget_vec.push_back(creatHouse);


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
    /*******************************************************************
    * ��    �ܣ������濪ʼ��Ϸ����������䰴ť����Ҫ����һЩ��Ϣ
    *******************************************************************/
    /*******************************************************************
    * ��    �ܣ�����������䰴ť����Ҫ����һЩ��Ϣ,����ϵ����ˣ�newhouse.xml  myhouse.xml
    *******************************************************************/
    if(button->getName() == "CreateHouse"  || button->getName() == "StartGame_GameSet") //�����·������Ϣ
    {
        //����һ��XML���ĵ�����
        TiXmlDocument myDocument ;//= new TiXmlDocument();
        //����һ����Ԫ�ز����ӡ�
        TiXmlElement *RootElement = new TiXmlElement("houses");
        myDocument.LinkEndChild(RootElement);
        //����һ��PersonԪ�ز����ӡ�
        TiXmlElement *PersonElement = new TiXmlElement("house");
        RootElement->LinkEndChild(PersonElement);
        //����PersonԪ�ص����ԡ�

        /*TextBox T_RoomName
        SelectMenu S_DanceStyle
        SelectMenu S_DanceSong
        SelectMenu S_DanceScence*/
        TextBox *tempTextBox ;
        if(button->getName() == "CreateHouse")
        {
            tempTextBox = (TextBox *) this->mTrayMgr->getWidget("T_RoomName");
        }
        SelectMenu *tempSelectMenu1 = (SelectMenu *) this->mTrayMgr->getWidget("S_DanceStyle");
        SelectMenu *tempSelectMenu2 = (SelectMenu *) this->mTrayMgr->getWidget("S_DanceSong");
        SelectMenu *tempSelectMenu3 = (SelectMenu *) this->mTrayMgr->getWidget("S_DanceScence");

        string temp1;
        if(button->getName() == "CreateHouse")
        {
            temp1 = tempTextBox->getText();
        }
        else
        {
            temp1 = "DefaultScene";
        }
        string temp2 = tempSelectMenu1->getSelectedItem();
        string temp3 = tempSelectMenu2->getSelectedItem();
        string temp4 = tempSelectMenu3->getSelectedItem();


        PersonElement->SetAttribute("name", temp1.c_str());
        PersonElement->SetAttribute("dancestyle", temp2.c_str());
        PersonElement->SetAttribute("dancemusic", temp3.c_str());
        PersonElement->SetAttribute("dancescene", temp4.c_str());


        myDocument.SaveFile("myhouse.xml");


        if(button->getName() == "CreateHouse")
        {
            myDocument.SaveFile("newhouse.xml");//���浽�ļ�
            ConnectManager::GetInstance()->Send("newhouse");
        }

    }
    /*******************************************************************
    * ��    �ܣ����汾����ɫ��Ϣ�������ǵ���ģʽ��������ģʽ��ּ�ڱ���role.xml�����跢����������
    *******************************************************************/
    if(button->getName() == "StartGame_role" || button->getName() == "createRole_mut" || button->getName() == "createRole_sig")
    {
        //����һ��XML���ĵ�����
        TiXmlDocument myDocument;// = new TiXmlDocument();
        //����һ����Ԫ�ز����ӡ�
        TiXmlElement *RootElement = new TiXmlElement("roles");
        myDocument.LinkEndChild(RootElement);
        //����һ��PersonԪ�ز����ӡ�
        TiXmlElement *PersonElement = new TiXmlElement("role");
        RootElement->LinkEndChild(PersonElement);

        /*TextBox T_Name
        checkbox C_SexM C_SexF
        SelectMenu S_Hair
        SelectMenu S_Rings
        SelectMenu S_Shangzhuang
        SelectMenu S_Xiazhuang
        SelectMenu S_Shoes*/

        TextBox *tempTextBox = (TextBox *) this->mTrayMgr->getWidget("T_Name");
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("C_SexM");
        SelectMenu *tempSelectMenu1 = (SelectMenu *) this->mTrayMgr->getWidget("S_Hair");
        SelectMenu *tempSelectMenu2 = (SelectMenu *) this->mTrayMgr->getWidget("S_Rings");
        SelectMenu *tempSelectMenu3 = (SelectMenu *) this->mTrayMgr->getWidget("S_Shangzhuang");
        SelectMenu *tempSelectMenu4 = (SelectMenu *) this->mTrayMgr->getWidget("S_Xiazhuang");
        SelectMenu *tempSelectMenu5 = (SelectMenu *) this->mTrayMgr->getWidget("S_Shoes");

        string temp1 = tempTextBox->getText();
        bool temp2 = tempCheckBox->isChecked();
        string temp3 = tempSelectMenu1->getSelectedItem();
        string temp4 = tempSelectMenu2->getSelectedItem();
        string temp5 = tempSelectMenu3->getSelectedItem();
        string temp6 = tempSelectMenu4->getSelectedItem();
        string temp7 = tempSelectMenu5->getSelectedItem();


        PersonElement->SetAttribute("name", temp1.c_str());
        PersonElement->SetAttribute("sex", temp2);
        PersonElement->SetAttribute("hire", temp3.c_str());
        PersonElement->SetAttribute("decorate", temp4.c_str());
        PersonElement->SetAttribute("upware", temp5.c_str());
        PersonElement->SetAttribute("downware", temp6.c_str());
        PersonElement->SetAttribute("shoe", temp7.c_str());

        myDocument.SaveFile("myrole.xml");//���浽�ļ�
    }
    /*******************************************************************
    * ��    �ܣ��˳��û���ϢGameStart->SetGame����� = nothing();   SelectHouse-������
    *******************************************************************/
    if(button->getName() == "SetGame" || button->getName() == "SelectHouse")
    {
        TiXmlDocument myDocument ;
        //myDocument.SaveFile("myhouse.xml");

        if(button->getName() == "SetGame")
        {
            myDocument.SaveFile("otherrole.xml");
            myDocument.SaveFile("newhouse.xml");
            ConnectManager::GetInstance()->Send("logoff");
        }

    }
    /*******************************************************************
    * ��    �ܣ�������Ϸ  CreateHouse->StartGame_CreateHouse
    *******************************************************************/
    if(button->getName() == "StartGame_CreateHouse")
    {
        if(this->mWillHouse != "")
        {
            ConnectManager::GetInstance()->Send("login", this->mWillHouse);
        }
        else
        {
            //fux addû��ѡ�񷿼����ʾ��Ϣ
        }
    }


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
    string tempstring = label->getName();
    const char *tempchar = tempstring.c_str();
    if(tempchar[5]  == '_')
    {
        //��ԭ��һ��������Ķ���
        Label *tempLable = (Label *) this->mTrayMgr->getWidget(mWillHouseLabelName);
        if(tempLable)
        {
            Ogre::Real top = tempLable->getOverlayElement()->getTop();
            Ogre::Real left = tempLable->getOverlayElement()->getLeft();
            tempLable->getOverlayElement()->setPosition(left + 20, top);
        }
        Ogre::Real top = label->getOverlayElement()->getTop();
        Ogre::Real left = label->getOverlayElement()->getLeft();
        label->getOverlayElement()->setPosition(left - 20, top);
        this->mWillHouseLabelName = label->getName();

        //��ȡ������
        {
            string tempstring = label->getCaption();
            const char *tempchar = tempstring.c_str();
            tempstring = "";
            for(int i = 2; tempchar[i] != ' '; ++i)
            {
                tempstring += tempchar[i];
            }
            this->mWillHouse = tempstring;
        }

    }
    //SelectMenu *tempSelectMenu1 = (SelectMenu *) this->mTrayMgr->getWidget("S_DanceStyle");
    //house_
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
    //��checkbox�����жϣ�ʵ��������ֻ�ܵ��һ��
    if(boxName == Ogre::String("Box_Single"))
    {

        this->mTrayMgr->getWidget("createRole_sig")->show();
        this->mTrayMgr->getWidget("createRole_mut")->hide();

        //����Ϊ����ģʽ
        this->m_gameStyle = 1;
        if(box->isChecked())
            this->multiBox->setChecked(false, false);
    }
    else if(boxName == Ogre::String("Box_Multi"))
    {
        this->mTrayMgr->getWidget("createRole_sig")->hide();
        this->mTrayMgr->getWidget("createRole_mut")->show();

        //����Ϊ������ģʽ
        this->m_gameStyle = 2;
        if(box->isChecked())
            this->singleBox->setChecked(false, false);
    }
    else if(boxName == Ogre::String("C_SexM"))
    {



        //������
        //������ʾ�������󣬺�����δ���
        if(box->isChecked())
            this->femaleBox->setChecked(false, false);

        this->changgeScene(box->getName() );
    }
    else if(boxName == Ogre::String("C_SexF"))
    {
        //������
        //������ʾŮ�����󣬺�����δ���
        if(box->isChecked())
            this->maleBox->setChecked(false, false);
        this->changgeScene(box->getName() );
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
    //this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;
    this->mMap[mPair]  = &DancingGuiSys::nothing;
    mPair.first =  CreateRole;
    mPair.second = "createRole_mut";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;
    mPair.first =  CreateRole;
    mPair.second = "StartGame_role";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
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
    mPair.second = "CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
    mPair.first =  CreateHouse;
    mPair.second = "QuitGame_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;

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


