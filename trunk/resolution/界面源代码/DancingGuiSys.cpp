#include "DancingGuiSys.h"


DancingGuiSys::DancingGuiSys(void)
{
}

DancingGuiSys::~DancingGuiSys(void)
{
}

//���ﴫ�������������ڶ���������Ϊ�˿�����Ϸ�˳�
DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager,Ogre::Root *mRoot)
{
    this->mTrayMgr = sdktraymanager;
	this->mRoot = mRoot;
	//Ĭ�ϵ���ģʽ
	m_gameStyle = 1;
    //Ĭ��״̬
    mCurrentWidgetType = BaseState;
   // this->ConfigGuiInfo();
	
}
void DancingGuiSys::setGameStart()
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
	Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"Quit",Ogre::DisplayString(L"�˳���Ϸ"),100);
	quitGame->getOverlayElement()->setPosition(900,550);
	this->mWidget_vec.push_back(quitGame);

	//��������������Ϸ����(�����ťֻ�����ڵ���ģʽ�в���)
	if(this->m_gameStyle == 1)
	{
		Button *setGame= mTrayMgr->createButton(OgreBites::TL_NONE,"SetGame",Ogre::DisplayString(L"����"),100);
	    setGame->getOverlayElement()->setPosition(900,600);
	    this->mWidget_vec.push_back(setGame);
	}

	//��������ѡ�񷿼����(�����ťֻ�����ھ������в���)
	if(this->m_gameStyle == 2)
	{
		Button *selectHouse = mTrayMgr->createButton(OgreBites::TL_NONE,"SelectHouse",Ogre::DisplayString(L"����"),100);
	    selectHouse->getOverlayElement()->setPosition(900,600);
	    this->mWidget_vec.push_back(selectHouse);
	}


	//��Ϸ�ж�������������Ʒ���DancingHandleSys���У�����DancingHandleSys�Ķ���
	//DancingHandleSys *temp = new DancingHandleSys();
	//������
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
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame",Ogre::DisplayString(L"��ʼ��Ϸ"),100);
	startGame->getOverlayElement()->setDimensions(120,50);
	startGame->getOverlayElement()->setPosition(450,350);
	this->mWidget_vec.push_back(startGame);
	
	
	//startGame->getOverlayElement()->setp
	//�˳���ť
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame",Ogre::DisplayString(L"�˳�"),100);
	quitGame->getOverlayElement()->setDimensions(120,50);
	quitGame->getOverlayElement()->setPosition(450,410);
	this->mWidget_vec.push_back(quitGame);
	
	//�������� ��ť
	OgreBites::Button *aboutUs = mTrayMgr->createButton(OgreBites::TL_NONE,"AboutUs",Ogre::DisplayString(L"��������"),100);
	aboutUs->getOverlayElement()->setDimensions(120,50);
	aboutUs->getOverlayElement()->setPosition(450,470);
	this->mWidget_vec.push_back(aboutUs);
}
void DancingGuiSys::setWidgetCreateRole()
{
    //���õ�ǰ״̬
    this->mCurrentWidgetType = CreateRole;

    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

	//����λ�õı���
    Ogre::Real left = 200;
	Ogre::Real top = 100;

	//������/����ģʽ��ѡ��
	singleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Box_Single",Ogre::DisplayString(L"����ģʽ"));
	singleBox->getOverlayElement()->setDimensions(100,30);
	singleBox->getOverlayElement()->setPosition(850,10);
	this->mWidget_vec.push_back(singleBox);
	if(this->m_gameStyle == 1)
	singleBox->setChecked(true,false);

	multiBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Box_Multi",Ogre::DisplayString(L"������ģʽ"));
	multiBox->getOverlayElement()->setDimensions(100,30);
	multiBox->getOverlayElement()->setPosition(850,50);
	this->mWidget_vec.push_back(multiBox);
	if(this->m_gameStyle == 2)
	multiBox->setChecked(true,false);

	//�ǳƱ�ǩ
	OgreBites::Label *lname = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Name",Ogre::DisplayString(L"�ǳ�"),50);
	lname->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lname);
	left += 50; //250,90
	
	//�����ǳ��ı���
	//������ı���û��ʵ������
	OgreBites::TextBox *tname = mTrayMgr->createTextBox(OgreBites::TL_NONE,"T_Name",Ogre::DisplayString(L"������"),180,50);
	tname->getOverlayElement()->setPosition(left,top);
	tname->setText(Ogre::DisplayString(L"����������ǳ�"));
	this->mWidget_vec.push_back(tname);
	left -= 50; 
	top  += 60;//200,150

	//�Ա��ǩ
	OgreBites::Label *lsex = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Sex",Ogre::DisplayString(L"�Ա�"),50);
	lsex->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lsex);
	left += 50;//250,150

	//�Ա�checkbox
	maleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"C_SexM",Ogre::DisplayString(L"��"),60);
	maleBox->getOverlayElement()->setPosition(left,top);
	maleBox->setChecked(true,false);
	this->mWidget_vec.push_back(maleBox);
	left += 120;//370,150

	femaleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"C_SexF",Ogre::DisplayString(L"Ů"),60);
	femaleBox->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(femaleBox);
    left -= 170;
	top += 60;//200,210

	//���ͱ�ǩ
	OgreBites::Label *lhair = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Hair",Ogre::DisplayString(L"����"),50);
	lhair->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lhair);
	left += 50;//250,210

	//����������
	Ogre::StringVector  hairstyle;
	hairstyle.push_back(Ogre::DisplayString(L"�̷�"));
	hairstyle.push_back(Ogre::DisplayString(L"�з�"));
	OgreBites::SelectMenu *shair = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Hair",Ogre::DisplayString(L"��ѡ��"),180,10,hairstyle);
	shair->getOverlayElement()->setHeight(50);
	shair->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(shair);
	left -= 50;
	top += 60;//200,270

	//����
	OgreBites::Label *lrings = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Rings",Ogre::DisplayString(L"����"),50);
	lrings->getOverlayElement()->setPosition(left,top);
	left += 50;//250,270
	this->mWidget_vec.push_back(lrings);

	//����������
	Ogre::StringVector  ringstyle;
	ringstyle.push_back(Ogre::DisplayString(L"����"));
	ringstyle.push_back(Ogre::DisplayString(L"����"));
	OgreBites::SelectMenu *srings = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Rings",Ogre::DisplayString(L"��ѡ��"),180,10,ringstyle);
	srings->getOverlayElement()->setHeight(50);
	srings->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(srings);
	left -= 50;
	top += 60;//200,330

	//��װ
	OgreBites::Label *lshangzhuang = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Shangzhuang",Ogre::DisplayString(L"��װ"),50);
	lshangzhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lshangzhuang);
	left += 50;//250,330

	//��װ
	Ogre::StringVector  shangstyle;
	shangstyle.push_back(Ogre::DisplayString(L"����"));
	shangstyle.push_back(Ogre::DisplayString(L"T��"));
	OgreBites::SelectMenu *shangzhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Shangzhuang",Ogre::DisplayString(L"��ѡ��"),180,10,shangstyle);
	shangzhuang->getOverlayElement()->setHeight(50);
	shangzhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(shangzhuang);
	left -= 50;
	top += 60;//200,390

	//�����濪ʼ�������б�������ʾ�����ˣ��ҳ�������װѡ���ж�Ӽ���Ӷ�����ʾ���ĵ���Ҳ�ᱨ���ǲ����ڴ治����
	//��װ
	OgreBites::Label *lxiazhuang = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Xiazhuang",Ogre::DisplayString(L"��װ"),50);
	lxiazhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(lxiazhuang);
	left += 50;//250,330

	//��װ
	Ogre::StringVector  xiastyle;
	xiastyle.push_back(Ogre::DisplayString(L"mini-Skirt"));
	xiastyle.push_back(Ogre::DisplayString(L"Boshimiya-Skirt"));
	OgreBites::SelectMenu *xiazhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Xiazhuang",Ogre::DisplayString(L"��ѡ��"),180,10,xiastyle);
	xiazhuang->getOverlayElement()->setHeight(50);
	xiazhuang->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(xiazhuang);
	left -= 50;
	top += 60;//200,390

	//Ь��
	Label *lshoes = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Shoes",Ogre::DisplayString(L"Ь��"),50);
	lshoes->getOverlayElement()->setPosition(left,top);
	left += 50;//250,450
	this->mWidget_vec.push_back(lshoes);

	Ogre::StringVector  shoestyle;
	shoestyle.push_back(Ogre::DisplayString(L"song"));
	shoestyle.push_back(Ogre::DisplayString(L"gao"));
	OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_Shoes",Ogre::DisplayString(L"��ѡ��"),180,10,shoestyle);
	sshoes->getOverlayElement()->setHeight(50);
	sshoes->getOverlayElement()->setPosition(left,top);
	left -= 50;
	top += 60;//200��510
	this->mWidget_vec.push_back(sshoes);

	//��ʾ��ǰ�����ǩ
	OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_ShowImage",Ogre::DisplayString(L"��ǰ����"),100);
	showImage->getOverlayElement()->setPosition(630,100);
	this->mWidget_vec.push_back(showImage);
	//��ʾ����ռ�
	OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_Image","");
	image->getOverlayElement()->setDimensions(210,350);
	image->getOverlayElement()->setPosition(580,130);
	this->mWidget_vec.push_back(image);
	//image->getOverlayElement()->setMaterialName("");


	//������ɫ ��ť
	OgreBites::Button *createRole = mTrayMgr->createButton(OgreBites::TL_NONE,"createRole",Ogre::DisplayString(L"������ɫ"),100);
	createRole->getOverlayElement()->setDimensions(100,50);
	createRole->getOverlayElement()->setPosition(350,570);
	this->mWidget_vec.push_back(createRole);

	//ֱ�ӿ�ʼ��Ϸ��ť
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_role",Ogre::DisplayString(L"��ʼ��Ϸ"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(470,570);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//�˳���ť
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_role",Ogre::DisplayString(L"�˳�"),100);
	quitGame->getOverlayElement()->setDimensions(100,50);
	quitGame->getOverlayElement()->setPosition(590,570);
	this->mWidget_vec.push_back(quitGame);

    //�����ؼ�
}//startgame createhouse createrole gameset housed
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
	Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceStyle",Ogre::DisplayString(L"����"));
	l_danceStyle->getOverlayElement()->setDimensions(100,50);
	l_danceStyle->getOverlayElement()->setPosition(400,120);
	this->mWidget_vec.push_back(l_danceStyle);

	Ogre::StringVector danceStyle;
	danceStyle.push_back(Ogre::DisplayString(L"Latin"));
	danceStyle.push_back(Ogre::DisplayString(L"QiaQia"));
	SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceStyle",Ogre::DisplayString(L"��ѡ��"),180,10,danceStyle);
	s_danceStyle->getOverlayElement()->setDimensions(180,50);
	s_danceStyle->getOverlayElement()->setPosition(505,110);
	this->mWidget_vec.push_back(s_danceStyle);

	//���⿪ʼ������������б���û��Ӧ�ˣ�
	//����
	Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceSong",Ogre::DisplayString(L"����"));
	l_danceSong->getOverlayElement()->setDimensions(100,50);
	l_danceSong->getOverlayElement()->setPosition(400,200);
	this->mWidget_vec.push_back(l_danceSong);

	Ogre::StringVector danceSong;
	danceStyle.push_back(Ogre::DisplayString("SanFrancisco"));
	danceStyle.push_back(Ogre::DisplayString("Young For You"));
	SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceSong",Ogre::DisplayString(L"��ѡ��"),180,10,danceSong);
	s_danceSong->getOverlayElement()->setDimensions(180,50);
	s_danceSong->getOverlayElement()->setPosition(505,190);
	this->mWidget_vec.push_back(s_danceSong);

	//����
	Label *l_danceScence= mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceScence",Ogre::DisplayString(L"����"));
	l_danceScence->getOverlayElement()->setDimensions(100,50);
	l_danceScence->getOverlayElement()->setPosition(400,280);
	this->mWidget_vec.push_back(l_danceScence);

	Ogre::StringVector danceScence;
	danceStyle.push_back(Ogre::DisplayString("Sea"));
	danceStyle.push_back(Ogre::DisplayString("Road"));
	SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceScence",Ogre::DisplayString(L"��ѡ��"),180,10,danceScence);
	s_danceScence->getOverlayElement()->setDimensions(180,50);
	s_danceScence->getOverlayElement()->setPosition(505,270);
	this->mWidget_vec.push_back(s_danceScence);

	//����Ԥ��
	Label *l_danceView= mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceView",Ogre::DisplayString(L"����Ԥ��"));
	l_danceView->getOverlayElement()->setDimensions(100,50);
	l_danceView->getOverlayElement()->setPosition(502,350);
	this->mWidget_vec.push_back(l_danceView);

	OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceImage","");
	l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125,125,125));
	l_danceimage->getOverlayElement()->setDimensions(200,200);
	l_danceimage->getOverlayElement()->setPosition(450,400);
	l_danceimage->show();
	this->mWidget_vec.push_back(l_danceimage);


	//�޸Ľ�ɫ��ť
	OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE,"CorectRole_GameSet",Ogre::DisplayString(L"�޸Ľ�ɫ"),100);
	corectRole->getOverlayElement()->setDimensions(100,50);
	corectRole->getOverlayElement()->setPosition(370,620);
	this->mWidget_vec.push_back(corectRole);

	//ֱ�ӿ�ʼ��Ϸ��ť
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_GameSet",Ogre::DisplayString(L"��ʼ��Ϸ"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(490,620);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//�˳���ť
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_GameSet",Ogre::DisplayString(L"�˳�"),100);
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

	//������
	Label  *houseName = mTrayMgr->createLabel(OgreBites::TL_NONE,"HouseName",Ogre::DisplayString(L"��������"),100);
	this->mWidget_vec.push_back(houseName);
	houseName->getOverlayElement()->setDimensions(120,30);
	houseName->getOverlayElement()->setPosition(90,140);

	//��������
	Label  *danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"DanceStyle",Ogre::DisplayString(L"��Ϸ����"),100);
	this->mWidget_vec.push_back(danceStyle);
	danceStyle->getOverlayElement()->setDimensions(120,30);
	danceStyle->getOverlayElement()->setPosition(210,140);

	//ʣ����λ
	Label  *leftSeats = mTrayMgr->createLabel(OgreBites::TL_NONE,"LeftSeats",Ogre::DisplayString(L"ʣ����λ"),100);
	this->mWidget_vec.push_back(leftSeats);
    leftSeats->getOverlayElement()->setDimensions(120,30);
	leftSeats->getOverlayElement()->setPosition(330,140);

	//14����ʾ����ı�ǩ������
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


	//��ʱ��vector���������洢14����ʾ����ı�ǩ
	std::vector<OgreBites::Label *> mLabel_vec;
	Ogre::Real pTop = 170;
	for(int i = 0;i < 14;i++)
	{  
		//��14����ǩ������ʾ�������Ϣ
		mLabel_vec.push_back(mTrayMgr->createLabel(OgreBites::TL_NONE,labelString[i],"",360));
		mLabel_vec[i]->getOverlayElement()->setDimensions(360,30);
		mLabel_vec[i]->getOverlayElement()->setPosition(90,pTop);
		pTop += 30;
		this->mWidget_vec.push_back(mLabel_vec[i]);
	}

	//��ֱ�߻�������
	OgreBites::Separator *cutSeparator = mTrayMgr->createSeparator(OgreBites::TL_NONE,"Se_Cut",3);
	cutSeparator->getOverlayElement()->setHeight(450);
	cutSeparator->getOverlayElement()->setPosition(500,140);
	this->mWidget_vec.push_back(cutSeparator);

	
	//�����µķ���
	//��ǩ
	Label *creatNew = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_CreatNew",Ogre::DisplayString(L"�����·���"),120);
	creatNew->getOverlayElement()->setDimensions(120,30);
	creatNew->getOverlayElement()->setPosition(550,140);
	this->mWidget_vec.push_back(creatNew);
	
	//������¼λ�õı���
	Ogre::Real left,top;
	left = 600;
	top = 180;

	//�������Ʊ�ǩ
	Label *l_roomName = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_RoomName",Ogre::DisplayString(L"��������"),120);
	l_roomName->getOverlayElement()->setDimensions(120,30);
	l_roomName->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_roomName);
	top -= 10;
	left += 120;//left 670,top 130
	//�������������
	OgreBites::TextBox *t_roomName = mTrayMgr->createTextBox(OgreBites::TL_NONE,"T_RoomName",Ogre::DisplayString(L"�����뷿������"),200,50);
	t_roomName->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(t_roomName);
	left -= 120;
	top  += 70;//left 550,top 180

	//����
	//��ǩ
	Label *l_danceStyle = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceStyle",Ogre::DisplayString(L"����ѡ��"),120);
	l_danceStyle->getOverlayElement()->setDimensions(120,30);
	l_danceStyle->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceStyle);
	left += 120;
	top -= 10;//left 670,top 170

	//�����б�
	Ogre::StringVector v_danceStyle;
	v_danceStyle.push_back("Latin");
	v_danceStyle.push_back("QiaQia");
	OgreBites::SelectMenu *s_danceStyle = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceStyle",Ogre::DisplayString(L"����ѡ��"),200,5,v_danceStyle);
	s_danceStyle->getOverlayElement()->setDimensions(200,50);
	s_danceStyle->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceStyle);
	left -= 120;
	top  += 70;//left 550,top 220

	//����
	//��ǩ
	Label *l_danceSong = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceSong",Ogre::DisplayString(L"����ѡ��"),120);
	l_danceSong->getOverlayElement()->setDimensions(120,30);
	l_danceSong->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceSong);
	left += 120;
	top  -= 10;//left 670,top 210

	//�����б�
	Ogre::StringVector v_danceSong;
	v_danceSong.push_back("pretty");
	v_danceSong.push_back("lalala");
	OgreBites::SelectMenu *s_danceSong = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceSong",Ogre::DisplayString(L"����ѡ��"),200,5,v_danceSong);
	s_danceSong->getOverlayElement()->setDimensions(200,50);
	s_danceSong->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceSong);
	left -= 120;
	top  += 70;//left 550,top 260

	//����
	//��ǩ
	Label *l_danceScence = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_DanceScence",Ogre::DisplayString(L"����ѡ��"),120);
	l_danceScence->getOverlayElement()->setDimensions(120,30);
	l_danceScence->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceScence);
	left += 120;
	top  -= 10;//left 670,top 250

	//�����б�
	Ogre::StringVector v_danceScence;
	v_danceScence.push_back("seaside");
	v_danceScence.push_back("roadway");
	OgreBites::SelectMenu *s_danceScence = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_DanceScence",Ogre::DisplayString(L"����ѡ��"),200,5,v_danceScence);
	s_danceScence->getOverlayElement()->setDimensions(200,50);
	s_danceScence->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(s_danceScence);

	top  += 50;//left 670,top 300
	//����Ԥ��
	OgreBites::Label *l_danceimage = mTrayMgr->createLabel(OgreBites::TL_NONE,"DanceImage","");
	l_danceimage->getOverlayElement()->setColour(Ogre::ColourValue(125,125,125));
	l_danceimage->getOverlayElement()->setDimensions(200,200);
	l_danceimage->getOverlayElement()->setPosition(left,top);
	this->mWidget_vec.push_back(l_danceimage);

	//�޸Ľ�ɫ��ť
	OgreBites::Button *corectRole = mTrayMgr->createButton(OgreBites::TL_NONE,"CorectRole_CreateHouse",Ogre::DisplayString(L"�޸Ľ�ɫ"),100);
	corectRole->getOverlayElement()->setDimensions(100,50);
	corectRole->getOverlayElement()->setPosition(370,620);
	this->mWidget_vec.push_back(corectRole);

	//ֱ�ӿ�ʼ��Ϸ��ť
	OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE,"StartGame_CreateHouse",Ogre::DisplayString(L"��ʼ��Ϸ"),100);
	startGame->getOverlayElement()->setDimensions(100,50);
	startGame->getOverlayElement()->setPosition(490,620);
	this->mWidget_vec.push_back(startGame);
	
	//startGame->getOverlayElement()->setp
	//�˳���ť
	OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE,"QuitGame_CreateHouse",Ogre::DisplayString(L"�˳�"),100);
	quitGame->getOverlayElement()->setDimensions(100,50);
	quitGame->getOverlayElement()->setPosition(610,620);
	this->mWidget_vec.push_back(quitGame);

}//startgame createhouse createrole gameset housed

//�Ұѽ��뷿��ȴ����Ǹ�����ɾ���ˣ��û����÷���������ú���Ϸѡ���Ӧ��ֱ�ӽ���������Ǹ�����ȴ�����
/*void DancingGuiSys::setWidgetHoused()
{
    this->mCurrentWidgetType = Housed;

    //ɾ�����������еĿؼ�
    vector<OgreBites::Widget *>::iterator tempIte = this->mWidget_vec.begin();
    for (; tempIte != this->mWidget_vec.end(); ++tempIte)
    {
        this->mTrayMgr->destroyWidget(*tempIte);
    }
    //��ս���ؼ��б�
    mWidget_vec.clear();

    //8����λ��ǩ
	Ogre::StringVector seatName;
	seatName.push_back("seat_1");
	seatName.push_back("seat_2");
	seatName.push_back("seat_3");
	seatName.push_back("seat_4");
	seatName.push_back("seat_5");
	seatName.push_back("seat_6");
	seatName.push_back("seat_7");
	seatName.push_back("seat_8");
	
	//�洢��ǩ����ʾ������
	Ogre::StringVector seatString;
	seatString.push_back("1");
	seatString.push_back("2");
	seatString.push_back("3");
	seatString.push_back("4");
	seatString.push_back("5");
	seatString.push_back("6");
	seatString.push_back("7");
	seatString.push_back("8");

	//��ʱ��vector���������洢8����ʾΪ��λ�ı�ǩ
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

	//�����С��˳����͡��������ǡ��İ�ť�������⴦����������map��������
	if(btnName == Ogre::String("Quit") || btnName == Ogre::String("QuitGame_CreateHouse") || btnName == Ogre::String("QuitGame") || btnName == Ogre::String("QuitGame_role") ||btnName == Ogre::String("QuitGame_GameSet"))
	{
		mRoot->queueEndRendering();
	}
	else if(btnName == Ogre::String("AboutUs"))
	{
		mTrayMgr->showOkDialog(Ogre::DisplayString(L"��������"),Ogre::DisplayString("tell me about you"));
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
	//��checkbox�����жϣ�ʵ��������ֻ�ܵ��һ��
	if(boxName == Ogre::String("Box_Single"))
	{   
		//����Ϊ����ģʽ
		this->m_gameStyle = 1;
		if(box->isChecked())
		this->multiBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("Box_Multi"))
	{  
		//����Ϊ������ģʽ
		this->m_gameStyle = 2;
		if(box->isChecked())
		this->singleBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("C_SexM"))
	{
		//������
		//������ʾ�������󣬺�����δ���
		if(box->isChecked())
		this->femaleBox->setChecked(false,false);
	}
	else if(boxName == Ogre::String("C_SexF"))
	{
		//������
		//������ʾŮ�����󣬺�����δ���
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

	//�����;��������е�
	mPair.first = CreateRole;
	mPair.second = "StartGame_role";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;


	//����ģʽ������������ת
	if(m_gameStyle == 1)
	{
    //�ʼ���г���ʱ�Ľ���
    mPair.first =  BaseState;
    mPair.second = "StartGame";
	//�����ʼ��ť���Զ��л���������ɫ����
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

    //��ɫ������Ϻ󣬵��������ɫ����ת����Ϸ�趨
    mPair.first =  CreateRole;
    mPair.second = "createRole";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetGameSet;

    //��Ϸ�趨Ҳ���������ﻹҪ��ӷ�����һ�����ж��л�
    mPair.first =  GameSet;
    mPair.second = "CorectRole_GameSet";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

	//������Ϸ����-->��Ϸ��ʼ����
	mPair.first = GameSet;
	mPair.second = "StartGame_GameSet";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;
    
	//��Ϸ��ʼ����-->������Ϸ����
	mPair.first =  GameStart;
    mPair.second = "SetGame";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetGameSet;
	
	}
	else if(m_gameStyle == 2)
	{
		//������ʱ������ת
   //������ɫ��ת�����������ѡ�񷿼����
    mPair.first =  CreateRole;
    mPair.second = "createRole";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetCreateHouse;

	//�ɴ��������ѡ�񷿼�Ľ�����ת�ش�����ɫ����
    mPair.first =  CreateHouse;
    mPair.second = "CorectRole_CreateHouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateRole;

	////////////////////////////////////////////////////
	//��Ӧ������������Ϸ�Ľ���
	//�ڴ����÷����ֱ�ӵ����ʼ��Ϸ���������Ϸ��ʼ�Ľ�����
	mPair.first = CreateHouse;
	mPair.second = "StartGame_CreateHouse";
	this->mMap[mPair] = &DancingGuiSys::setGameStart;
    
	//��Ϸ��ʼ����-->ѡ��򴴽��������
	mPair.first = GameStart;
	mPair.second = "SelectHouse";
	this->mMap[mPair] = &DancingGuiSys::setWidgetCreateHouse;
	}
}
