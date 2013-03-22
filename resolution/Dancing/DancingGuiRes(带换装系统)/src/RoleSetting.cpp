#include "DancingGuiSys.h"

#include "Ogre.h"
#include "OgrePlugin.h"
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

	//licorice
	if(this->mWindow->isFullScreen())
	{
		//设置left和top
	}

    //局域网/单机模式的选择
    singleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Single", Ogre::DisplayString(L"单机模式"));
    singleBox->getOverlayElement()->setDimensions(100, 30);
    singleBox->getOverlayElement()->setPosition(850, 10);
    this->mWidget_vec.push_back(singleBox);
    if(this->m_gameStyle == 1)
        singleBox->setChecked(true, false);

    multiBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Multi", Ogre::DisplayString(L"局域网模式"));
    multiBox->getOverlayElement()->setDimensions(100, 30);
    multiBox->getOverlayElement()->setPosition(850, 50);
    this->mWidget_vec.push_back(multiBox);
    if(this->m_gameStyle == 2)
        multiBox->setChecked(true, false);

	//licorice
	//角色预制信息
	Label *lrolePre = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_RolePreSet",Ogre::DisplayString(L"已有角色"),100);
	lrolePre->getOverlayElement()->setPosition(left + 250,top-50);
	this->mWidget_vec.push_back(lrolePre);

	//先暂时用着这个，之后应该是从文件中读取已经存在的角色的名字，显示在下拉列表中
	Ogre::StringVector roleVector;
	roleVector.push_back("Nancy");
	roleVector.push_back("Lucy");
	SelectMenu *srolePre = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_RolePreSet",Ogre::DisplayString(L"请选择"),180,5,roleVector);
	srolePre->getOverlayElement()->setPosition(left+250+100,top-50);
	this->mWidget_vec.push_back(srolePre);

	///////////////////////////////////////////////////////////////////
    //昵称标签
    OgreBites::Label *lname = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Name", Ogre::DisplayString(L"昵称"), 50);
    lname->getOverlayElement()->setPosition(left, top - 50 );
    this->mWidget_vec.push_back(lname);
    left += 50; //250,90

    //输入昵称文本框
    //这里的文本框没有实现输入
    /*OgreBites::TextBox *tname = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name", Ogre::DisplayString(L"请输入"), 180, 70);
    tname->getOverlayElement()->setPosition(left, top - 20);
    tname->setText(Ogre::DisplayString(L"请输入你的昵称"));
    this->mWidget_vec.push_back(tname);

    mTextBox =  mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name", Ogre::DisplayString(L"请输入"), 180, 150);
    mTextBox->getOverlayElement()->setPosition(left, top - 100);
    mTextBox->setText(Ogre::DisplayString(L"请输入你的昵称"));
    this->mWidget_vec.push_back(mTextBox);
    left -= 50;
    top  += 60;//200,150*/
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name",  Ogre::DisplayString(L"请输入"), 180, 100);
    mTextBox->getOverlayElement()->setPosition(left, top - 50 );
    mTextBox->setText( Ogre::DisplayString(L"riririirirllllllll"));
    this->mWidget_vec.push_back(mTextBox);
    left -= 50;
    top  += 60;


    //性别标签
    OgreBites::Label *lsex = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Sex", Ogre::DisplayString(L"性别"), 50);
    lsex->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lsex);
    left += 50;//250,150

    //性别checkbox
    maleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexM", Ogre::DisplayString(L"男"), 60);
    maleBox->getOverlayElement()->setPosition(left, top);
	maleBox->setChecked(true, false);
    this->mWidget_vec.push_back(maleBox);
    left += 120;//370,150

    femaleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexF", Ogre::DisplayString(L"女"), 60);
    femaleBox->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(femaleBox);
    left -= 170;
    top += 60;//200,210

    //发型标签
    OgreBites::Label *lhair = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Hair", Ogre::DisplayString(L"发型"), 50);
    lhair->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lhair);
    left += 50;//250,210

    //发型下拉框
    Ogre::StringVector  hairstyle;
    hairstyle.push_back(Ogre::DisplayString("ShortHair"));
    hairstyle.push_back(Ogre::DisplayString("LongHair"));
	OgreBites::SelectMenu *shair = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Hair", Ogre::DisplayString(L"请选择"), 180, 10, hairstyle);
    shair->getOverlayElement()->setHeight(50);
    //shair->(0);
    shair->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(shair);
    left -= 50;
    top += 60;//200,270

    //配饰
    OgreBites::Label *lrings = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Rings", Ogre::DisplayString(L"配饰"), 50);
    lrings->getOverlayElement()->setPosition(left, top);
    left += 50;//250,270
    this->mWidget_vec.push_back(lrings);

    //配饰下拉框
    Ogre::StringVector  ringstyle;
    ringstyle.push_back(Ogre::DisplayString(L"耳环"));
    ringstyle.push_back(Ogre::DisplayString(L"耳钉"));
    OgreBites::SelectMenu *srings = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Rings", Ogre::DisplayString(L"请选择"), 180, 10, ringstyle);
    srings->getOverlayElement()->setHeight(50);
    srings->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(srings);
    left -= 50;
    top += 60;//200,330

    //上装
    OgreBites::Label *lshangzhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shangzhuang", Ogre::DisplayString(L"上装"), 50);
    lshangzhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lshangzhuang);
    left += 50;//250,330

    //上装
    Ogre::StringVector  shangstyle;
    shangstyle.push_back(Ogre::DisplayString("Overcoat"));
    shangstyle.push_back(Ogre::DisplayString("Sweater"));
    OgreBites::SelectMenu *shangzhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shangzhuang", Ogre::DisplayString(L"请选择"), 180, 10, shangstyle);
    shangzhuang->getOverlayElement()->setHeight(50);
    shangzhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(shangzhuang);
    left -= 50;
    top += 60;//200,390

    //从下面开始，下拉列表不能再显示中文了，我尝试在上装选项中多加几项，加多了显示中文的项也会报错，是不是内存不够？
    //下装
    OgreBites::Label *lxiazhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Xiazhuang", Ogre::DisplayString(L"下装"), 50);
    lxiazhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lxiazhuang);
    left += 50;//250,330

    //下装
    Ogre::StringVector  xiastyle;
    xiastyle.push_back(Ogre::DisplayString("Jeans"));
    xiastyle.push_back(Ogre::DisplayString("WhitePants"));
    OgreBites::SelectMenu *xiazhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Xiazhuang", Ogre::DisplayString(L"请选择"), 180, 10, xiastyle);
    xiazhuang->getOverlayElement()->setHeight(50);
    xiazhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(xiazhuang);
    left -= 50;
    top += 60;//200,390

    //鞋子
    Label *lshoes = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shoes", Ogre::DisplayString(L"鞋子"), 50);
    lshoes->getOverlayElement()->setPosition(left, top);
    left += 50;//250,450
    this->mWidget_vec.push_back(lshoes);

    Ogre::StringVector  shoestyle;
    shoestyle.push_back(Ogre::DisplayString("Leather"));
    shoestyle.push_back(Ogre::DisplayString("RunningShoes"));
    OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shoes", Ogre::DisplayString(L"请选择"), 180, 10, shoestyle);
    sshoes->getOverlayElement()->setHeight(50);
    sshoes->getOverlayElement()->setPosition(left, top);
    left -= 50;
    top += 60;//200，510
    this->mWidget_vec.push_back(sshoes);

    //显示当前形象标签
    OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_ShowImage", Ogre::DisplayString(L"当前形象"), 100);
    showImage->getOverlayElement()->setPosition(630, 150);
    this->mWidget_vec.push_back(showImage);
    //显示形象空间
    OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Image", "");
    image->getOverlayElement()->setDimensions(210, 400);
    image->getOverlayElement()->setPosition(580, 130);
    this->mWidget_vec.push_back(image);
    //image->getOverlayElement()->setMaterialName("");

	//实时建模和卡通形象
	role_cartoon = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Cartoon_Role",Ogre::DisplayString(L"卡通形象"),100);
	this->mWidget_vec.push_back(role_cartoon);
	role_cartoon->getOverlayElement()->setPosition(560,500);
	if(this->m_roleStyle == 1)
	role_cartoon->setChecked(true,false);

	role_real = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Real_Role",Ogre::DisplayString(L"实时建模"),100);
	this->mWidget_vec.push_back(role_real);
	role_real->getOverlayElement()->setPosition(700,500);
	if(this->m_roleStyle == 2)
	role_real->setChecked(true,false);


    //创建角色 按钮
    OgreBites::Button *createRole_sig = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_sig", Ogre::DisplayString(L"创建角色1"), 100);
    createRole_sig->getOverlayElement()->setDimensions(100, 50);
    createRole_sig->getOverlayElement()->setPosition(350, 570);
    this->mWidget_vec.push_back(createRole_sig);

    OgreBites::Button *createRole_mut = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_mut", Ogre::DisplayString(L"创建角色2"), 100);
    createRole_mut->getOverlayElement()->setDimensions(100, 50);
    createRole_mut->getOverlayElement()->setPosition(350, 570);
    this->mWidget_vec.push_back(createRole_mut);
    createRole_mut->hide();
	//createRole_mut->getOverlayElement()->hide();

	//licorice 删掉开始游戏按钮
    //直接开始游戏按钮
    /*OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_role", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(470, 570);
    this->mWidget_vec.push_back(startGame);*/

    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_role", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(590, 570);
    this->mWidget_vec.push_back(quitGame);

	//xuyunhan
	changgeScene("CreateRole");//生成默认的预览形象

    //其他控件
}//startgame createhouse createrole gameset housed

//xuyunhan
void DancingGuiSys::changgeScene(string widgetName)
{
	//根据男女变换选项
	if (widgetName == "C_SexF" || widgetName == "C_SexM" || widgetName == "CreateRole")
	{
		//获取选框
		OgreBites::SelectMenu * hairSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Hair");
		OgreBites::SelectMenu * upSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Shangzhuang");
		OgreBites::SelectMenu * downSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Xiazhuang");
		OgreBites::SelectMenu * shoesSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Shoes");

		if (femaleBox->isChecked())//若女
		{
			//上身
			upSelect->clearItems();//清空
			//添加
			upSelect->addItem("BrownSweater");
			upSelect->addItem("PinkSweater");

			//下身
			downSelect->clearItems();
			downSelect->addItem("DarkPants");
			downSelect->addItem("WhitePants");

			//鞋子
			shoesSelect->clearItems();
			shoesSelect->addItem("Boots");
			shoesSelect->addItem("WhiteShoes");
		}
		else if (maleBox->isChecked())//若男
		{
			//上身
			upSelect->clearItems();
			upSelect->addItem("Overcoat");
			upSelect->addItem("Sweater");

			//下身
			downSelect->clearItems();
			downSelect->addItem("Jeans");
			downSelect->addItem("WhitePants");

			//鞋子
			shoesSelect->clearItems();
			shoesSelect->addItem("Leather");
			shoesSelect->addItem("RunningShoes");
		}
		//获取当前选项
		Ogre::DisplayString hairName = hairSelect->getSelectedItem();
		Ogre::DisplayString upName = upSelect->getSelectedItem();
		Ogre::DisplayString downName = downSelect->getSelectedItem();
		Ogre::DisplayString shoesName = shoesSelect->getSelectedItem();

		//创建预览角色
		createPreviewImage(hairName,upName,downName,shoesName);

	}//男女变换end

	//若为配饰则无视
	else if (widgetName == "S_Rings")
	{
		;
	}
	//若为单项变换
	else
	{
		OgreBites::SelectMenu * widgetSelect = (OgreBites::SelectMenu *) this->mTrayMgr->getWidget(widgetName);//获取选框
		Ogre::DisplayString selectedName = widgetSelect->getSelectedItem();//获取当前选项
		createPreviewImage(widgetName,selectedName);//变换选择部分
	}
}

void DancingGuiSys::createPreviewImage(Ogre::String widgetName,Ogre::String selectedName)
{
	if (femaleBox->isChecked())//若女
	{
		if (widgetName == "S_Hair")
		{
			selectedName.insert(0,"First.Woman.Hair.");//第0位（也就是开头）插入字符串
			replaceEntity(entyHair,selectedName+".mesh");
			if (selectedName == "First.Woman.Hair.LongHair")
			{
				replaceEntity(entyForWomanLongHair,"First.Woman.Hair.PartforLongHair.mesh");
			}
		}
		else if (widgetName == "S_Shangzhuang")
		{
			selectedName.insert(0,"First.Woman.Up.");
			replaceEntity(entyUp,selectedName+".mesh");
		}
		else if (widgetName == "S_Xiazhuang")
		{
			selectedName.insert(0,"First.Woman.Down.");
			replaceEntity(entyDown,selectedName+".mesh");
		}
		else if (widgetName == "S_Shoes")
		{
			selectedName.insert(0,"First.Woman.Shoes.");
			replaceEntity(entyShoes_L,selectedName+".L.mesh");
			replaceEntity(entyShoes_R,selectedName+".R.mesh");
		}
	} 
	else if(maleBox->isChecked())//若男
	{
		if (widgetName == "S_Hair")
		{
			selectedName.insert(0,"First.Man.Hair.");//第0位（也就是开头）插入字符串
			replaceEntity(entyHair,selectedName+".mesh");
		}
		else if (widgetName == "S_Shangzhuang")
		{
			selectedName.insert(0,"First.Man.Up.");
			replaceEntity(entyUp,selectedName+".mesh");
		}
		else if (widgetName == "S_Xiazhuang")
		{
			selectedName.insert(0,"First.Man.Down.");
			replaceEntity(entyDown,selectedName+".mesh");
		}
		else if (widgetName == "S_Shoes")
		{
			selectedName.insert(0,"First.Man.Shoes.");
			replaceEntity(entyShoes_L,selectedName+".L.mesh");
			replaceEntity(entyShoes_R,selectedName+".R.mesh");
		}
	}
	
}

void DancingGuiSys::createPreviewImage(Ogre::String hairName,Ogre::String upName,Ogre::String downName,Ogre::String shoesName)
{
	createPreviewImage("S_Hair",hairName);
	createPreviewImage("S_Shangzhuang",upName);
	createPreviewImage("S_Xiazhuang",downName);
	createPreviewImage("S_Shoes",shoesName);
}

void DancingGuiSys::replaceEntity(Ogre::Entity * & entyReplaced,Ogre::String newEntyName)
{
	//获取场景管理器
	Ogre::SceneManager * sceneMgr = this->mRoot->getSceneManager("SceneManager");

	if (entyReplaced != NULL)//判断要替换的实体是否已经被创造，若被创造则销毁
	{
		entyReplaced->getParentSceneNode()->detachObject(entyReplaced->getName());//解除绑定
		sceneMgr->destroyEntity(entyReplaced);//销毁实体
	}

	entyReplaced = sceneMgr->createEntity(newEntyName);//创建实体
	sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(4.1,-2.5,60))->attachObject(entyReplaced);//绑定实体
}