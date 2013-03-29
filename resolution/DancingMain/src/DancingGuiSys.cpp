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

    m_gameStyle = 1;//默认单人模式

    mCurrentWidgetType = BaseState;//默认界面状态
    this->isCurrentTypeChanged = true;

    this->ConfigGuiInfo();//配置mMap

    this->mDancingGuiLisener = new DancingGuiLisener();

    //xuyunhan
    //初始化实体对象指针
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
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

    //初始化一下必须的控件

    //licorice
    //准备按钮
    Button *readyGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Ready", Ogre::DisplayString(L"准备"), 100);
    readyGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 105);
    this->mWidget_vec.push_back(readyGame);


    //练习按钮（舞步教学）
    Button *studyGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Practise", Ogre::DisplayString(L"练习"), 100);
    studyGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 155);
    this->mWidget_vec.push_back(studyGame);


    //退出按钮
    Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Quit", Ogre::DisplayString(L"退出游戏"), 100);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 205);
    this->mWidget_vec.push_back(quitGame);


    //返回重新设置游戏界面(这个按钮只有是在单机模式中才有)
    if(this->m_gameStyle == 1)
    {
        Button *setGame = mTrayMgr->createButton(OgreBites::TL_NONE, "SetGame", Ogre::DisplayString(L"返回"), 100);
        setGame->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 255);
        this->mWidget_vec.push_back(setGame);
    }

    //返回重新选择房间界面(这个按钮只有是在局域网中才有)
    if(this->m_gameStyle == 2)
    {
        Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "SelectHouse", Ogre::DisplayString(L"返回"), 100);
        selectHouse->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 255);
        this->mWidget_vec.push_back(selectHouse);
    }


    //游戏中对人物的其他控制放在DancingHandleSys类中，创建DancingHandleSys的对象
    //DancingHandleSys *temp = new DancingHandleSys();
    //。。。
}
void DancingGuiSys::setWidgetAboutMe()
{
    mTrayMgr->showOkDialog(Ogre::DisplayString(L"关于我们"), Ogre::DisplayString("tell me about you"));
}
void DancingGuiSys::setWidgetGameOver()
{
    mRoot->queueEndRendering();
}
void DancingGuiSys::setWidgetBaseState()
{
    this->mCurrentWidgetType = BaseState;
    this->isCurrentTypeChanged = true;
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

    //开始游戏按钮
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(120, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(startGame);


    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(120, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 65);
    this->mWidget_vec.push_back(quitGame);

    //关于我们 按钮
    OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE, "AboutUs", Ogre::DisplayString(L"关于我们"), 100);
    aboutUs->getOverlayElement()->setDimensions(120, 50);
    aboutUs->getOverlayElement()->setPosition(this->mHorizontalCenter - 62, this->mVerticalCenter + 125);
    this->mWidget_vec.push_back(aboutUs);


}

void DancingGuiSys::setWidgetGameSet()
{
    this->mCurrentWidgetType = GameSet;
    this->isCurrentTypeChanged = true;
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

    //舞种
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"舞种"));
    l_danceStyle->getOverlayElement()->setDimensions(100, 50);
    l_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 225);
    this->mWidget_vec.push_back(l_danceStyle);

    Ogre::StringVector danceStyle;
    //danceStyle.push_back(Ogre::DisplayString(L"Latin"));
    danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
    SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"请选择"), 180, 10, danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(180, 50);
    s_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 235);
    this->mWidget_vec.push_back(s_danceStyle);

    //从这开始，下面的下拉列表点击没反应了！
    //舞曲
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"舞曲"));
    l_danceSong->getOverlayElement()->setDimensions(100, 50);
    l_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 145);
    this->mWidget_vec.push_back(l_danceSong);

    Ogre::StringVector danceSong;
    danceSong.push_back(Ogre::DisplayString("pretty"));
    //danceSong.push_back(Ogre::DisplayString("Young For You"));
    //danceSong.push_back(Ogre::DisplayString(L"阿Q"));
    SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"请选择"), 180, 10, danceSong);
    s_danceSong->getOverlayElement()->setDimensions(180, 50);
    s_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 155);
    this->mWidget_vec.push_back(s_danceSong);

    //场景
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"场景"));
    l_danceScence->getOverlayElement()->setDimensions(100, 50);
    l_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter - 112, this->mVerticalCenter - 65);
    this->mWidget_vec.push_back(l_danceScence);

    Ogre::StringVector danceScence;
    danceScence.push_back(Ogre::DisplayString("Street"));
    danceScence.push_back(Ogre::DisplayString("HG"));
    //danceScence.push_back(Ogre::DisplayString(L"天池"));
    SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"请选择"), 180, 10, danceScence);
    s_danceScence->getOverlayElement()->setDimensions(180, 50);
    s_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter - 7, this->mVerticalCenter - 75);
    this->mWidget_vec.push_back(s_danceScence);

    //场景预览
    Label *l_danceView = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceView", Ogre::DisplayString(L"场景预览"));
    l_danceView->getOverlayElement()->setDimensions(100, 50);
    l_danceView->getOverlayElement()->setPosition(this->mHorizontalCenter - 10, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(l_danceView);

    OgreBites::DecorWidget *tempSceneView = mTrayMgr->createDecorWidget(OgreBites::TL_NONE, "temp", "SdkTrays/Street");
    tempSceneView->getOverlayElement()->setPosition(this->mHorizontalCenter - 122, this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(tempSceneView);


    //修改角色按钮
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_GameSet", Ogre::DisplayString(L"修改角色"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(this->mHorizontalCenter - 142, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(corectRole);

    //直接开始游戏按钮
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_GameSet", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 22, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_GameSet", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter + 98, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(quitGame);

}
void DancingGuiSys::nothing()
{
    //向服务器请求房间列表

    TiXmlDocument  myDocument ;

    TiXmlElement *RootElement = new TiXmlElement("houses");
    myDocument.LinkEndChild(RootElement);
    myDocument.SaveFile("houses.xml");


    ConnectManager::GetInstance()->Send("houselist");
}
void DancingGuiSys::setWidgetCreateHouse()
{
    //清空以往已选房间的记录
    this->mDancingGuiLisener->clearInfo();


    this->mCurrentWidgetType = CreateHouse;
    this->isCurrentTypeChanged = true;

    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    mWidget_vec.clear();

    //房间名
    Label  *houseName = mTrayMgr->createLabel(OgreBites::TL_NONE, "HouseName", Ogre::DisplayString(L"房间名称"), 100);
    this->mWidget_vec.push_back(houseName);
    houseName->getOverlayElement()->setDimensions(120, 30);
    houseName->getOverlayElement()->setPosition(this->mHorizontalCenter - 422, this->mVerticalCenter - 205);

    //舞曲类型
    Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceStyle", Ogre::DisplayString(L"游戏舞种"), 100);
    this->mWidget_vec.push_back(danceStyle);
    danceStyle->getOverlayElement()->setDimensions(120, 30);
    danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter - 302, this->mVerticalCenter - 205);

    //剩余座位
    Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE, "LeftSeats", Ogre::DisplayString(L"剩余座位"), 100);
    this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120, 30);
    leftSeats->getOverlayElement()->setPosition(this->mHorizontalCenter - 182, this->mVerticalCenter - 205);

    /**///14个显示房间的标签的名称
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
    * 功    能：根据houses.xml文件动态生成房间列表【该列表点击后应有所表示，即左移或右移一点】
    * 参    数：
    * 返 回 值：
    * 作    者：fux
    * 电子邮箱：10809148@qq.com
    * 日    期：2013年3月14日
    *******************************************************************/
    TiXmlDocument myDocument ;//= new TiXmlDocument();
    myDocument.LoadFile("houses.xml");
    //获得根元素，即Persons。
    TiXmlElement *RootElement = myDocument.RootElement();//roles

    TiXmlElement *Person = RootElement->FirstChildElement();

    //临时的vector容器用来存储14个显示房间的标签
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
        //把14个标签用来显示房间的信息
        mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE, labelString[i], temp_str, 360));
        mLabel_vec[i]->getOverlayElement()->setDimensions(360, 30);
        mLabel_vec[i]->getOverlayElement()->setPosition(this->mHorizontalCenter - 422, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }



    //竖直线划分区域
    OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE, "Se_Cut", 3);
    cutSeparator->getOverlayElement()->setHeight(450);
    cutSeparator->getOverlayElement()->setPosition(this->mHorizontalCenter - 12, this->mVerticalCenter - 205);
    this->mWidget_vec.push_back(cutSeparator);

    //创建新的房间
    //标签
    Button *creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse_hide", Ogre::DisplayString(L"创建新房间"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(this->mHorizontalCenter + 38, this->mVerticalCenter - 205);
    this->mWidget_vec.push_back(creatNew);

    //修改角色按钮
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_CreateHouse", Ogre::DisplayString(L"修改角色"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(this->mHorizontalCenter - 142, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(corectRole);

    //直接开始游戏按钮
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_CreateHouse", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(this->mHorizontalCenter - 22, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(startGame);

    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_CreateHouse", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter + 98, this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(quitGame);

}
void DancingGuiSys::setWidgetCreateNewHouse()//一个没有状态的设置界面函数
{
    Button *creatNew =  (Button *)mTrayMgr->getWidget("CreatNewHouse_hide");
    creatNew->hide();
    creatNew =  (Button *)mTrayMgr->getWidget("StartGame_CreateHouse");
    creatNew->hide();

    creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse_show", Ogre::DisplayString(L"创建新房间"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(this->mHorizontalCenter + 38, 140);
    this->mWidget_vec.push_back(creatNew);


    //房间名称标签
    Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_RoomName", Ogre::DisplayString(L"房间名称"), 120);
    l_roomName->getOverlayElement()->setDimensions(120, 30);
    l_roomName->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter  - 165);
    this->mWidget_vec.push_back(l_roomName);

    //房间名称输入框
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName",  Ogre::DisplayString(L"请输入房间名称"), 200, 100);
    mTextBox->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 225 );
    this->mWidget_vec.push_back(mTextBox);


    //舞种
    //标签
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"舞种选择"), 120);
    l_danceStyle->getOverlayElement()->setDimensions(120, 30);
    l_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter - 105);
    this->mWidget_vec.push_back(l_danceStyle);


    //下拉列表
    Ogre::StringVector v_danceStyle;
    //v_danceStyle.push_back("Latin");
    v_danceStyle.push_back("QiaQia");
    OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"舞种选择"), 200, 5, v_danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(200, 50);
    s_danceStyle->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 115);
    this->mWidget_vec.push_back(s_danceStyle);


    //舞曲
    //标签
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"舞曲选择"), 120);
    l_danceSong->getOverlayElement()->setDimensions(120, 30);
    l_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter - 45);
    this->mWidget_vec.push_back(l_danceSong);


    //下拉列表
    Ogre::StringVector v_danceSong;
    v_danceSong.push_back("pretty");
    //v_danceSong.push_back("lalala");
    OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"舞曲选择"), 200, 5, v_danceSong);
    s_danceSong->getOverlayElement()->setDimensions(200, 50);
    s_danceSong->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter - 55);
    this->mWidget_vec.push_back(s_danceSong);


    //场景
    //标签
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"场景选择"), 120);
    l_danceScence->getOverlayElement()->setDimensions(120, 30);
    l_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter + 88, this->mVerticalCenter + 15);
    this->mWidget_vec.push_back(l_danceScence);


    //下拉列表
    Ogre::StringVector v_danceScence;
    v_danceScence.push_back("Street");
    v_danceScence.push_back("HG");
    OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"场景选择"), 200, 5, v_danceScence);
    s_danceScence->getOverlayElement()->setDimensions(200, 50);
    s_danceScence->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 5);
    this->mWidget_vec.push_back(s_danceScence);


    OgreBites::DecorWidget *tempSceneView = mTrayMgr->createDecorWidget(OgreBites::TL_NONE, "temp", "SdkTrays/Street");
    tempSceneView->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 55);
    //场景预览
    // OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceImage", "");
    // l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    // l_danceimage->getOverlayElement()->setDimensions(200, 200);
    //l_danceimage->getOverlayElement()->setPosition(this->mHorizontalCenter + 208, this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(tempSceneView);


    //确定创建按钮
    Button *create = mTrayMgr->createButton(OgreBites::TL_NONE, "CreateHouse", Ogre::DisplayString(L"确认创建"), 100);
    create->getOverlayElement()->setDimensions(100, 50);
    create->getOverlayElement()->setPosition(this->mHorizontalCenter - 22 , this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(create);
}

void DancingGuiSys::setWidgetPlayVideo()
{
    //播放视频
}

//licorice
void DancingGuiSys::setWidgetGamePractise()
{
    //舞步练习的场景
    this->mCurrentWidgetType = GamePractise;
    this->isCurrentTypeChanged = true;
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();


    //初始化一些必须的按钮
    //播放视频
    Button *playVideo = this->mTrayMgr->createButton(OgreBites::TL_NONE, "PlayVideo", Ogre::DisplayString(L"播放视频"), 100);
    playVideo->getOverlayElement()->setPosition(this->mHorizontalCenter * 2  - 118, this->mVerticalCenter + 205);
    this->mWidget_vec.push_back(playVideo);
    //返回按钮
    Button *returnGame = mTrayMgr->createButton(OgreBites::TL_NONE, "ReturnGame", Ogre::DisplayString(L"返回游戏"), 100);
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
    mPair.second = "CreateHouse";//确认创建房间按钮
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameStart;
    mPair.first =  CreateHouse;
    mPair.second = "QuitGame_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameOver;
    mPair.first =  CreateHouse;
    mPair.second = "CreatNewHouse_hide";//创建房间信息隐藏时的按钮
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
    //传递
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


