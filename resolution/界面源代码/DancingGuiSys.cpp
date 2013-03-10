#include "DancingGuiSys.h"


DancingGuiSys::DancingGuiSys(void)
{
}

DancingGuiSys::~DancingGuiSys(void)
{
}

//这里传了两个参数，第二个参数是为了控制游戏退出
DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager,Ogre::Root *mRoot)
{
    this->mTrayMgr = sdktraymanager;
	this->mRoot = mRoot;
	//默认单人模式
	m_gameStyle = 1;
    //默认状态
    mCurrentWidgetType = BaseState;
   // this->ConfigGuiInfo();
	
}
void DancingGuiSys::setGameStart()
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
	//退出按钮
	Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Quit",Ogre::DisplayString(L"退出游戏"),100);
	quitGame->getOverlayElement()->setPosition(900,550);
	this->mWidget_vec.push_back(quitGame);

	//返回重新设置游戏界面(这个按钮只有是在单机模式中才有)
	if(this->m_gameStyle == 1)
	{
		Button *setGame= mTrayMgr->createButton(OgreBites::TL_NONE,"SetGame",Ogre::DisplayString(L"返回"),100);
	    setGame->getOverlayElement()->setPosition(900,600);
	    this->mWidget_vec.push_back(setGame);
	}

	//返回重新选择房间界面(这个按钮只有是在局域网中才有)
	if(this->m_gameStyle == 2)
	{
		Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE,"SelectHouse",Ogre::DisplayString(L"返回"),100);
	    selectHouse->getOverlayElement()->setPosition(900,600);
	    this->mWidget_vec.push_back(selectHouse);
	}


	//游戏中对人物的其他控制放在DancingHandleSys类中，创建DancingHandleSys的对象
	//DancingHandleSys *temp = new DancingHandleSys();
	//。。。
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
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame",Ogre::DisplayString(L"开始游戏"),100);
	startGame->getOverlayElement()->setDimensions(120,50);
	startGame->getOverlayElement()->setPosition(450,350);
	this->mWidget_vec.push_back(startGame);
	
	
	//startGame->getOverlayElement()->setp
	//退出按钮
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame",Ogre::DisplayString(L"退出"),100);
	quitGame->getOverlayElement()->setDimensions(120,50);
	quitGame->getOverlayElement()->setPosition(450,410);
	this->mWidget_vec.push_back(quitGame);
	
	//关于我们 按钮
	OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE,"AboutUs",Ogre::DisplayString(L"关于我们"),100);
	aboutUs->getOverlayElement()->setDimensions(120,50);
	aboutUs->getOverlayElement()->setPosition(450,470);
	this->mWidget_vec.push_back(aboutUs);
}
void DancingGuiSys::setWidgetCreateRole()
{
    //设置当前状态
    this->mCurrentWidgetType = CreateRole;

    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

	//控制位置的变量
    Ogre::Real left = 200;
	Ogre::Real top = 100;

	//局域网/单机模式的选择
	singleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Box_Single",Ogre::DisplayString(L"单机模式"));
	singleBox->getOverlayElement()->setDimensions(100,30);
	singleBox->getOverlayElement()->setPosition(850,10);
	this->mWidget_vec.push_back(singleBox);
	if(this->m_gameStyle == 1)
	singleBox->setChecked(true,false);

	multiBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Box_Multi",Ogre::DisplayString(L"局域网模式"));
	multiBox->getOverlayElement()->setDimensions(100,30);
	multiBox->getOverlayElement()->setPosition(850,50);
	this->mWidget_vec.push_back(multiBox);
	if(this->m_gameStyle == 2)
	multiBox->setChecked(true,false);

	//昵称标签
	OgreBites::Label *lname = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Name",Ogre::DisplayString(L"昵称"),50);
	lname->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lname);
	left += 50; //250,90
	
	//输入昵称文本框
	//这里的文本框没有实现输入
	OgreBites::TextBox *tname = mTrayMgr->createTextBox(OgreBites::TL_NONE,"T_Name",Ogre::DisplayString(L"请输入"),180,50);
	tname->getOverlayElement()->setPosition(left,top);
	tname->setText(Ogre::DisplayString(L"请输入你的昵称"));
	this->mWidget_vec.push_back(tname);
	left -= 50; 
	top  += 60;//200,150

	//性别标签
	OgreBites::Label *lsex = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Sex",Ogre::DisplayString(L"性别"),50);
	lsex->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lsex);
	left += 50;//250,150

	//性别checkbox
	maleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"C_SexM",Ogre::DisplayString(L"男"),60);
	maleBox->getOverlayElement()->setPosition(left,top);
	maleBox->setChecked(true,false);
	this->mWidget_vec.push_back(maleBox);
	left += 120;//370,150

	femaleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"C_SexF",Ogre::DisplayString(L"女"),60);
	femaleBox->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(femaleBox);
    left -= 170;
	top += 60;//200,210

	//发型标签
	OgreBites::Label *lhair = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Hair",Ogre::DisplayString(L"发型"),50);
	lhair->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lhair);
	left += 50;//250,210

	//发型下拉框
	Ogre::StringVector  hairstyle;
	hairstyle.push_back(Ogre::DisplayString(L"短发"));
	hairstyle.push_back(Ogre::DisplayString(L"中分"));
	OgreBites::SelectMenu *shair = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Hair",Ogre::DisplayString(L"请选择"),180,10,hairstyle);
	shair->getOverlayElement()->setHeight(50);
	shair->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(shair);
	left -= 50;
	top += 60;//200,270

	//配饰
	OgreBites::Label *lrings = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Rings",Ogre::DisplayString(L"配饰"),50);
	lrings->getOverlayElement()->setPosition(left,top);
	left += 50;//250,270
	this->mWidget_vec.push_back(lrings);

	//配饰下拉框
	Ogre::StringVector  ringstyle;
	ringstyle.push_back(Ogre::DisplayString(L"耳环"));
	ringstyle.push_back(Ogre::DisplayString(L"耳钉"));
	OgreBites::SelectMenu *srings = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Rings",Ogre::DisplayString(L"请选择"),180,10,ringstyle);
	srings->getOverlayElement()->setHeight(50);
	srings->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(srings);
	left -= 50;
	top += 60;//200,330

	//上装
	OgreBites::Label *lshangzhuang = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Shangzhuang",Ogre::DisplayString(L"上装"),50);
	lshangzhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lshangzhuang);
	left += 50;//250,330

	//上装
	Ogre::StringVector  shangstyle;
	shangstyle.push_back(Ogre::DisplayString(L"衬衫"));
	shangstyle.push_back(Ogre::DisplayString(L"T恤"));
	OgreBites::SelectMenu *shangzhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Shangzhuang",Ogre::DisplayString(L"请选择"),180,10,shangstyle);
	shangzhuang->getOverlayElement()->setHeight(50);
	shangzhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(shangzhuang);
	left -= 50;
	top += 60;//200,390

	//从下面开始，下拉列表不能再显示中文了，我尝试在上装选项中多加几项，加多了显示中文的项也会报错，是不是内存不够？
	//下装
	OgreBites::Label *lxiazhuang = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Xiazhuang",Ogre::DisplayString(L"下装"),50);
	lxiazhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lxiazhuang);
	left += 50;//250,330

	//下装
	Ogre::StringVector  xiastyle;
	xiastyle.push_back(Ogre::DisplayString(L"mini-Skirt"));
	xiastyle.push_back(Ogre::DisplayString(L"Boshimiya-Skirt"));
	OgreBites::SelectMenu *xiazhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Xiazhuang",Ogre::DisplayString(L"请选择"),180,10,xiastyle);
	xiazhuang->getOverlayElement()->setHeight(50);
	xiazhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(xiazhuang);
	left -= 50;
	top += 60;//200,390

	//鞋子
	Label *lshoes = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Shoes",Ogre::DisplayString(L"鞋子"),50);
	lshoes->getOverlayElement()->setPosition(left,top);
	left += 50;//250,450
	this->mWidget_vec.push_back(lshoes);

	Ogre::StringVector  shoestyle;
	shoestyle.push_back(Ogre::DisplayString(L"song"));
	shoestyle.push_back(Ogre::DisplayString(L"gao"));
	OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Shoes",Ogre::DisplayString(L"请选择"),180,10,shoestyle);
	sshoes->getOverlayElement()->setHeight(50);
	sshoes->getOverlayElement()->setPosition(left,top);
	left -= 50;
	top += 60;//200，510
	this->mWidget_vec.push_back(sshoes);

	//显示当前形象标签
	OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_ShowImage",Ogre::DisplayString(L"当前形象"),100);
	showImage->getOverlayElement()->setPosition(630,100);
	this->mWidget_vec.push_back(showImage);
	//显示形象空间
	OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Image","");
	image->getOverlayElement()->setDimensions(210,350);
	image->getOverlayElement()->setPosition(580,130);
	this->mWidget_vec.push_back(image);
	//image->getOverlayElement()->setMaterialName("");


	//创建角色 按钮
	OgreBites::Button *createRole = mTrayMgr->createButton(OgreBites::TL_NONE,"createRole",Ogre::DisplayString(L"创建角色"),100);
	createRole->getOverlayElement()->setDimensions(100,50);
	createRole->getOverlayElement()->setPosition(350,570);
	this->mWidget_vec.push_back(createRole);

	//直接开始游戏按钮
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_role",Ogre::DisplayString(L"开始游戏"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(470,570);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//退出按钮
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_role",Ogre::DisplayString(L"退出"),100);
	quitGame->getOverlayElement()->setDimensions(100,50);
	quitGame->getOverlayElement()->setPosition(590,570);
	this->mWidget_vec.push_back(quitGame);

    //其他控件
}//startgame createhouse createrole gameset housed
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
	Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceStyle",Ogre::DisplayString(L"舞种"));
	l_danceStyle->getOverlayElement()->setDimensions(100,50);
	l_danceStyle->getOverlayElement()->setPosition(400,120);
	this->mWidget_vec.push_back(l_danceStyle);

	Ogre::StringVector danceStyle;
	danceStyle.push_back(Ogre::DisplayString(L"Latin"));
	danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
	SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceStyle",Ogre::DisplayString(L"请选择"),180,10,danceStyle);
	s_danceStyle->getOverlayElement()->setDimensions(180,50);
	s_danceStyle->getOverlayElement()->setPosition(505,110);
	this->mWidget_vec.push_back(s_danceStyle);

	//从这开始，下面的下拉列表点击没反应了！
	//舞曲
	Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceSong",Ogre::DisplayString(L"舞曲"));
	l_danceSong->getOverlayElement()->setDimensions(100,50);
	l_danceSong->getOverlayElement()->setPosition(400,200);
	this->mWidget_vec.push_back(l_danceSong);

	Ogre::StringVector danceSong;
	danceStyle.push_back(Ogre::DisplayString("SanFrancisco"));
	danceStyle.push_back(Ogre::DisplayString("Young For You"));
	SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceSong",Ogre::DisplayString(L"请选择"),180,10,danceSong);
	s_danceSong->getOverlayElement()->setDimensions(180,50);
	s_danceSong->getOverlayElement()->setPosition(505,190);
	this->mWidget_vec.push_back(s_danceSong);

	//场景
	Label *l_danceScence= mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceScence",Ogre::DisplayString(L"场景"));
	l_danceScence->getOverlayElement()->setDimensions(100,50);
	l_danceScence->getOverlayElement()->setPosition(400,280);
	this->mWidget_vec.push_back(l_danceScence);

	Ogre::StringVector danceScence;
	danceStyle.push_back(Ogre::DisplayString("Sea"));
	danceStyle.push_back(Ogre::DisplayString("Road"));
	SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceScence",Ogre::DisplayString(L"请选择"),180,10,danceScence);
	s_danceScence->getOverlayElement()->setDimensions(180,50);
	s_danceScence->getOverlayElement()->setPosition(505,270);
	this->mWidget_vec.push_back(s_danceScence);

	//场景预览
	Label *l_danceView= mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceView",Ogre::DisplayString(L"场景预览"));
	l_danceView->getOverlayElement()->setDimensions(100,50);
	l_danceView->getOverlayElement()->setPosition(502,350);
	this->mWidget_vec.push_back(l_danceView);

	OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceImage","");
	l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125,125,125));
	l_danceimage->getOverlayElement()->setDimensions(200,200);
	l_danceimage->getOverlayElement()->setPosition(450,400);
	l_danceimage->show();
	this->mWidget_vec.push_back(l_danceimage);


	//修改角色按钮
	OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE,"CorectRole_GameSet",Ogre::DisplayString(L"修改角色"),100);
	corectRole->getOverlayElement()->setDimensions(100,50);
	corectRole->getOverlayElement()->setPosition(370,620);
	this->mWidget_vec.push_back(corectRole);

	//直接开始游戏按钮
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_GameSet",Ogre::DisplayString(L"开始游戏"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(490,620);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//退出按钮
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_GameSet",Ogre::DisplayString(L"退出"),100);
	quitGame->getOverlayElement()->setDimensions(100,50);
	quitGame->getOverlayElement()->setPosition(610,620);
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
	Label  *houseName = mTrayMgr->createLabel(OgreBites::TL_NONE,"HouseName",Ogre::DisplayString(L"房间名称"),100);
	this->mWidget_vec.push_back(houseName);
	houseName->getOverlayElement()->setDimensions(120,30);
	houseName->getOverlayElement()->setPosition(90,140);

	//舞曲类型
	Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"DanceStyle",Ogre::DisplayString(L"游戏舞种"),100);
	this->mWidget_vec.push_back(danceStyle);
	danceStyle->getOverlayElement()->setDimensions(120,30);
	danceStyle->getOverlayElement()->setPosition(210,140);

	//剩余座位
	Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE,"LeftSeats",Ogre::DisplayString(L"剩余座位"),100);
	this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120,30);
	leftSeats->getOverlayElement()->setPosition(330,140);

	//14个显示房间的标签的名称
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


	//临时的vector容器用来存储14个显示房间的标签
	std::vector<OgreBites::Label *> mLabel_vec;
	Ogre::Real pTop = 170;
	for(int i = 0;i < 14;i++)
	{  
		//把14个标签用来显示房间的信息
		mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE,labelString[i],"",360));
		mLabel_vec[i]->getOverlayElement()->setDimensions(360,30);
		mLabel_vec[i]->getOverlayElement()->setPosition(90,pTop);
		pTop += 30;
		this->mWidget_vec.push_back(mLabel_vec[i]);
	}

	//竖直线划分区域
	OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE,"Se_Cut",3);
	cutSeparator->getOverlayElement()->setHeight(450);
	cutSeparator->getOverlayElement()->setPosition(500,140);
	this->mWidget_vec.push_back(cutSeparator);

	
	//创建新的房间
	//标签
	Label *creatNew = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_CreatNew",Ogre::DisplayString(L"创建新房间"),120);
	creatNew->getOverlayElement()->setDimensions(120,30);
	creatNew->getOverlayElement()->setPosition(550,140);
	this->mWidget_vec.push_back(creatNew);
	
	//用来记录位置的变量
	Ogre::Real left,top;
	left = 600;
	top = 180;

	//房间名称标签
	Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_RoomName",Ogre::DisplayString(L"房间名称"),120);
	l_roomName->getOverlayElement()->setDimensions(120,30);
	l_roomName->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_roomName);
	top -= 10;
	left += 120;//left 670,top 130
	//房间名称输入框
	OgreBites::TextBox *t_roomName = mTrayMgr->createTextBox(OgreBites::TL_NONE,"T_RoomName",Ogre::DisplayString(L"请输入房间名称"),200,50);
	t_roomName->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(t_roomName);
	left -= 120;
	top  += 70;//left 550,top 180

	//舞种
	//标签
	Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceStyle",Ogre::DisplayString(L"舞种选择"),120);
	l_danceStyle->getOverlayElement()->setDimensions(120,30);
	l_danceStyle->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceStyle);
	left += 120;
	top -= 10;//left 670,top 170

	//下拉列表
	Ogre::StringVector v_danceStyle;
	v_danceStyle.push_back("Latin");
	v_danceStyle.push_back("QiaQia");
	OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceStyle",Ogre::DisplayString(L"舞种选择"),200,5,v_danceStyle);
	s_danceStyle->getOverlayElement()->setDimensions(200,50);
	s_danceStyle->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceStyle);
	left -= 120;
	top  += 70;//left 550,top 220

	//舞曲
	//标签
	Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceSong",Ogre::DisplayString(L"舞曲选择"),120);
	l_danceSong->getOverlayElement()->setDimensions(120,30);
	l_danceSong->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceSong);
	left += 120;
	top  -= 10;//left 670,top 210

	//下拉列表
	Ogre::StringVector v_danceSong;
	v_danceSong.push_back("pretty");
	v_danceSong.push_back("lalala");
	OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceSong",Ogre::DisplayString(L"舞曲选择"),200,5,v_danceSong);
	s_danceSong->getOverlayElement()->setDimensions(200,50);
	s_danceSong->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceSong);
	left -= 120;
	top  += 70;//left 550,top 260

	//场景
	//标签
	Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceScence",Ogre::DisplayString(L"场景选择"),120);
	l_danceScence->getOverlayElement()->setDimensions(120,30);
	l_danceScence->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceScence);
	left += 120;
	top  -= 10;//left 670,top 250

	//下拉列表
	Ogre::StringVector v_danceScence;
	v_danceScence.push_back("seaside");
	v_danceScence.push_back("roadway");
	OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceScence",Ogre::DisplayString(L"场景选择"),200,5,v_danceScence);
	s_danceScence->getOverlayElement()->setDimensions(200,50);
	s_danceScence->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceScence);

	top  += 50;//left 670,top 300
	//场景预览
	OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE,"DanceImage","");
	l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125,125,125));
	l_danceimage->getOverlayElement()->setDimensions(200,200);
	l_danceimage->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceimage);

	//修改角色按钮
	OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE,"CorectRole_CreateHouse",Ogre::DisplayString(L"修改角色"),100);
	corectRole->getOverlayElement()->setDimensions(100,50);
	corectRole->getOverlayElement()->setPosition(370,620);
	this->mWidget_vec.push_back(corectRole);

	//直接开始游戏按钮
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_CreateHouse",Ogre::DisplayString(L"开始游戏"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(490,620);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//退出按钮
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_CreateHouse",Ogre::DisplayString(L"退出"),100);
	quitGame->getOverlayElement()->setDimensions(100,50);
	quitGame->getOverlayElement()->setPosition(610,620);
	this->mWidget_vec.push_back(quitGame);

}//startgame createhouse createrole gameset housed

//我把进入房间等待的那个界面删除了，用户建好房间或者设置好游戏选项后，应该直接进入跳舞的那个界面等待更好
/*void DancingGuiSys::setWidgetHoused()
{
    this->mCurrentWidgetType = Housed;

    //删除以往界面中的控件
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //清空界面控件列表
    mWidget_vec.clear();

    //8个座位标签
	Ogre::StringVector seatName;
	seatName.push_back("seat_1");
	seatName.push_back("seat_2");
	seatName.push_back("seat_3");
	seatName.push_back("seat_4");
	seatName.push_back("seat_5");
	seatName.push_back("seat_6");
	seatName.push_back("seat_7");
	seatName.push_back("seat_8");
	
	//存储标签上显示的容器
	Ogre::StringVector seatString;
	seatString.push_back("1");
	seatString.push_back("2");
	seatString.push_back("3");
	seatString.push_back("4");
	seatString.push_back("5");
	seatString.push_back("6");
	seatString.push_back("7");
	seatString.push_back("8");

	//临时的vector容器用来存储8个显示为座位的标签
	std::vector<OgreBites::Label *> mLabel_vec;
	Ogre::Real pTop = 150;
	Ogre::Real pLeft = 80;
	for(int i = 0;i < 4;i++)
	{  
		mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE,seatName[i],seatString[i],360));
		mLabel_vec[i]->getOverlayElement()->setDimensions(120,170);
		mLabel_vec[i]->getOverlayElement()->setPosition(pLeft,pTop);
		pLeft += 150;
		this->mWidget_vec.push_back(mLabel_vec[i]);
	}

	pTop += 190;
	pLeft = 80;
	for(int i = 4;i < 8;i++)
	{
		mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE,seatString[i],seatString[i],360));
		mLabel_vec[i]->getOverlayElement()->setDimensions(120,170);
		mLabel_vec[i]->getOverlayElement()->setPosition(pLeft,pTop);
		pLeft += 150;
		this->mWidget_vec.push_back(mLabel_vec[i]);
	}
   
	
}*/

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

	Ogre::String btnName = button->getName();

	//对所有“退出”和“关于我们”的按钮进行特殊处理，其余利用map关联查找
	if(btnName == Ogre::String("Quit") || btnName == Ogre::String("QuitGame_CreateHouse") || btnName == Ogre::String("QuitGame") || btnName == Ogre::String("QuitGame_role") ||btnName == Ogre::String("QuitGame_GameSet"))
	{
		mRoot->queueEndRendering();
	}
	else if(btnName == Ogre::String("AboutUs"))
	{
		mTrayMgr->showOkDialog(Ogre::DisplayString(L"关于我们"),Ogre::DisplayString("tell me about you"));
	}
	else
	{
		mMap.clear();
	this->ConfigGuiInfo();
    mPair.first = this->mCurrentWidgetType;
    mPair.second = btnName;
    functionPoint temp = this->mMap[mPair];
    (this->*temp)();
	}
}
void DancingGuiSys::itemSelected(SelectMenu *menu)
{
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
	//对checkbox进行判断，实现两者中只能点击一个
	if(boxName == Ogre::String("Box_Single"))
	{   
		//设置为单机模式
		this->m_gameStyle = 1;
		if(box->isChecked())
		this->multiBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("Box_Multi"))
	{  
		//设置为局域网模式
		this->m_gameStyle = 2;
		if(box->isChecked())
		this->singleBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("C_SexM"))
	{
		//待处理
		//处理显示男生形象，函数尚未添加
		if(box->isChecked())
		this->femaleBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("C_SexF"))
	{
		//待处理
		//处理显示女生形象，函数尚未添加
		if(box->isChecked())
		this->maleBox->setChecked(false,false);
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
    //startgame createhouse createrole gameset housed

	//单机和局域网共有的
	mPair.first = CreateRole;
	mPair.second = "StartGame_role";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;


	//单人模式下引导界面跳转
	if(m_gameStyle == 1)
	{
    //最开始运行程序时的界面
    mPair.first =  BaseState;
    mPair.second = "StartGame";
	//点击开始按钮后自动切换到创建角色界面
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

    //角色创建完毕后，点击创建角色，跳转到游戏设定
    mPair.first =  CreateRole;
    mPair.second = "createRole";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetGameSet;

    //游戏设定也结束后，这里还要添加返回上一步的判断切换
    mPair.first =  GameSet;
    mPair.second = "CorectRole_GameSet";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

	//设置游戏界面-->游戏开始界面
	mPair.first = GameSet;
	mPair.second = "StartGame_GameSet";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;
    
	//游戏开始界面-->设置游戏界面
	mPair.first =  GameStart;
    mPair.second = "SetGame";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetGameSet;
	
	}
	else if(m_gameStyle == 2)
	{
		//局域网时界面跳转
   //创建角色跳转到创建房间和选择房间界面
    mPair.first =  CreateRole;
    mPair.second = "createRole";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetCreateHouse;

	//由创建房间和选择房间的界面跳转回创建角色界面
    mPair.first =  CreateHouse;
    mPair.second = "CorectRole_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

	////////////////////////////////////////////////////
	//对应的真正进入游戏的界面
	//在创建好房间后直接点击开始游戏进入的是游戏开始的界面中
	mPair.first = CreateHouse;
	mPair.second = "StartGame_CreateHouse";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;
    
	//游戏开始界面-->选择或创建房间界面
	mPair.first = GameStart;
	mPair.second = "SelectHouse";
	this->mMap[mPair] = &DancingGuiSys::setWidgetCreateHouse;
	}
}
