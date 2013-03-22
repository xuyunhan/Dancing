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

//这里传了两个参数，第二个参数是为了控制游戏退出
DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager, Ogre::Root *mRoot,Ogre::RenderWindow *mWindow)
{

    mParseXml = new ParseXml();
    // mParseXml->inputRolesFile();
    //mParseXml->readRolesFile();


    this->mTrayMgr = sdktraymanager;
    this->mRoot = mRoot;
	this->mWindow = mWindow;
    //默认单人模式
    m_gameStyle = 1;
	//默认卡通形象
	m_roleStyle = 1;

	//默认没有心房间
	isNewHouse = false;
    //默认状态
    mCurrentWidgetType = BaseState;
   // this->ConfigGuiInfo();

//xuyunhan
	//初始化实体对象指针
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
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

    //初始化一下必须的控件
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
	//准备按钮
	Button *readyGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Ready",Ogre::DisplayString(L"准备"),100);
	readyGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(readyGame);
	top += 50;

	//练习按钮（舞步教学）
	Button *studyGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Practise",Ogre::DisplayString(L"练习"),100);
	studyGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(studyGame);
	top += 50;

    //退出按钮
    Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "Quit", Ogre::DisplayString(L"退出游戏"), 100);
    quitGame->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(quitGame);
	top += 50;

    //返回重新设置游戏界面(这个按钮只有是在单机模式中才有)
    if(this->m_gameStyle == 1)
    {
        Button *setGame = mTrayMgr->createButton(OgreBites::TL_NONE, "SetGame", Ogre::DisplayString(L"返回"), 100);
        setGame->getOverlayElement()->setPosition(left, top);
        this->mWidget_vec.push_back(setGame);
    }

    //返回重新选择房间界面(这个按钮只有是在局域网中才有)
    if(this->m_gameStyle == 2)
    {
        Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE, "SelectHouse", Ogre::DisplayString(L"返回"), 100);
        selectHouse->getOverlayElement()->setPosition(left, top);
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
//licorice
void DancingGuiSys::setWidgetPlayVideo()
{
	//播放视频
}
//licorice
void DancingGuiSys::setWidgetGameReady()
{   
	mTrayMgr->showOkDialog(Ogre::DisplayString(L"倒计时开始"),Ogre::DisplayString("5"));
	//倒计时
}
//licorice
void DancingGuiSys::setWidgetGamePractise()
{
	//舞步练习的场景
	this->mCurrentWidgetType = GamePractise;
    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

	Ogre::Real left = 900;
	Ogre::Real top = 550;

	//初始化一些必须的按钮
	//播放视频
	Button *playVideo = this->mTrayMgr->createButton(OgreBites::TL_NONE,"PlayVideo",Ogre::DisplayString(L"播放视频"),100);
	playVideo->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(playVideo);
	top += 50;
	//返回按钮
	Button *returnGame = mTrayMgr->createButton(OgreBites::TL_NONE,"ReturnGame",Ogre::DisplayString(L"返回游戏"),100);
	returnGame->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(returnGame);
}
void DancingGuiSys::setWidgetBaseState()
{
    this->mCurrentWidgetType = BaseState;
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
    startGame->getOverlayElement()->setPosition(450, 350);
    this->mWidget_vec.push_back(startGame);


    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(120, 50);
    quitGame->getOverlayElement()->setPosition(450, 410);
    this->mWidget_vec.push_back(quitGame);

    //关于我们 按钮
    OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE, "AboutUs", Ogre::DisplayString(L"关于我们"), 100);
    aboutUs->getOverlayElement()->setDimensions(120, 50);
    aboutUs->getOverlayElement()->setPosition(450, 470);
    this->mWidget_vec.push_back(aboutUs);
}
void DancingGuiSys::setWidgetCreateNewHouse()
{
	isNewHouse = true;
	  //用来记录位置的变量
    Ogre::Real left, top;
    left = 600;
    top = 180;

    //房间名称标签
    Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_RoomName", Ogre::DisplayString(L"房间名称"), 120);
    l_roomName->getOverlayElement()->setDimensions(120, 30);
    l_roomName->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_roomName);
    top -= 10;
    left += 120;//left 670,top 130
    //房间名称输入框
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName",  Ogre::DisplayString(L"请输入房间名称"), 200, 100);
    mTextBox->getOverlayElement()->setPosition(left, top - 50 );
    // mTextBox->setText( Ogre::DisplayString(L"riririirirllllllll"));
    this->mWidget_vec.push_back(mTextBox);
    //mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_RoomName", Ogre::DisplayString(L"请输入房间名称"), 200, 70);
    //mTextBox->getOverlayElement()->setPosition(left, top-20);
    //this->mWidget_vec.push_back(mTextBox);
    left -= 120;
    top  += 70;//left 550,top 180

    //舞种
    //标签
    Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceStyle", Ogre::DisplayString(L"舞种选择"), 120);
    l_danceStyle->getOverlayElement()->setDimensions(120, 30);
    l_danceStyle->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceStyle);
    left += 120;
    top -= 10;//left 670,top 170

    //下拉列表
    Ogre::StringVector v_danceStyle;
    v_danceStyle.push_back("Latin");
    v_danceStyle.push_back("QiaQia");
    OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"舞种选择"), 200, 5, v_danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(200, 50);
    s_danceStyle->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceStyle);
    left -= 120;
    top  += 70;//left 550,top 220

    //舞曲
    //标签
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"舞曲选择"), 120);
    l_danceSong->getOverlayElement()->setDimensions(120, 30);
    l_danceSong->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceSong);
    left += 120;
    top  -= 10;//left 670,top 210

    //下拉列表
    Ogre::StringVector v_danceSong;
    v_danceSong.push_back("pretty");
    v_danceSong.push_back("lalala");
    OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"舞曲选择"), 200, 5, v_danceSong);
    s_danceSong->getOverlayElement()->setDimensions(200, 50);
    s_danceSong->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceSong);
    left -= 120;
    top  += 70;//left 550,top 260

    //场景
    //标签
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"场景选择"), 120);
    l_danceScence->getOverlayElement()->setDimensions(120, 30);
    l_danceScence->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceScence);
    left += 120;
    top  -= 10;//left 670,top 250

    //下拉列表
    Ogre::StringVector v_danceScence;
    v_danceScence.push_back("seaside");
    v_danceScence.push_back("roadway");
    OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"场景选择"), 200, 5, v_danceScence);
    s_danceScence->getOverlayElement()->setDimensions(200, 50);
    s_danceScence->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(s_danceScence);

    top  += 50;//left 670,top 300
    //场景预览
    OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceImage", "");
    l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    l_danceimage->getOverlayElement()->setDimensions(200, 200);
    l_danceimage->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(l_danceimage);
	left -= 120;
	top += 150;

	//确定创建按钮
	//先注释了，感觉可以不要，因为开始游戏就相当于确定，简洁一点更好
	/*Button *create = mTrayMgr->createButton(OgreBites::TL_NONE,"CertainCreate",Ogre::DisplayString(L"确认"),100);
	create->getOverlayElement()->setDimensions(100,50);
	create->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(create);*/
}

void DancingGuiSys::setWidgetGameSet()
{
    this->mCurrentWidgetType = GameSet;
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
    l_danceStyle->getOverlayElement()->setPosition(400, 120);
    this->mWidget_vec.push_back(l_danceStyle);

    Ogre::StringVector danceStyle;
    danceStyle.push_back(Ogre::DisplayString(L"Latin"));
    danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
    SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceStyle", Ogre::DisplayString(L"请选择"), 180, 10, danceStyle);
    s_danceStyle->getOverlayElement()->setDimensions(180, 50);
    s_danceStyle->getOverlayElement()->setPosition(505, 110);
    this->mWidget_vec.push_back(s_danceStyle);

    //从这开始，下面的下拉列表点击没反应了！
    //舞曲
    Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceSong", Ogre::DisplayString(L"舞曲"));
    l_danceSong->getOverlayElement()->setDimensions(100, 50);
    l_danceSong->getOverlayElement()->setPosition(400, 200);
    this->mWidget_vec.push_back(l_danceSong);

    Ogre::StringVector danceSong;
    danceSong.push_back(Ogre::DisplayString("SanFrancisco"));
    danceSong.push_back(Ogre::DisplayString("Young For You"));
    danceSong.push_back(Ogre::DisplayString(L"阿Q"));
    SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceSong", Ogre::DisplayString(L"请选择"), 180, 10, danceSong);
    s_danceSong->getOverlayElement()->setDimensions(180, 50);
    s_danceSong->getOverlayElement()->setPosition(505, 190);
    this->mWidget_vec.push_back(s_danceSong);

    //场景
    Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceScence", Ogre::DisplayString(L"场景"));
    l_danceScence->getOverlayElement()->setDimensions(100, 50);
    l_danceScence->getOverlayElement()->setPosition(400, 280);
    this->mWidget_vec.push_back(l_danceScence);

    Ogre::StringVector danceScence;
    danceScence.push_back(Ogre::DisplayString("Sea"));
    danceScence.push_back(Ogre::DisplayString("Road"));
    danceScence.push_back(Ogre::DisplayString(L"天池"));
    SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_DanceScence", Ogre::DisplayString(L"请选择"), 180, 10, danceScence);
    s_danceScence->getOverlayElement()->setDimensions(180, 50);
    s_danceScence->getOverlayElement()->setPosition(505, 270);
    this->mWidget_vec.push_back(s_danceScence);

    //场景预览
    Label *l_danceView = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceView", Ogre::DisplayString(L"场景预览"));
    l_danceView->getOverlayElement()->setDimensions(100, 50);
    l_danceView->getOverlayElement()->setPosition(502, 350);
    this->mWidget_vec.push_back(l_danceView);

    OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_DanceImage", "");
    l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125, 125, 125));
    l_danceimage->getOverlayElement()->setDimensions(200, 200);
    l_danceimage->getOverlayElement()->setPosition(450, 400);
    l_danceimage->show();
    this->mWidget_vec.push_back(l_danceimage);


    //修改角色按钮
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_GameSet", Ogre::DisplayString(L"修改角色"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(370, 620);
    this->mWidget_vec.push_back(corectRole);

    //直接开始游戏按钮
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_GameSet", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(490, 620);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_GameSet", Ogre::DisplayString(L"退出"), 100);
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

    //房间名
    Label  *houseName = mTrayMgr->createLabel(OgreBites::TL_NONE, "HouseName", Ogre::DisplayString(L"房间名称"), 100);
    this->mWidget_vec.push_back(houseName);
    houseName->getOverlayElement()->setDimensions(120, 30);
    houseName->getOverlayElement()->setPosition(90, 140);

    //舞曲类型
    Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE, "DanceStyle", Ogre::DisplayString(L"游戏舞种"), 100);
    this->mWidget_vec.push_back(danceStyle);
    danceStyle->getOverlayElement()->setDimensions(120, 30);
    danceStyle->getOverlayElement()->setPosition(210, 140);

    //剩余座位
    Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE, "LeftSeats", Ogre::DisplayString(L"剩余座位"), 100);
    this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120, 30);
    leftSeats->getOverlayElement()->setPosition(330, 140);

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
    TiXmlDocument *myDocument = new TiXmlDocument("houses.xml");
    myDocument->LoadFile();
    //获得根元素，即Persons。
    TiXmlElement *RootElement = myDocument->RootElement();//roles

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
        mLabel_vec[i]->getOverlayElement()->setPosition(90, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }







    /*for(int i = 0; i < 14; i++)
    {
        //把14个标签用来显示房间的信息
        mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE, labelString[i], "", 360));
        mLabel_vec[i]->getOverlayElement()->setDimensions(360, 30);
        mLabel_vec[i]->getOverlayElement()->setPosition(90, pTop);
        pTop += 30;
        this->mWidget_vec.push_back(mLabel_vec[i]);
    }*/

    //竖直线划分区域
    OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE, "Se_Cut", 3);
    cutSeparator->getOverlayElement()->setHeight(450);
    cutSeparator->getOverlayElement()->setPosition(500, 140);
    this->mWidget_vec.push_back(cutSeparator);


    //创建新的房间
    //标签
    Button *creatNew = mTrayMgr->createButton(OgreBites::TL_NONE, "CreatNewHouse", Ogre::DisplayString(L"创建新房间"), 120);
    creatNew->getOverlayElement()->setDimensions(120, 30);
    creatNew->getOverlayElement()->setPosition(550, 140);
    this->mWidget_vec.push_back(creatNew);
	
	if(isNewHouse)
	{
		setWidgetCreateNewHouse();
	}
    //修改角色按钮
    OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE, "CorectRole_CreateHouse", Ogre::DisplayString(L"修改角色"), 100);
    corectRole->getOverlayElement()->setDimensions(100, 50);
    corectRole->getOverlayElement()->setPosition(370, 620);
    this->mWidget_vec.push_back(corectRole);

    //直接开始游戏按钮
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_CreateHouse", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(490, 620);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_CreateHouse", Ogre::DisplayString(L"退出"), 100);
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

	//licorice每次响应按钮后config一次，以防创建重复的按钮
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
	//对checkbox进行判断，实现两者中只能点击一个以及必须有一个被选中
	if(boxName == Ogre::String("Box_Single"))
	{   
		//设置为单机模式
		this->m_gameStyle = 1;
		
		//licorice
		//转换到底显示哪个创建角色按钮,单机下显示单机的创建角色按钮
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
		//设置为局域网模式
		this->m_gameStyle = 2;
		
		//licorice
		//转换到底显示哪个创建角色按钮
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
		//待处理
		//处理显示男生形象，函数尚未添加
					
		this->femaleBox->setChecked(false,false);
		this->maleBox->setChecked(true,false);
		this->changgeScene(box->getName() );
		
		
	}
	else if(boxName == Ogre::String("C_SexF"))
	{
		//待处理
		//处理显示女生形象，函数尚未添加
		
			this->maleBox->setChecked(false,false);
			this->femaleBox->setChecked(true,false);
			this->changgeScene(box->getName() );
			
	
	}
	else if(boxName == Ogre::String("Cartoon_Role"))
	{   
		this->m_roleStyle = 1;
		//处理卡通形象
		this->role_real->setChecked(false,false);
		this->role_cartoon->setChecked(true,false);
		
		//对应的操作
		
	}
	else if(boxName == Ogre::String("Real_Role"))
	{   
		this->m_roleStyle = 2;
		//处理实时建模
		
			//对应的操作
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

	//licorice 不要开始按钮的响应
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

	//licorice 当已经创建了后，不能再创建
	mPair.first = CreateHouse;
	mPair.second = "CreatNewHouse";
	if(!isNewHouse)//已经点击了创建新房间按钮吗？没有就创建
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


