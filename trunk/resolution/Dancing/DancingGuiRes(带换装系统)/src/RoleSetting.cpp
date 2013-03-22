#include "DancingGuiSys.h"

#include "Ogre.h"
#include "OgrePlugin.h"
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

	//licorice
	if(this->mWindow->isFullScreen())
	{
		//����left��top
	}

    //������/����ģʽ��ѡ��
    singleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Single", Ogre::DisplayString(L"����ģʽ"));
    singleBox->getOverlayElement()->setDimensions(100, 30);
    singleBox->getOverlayElement()->setPosition(850, 10);
    this->mWidget_vec.push_back(singleBox);
    if(this->m_gameStyle == 1)
        singleBox->setChecked(true, false);

    multiBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Multi", Ogre::DisplayString(L"������ģʽ"));
    multiBox->getOverlayElement()->setDimensions(100, 30);
    multiBox->getOverlayElement()->setPosition(850, 50);
    this->mWidget_vec.push_back(multiBox);
    if(this->m_gameStyle == 2)
        multiBox->setChecked(true, false);

	//licorice
	//��ɫԤ����Ϣ
	Label *lrolePre = mTrayMgr->createLabel(OgreBites::TL_NONE,"L_RolePreSet",Ogre::DisplayString(L"���н�ɫ"),100);
	lrolePre->getOverlayElement()->setPosition(left + 250,top-50);
	this->mWidget_vec.push_back(lrolePre);

	//����ʱ���������֮��Ӧ���Ǵ��ļ��ж�ȡ�Ѿ����ڵĽ�ɫ�����֣���ʾ�������б���
	Ogre::StringVector roleVector;
	roleVector.push_back("Nancy");
	roleVector.push_back("Lucy");
	SelectMenu *srolePre = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE,"S_RolePreSet",Ogre::DisplayString(L"��ѡ��"),180,5,roleVector);
	srolePre->getOverlayElement()->setPosition(left+250+100,top-50);
	this->mWidget_vec.push_back(srolePre);

	///////////////////////////////////////////////////////////////////
    //�ǳƱ�ǩ
    OgreBites::Label *lname = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Name", Ogre::DisplayString(L"�ǳ�"), 50);
    lname->getOverlayElement()->setPosition(left, top - 50 );
    this->mWidget_vec.push_back(lname);
    left += 50; //250,90

    //�����ǳ��ı���
    //������ı���û��ʵ������
    /*OgreBites::TextBox *tname = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name", Ogre::DisplayString(L"������"), 180, 70);
    tname->getOverlayElement()->setPosition(left, top - 20);
    tname->setText(Ogre::DisplayString(L"����������ǳ�"));
    this->mWidget_vec.push_back(tname);

    mTextBox =  mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name", Ogre::DisplayString(L"������"), 180, 150);
    mTextBox->getOverlayElement()->setPosition(left, top - 100);
    mTextBox->setText(Ogre::DisplayString(L"����������ǳ�"));
    this->mWidget_vec.push_back(mTextBox);
    left -= 50;
    top  += 60;//200,150*/
    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name",  Ogre::DisplayString(L"������"), 180, 100);
    mTextBox->getOverlayElement()->setPosition(left, top - 50 );
    mTextBox->setText( Ogre::DisplayString(L"riririirirllllllll"));
    this->mWidget_vec.push_back(mTextBox);
    left -= 50;
    top  += 60;


    //�Ա��ǩ
    OgreBites::Label *lsex = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Sex", Ogre::DisplayString(L"�Ա�"), 50);
    lsex->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lsex);
    left += 50;//250,150

    //�Ա�checkbox
    maleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexM", Ogre::DisplayString(L"��"), 60);
    maleBox->getOverlayElement()->setPosition(left, top);
	maleBox->setChecked(true, false);
    this->mWidget_vec.push_back(maleBox);
    left += 120;//370,150

    femaleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexF", Ogre::DisplayString(L"Ů"), 60);
    femaleBox->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(femaleBox);
    left -= 170;
    top += 60;//200,210

    //���ͱ�ǩ
    OgreBites::Label *lhair = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Hair", Ogre::DisplayString(L"����"), 50);
    lhair->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lhair);
    left += 50;//250,210

    //����������
    Ogre::StringVector  hairstyle;
    hairstyle.push_back(Ogre::DisplayString("ShortHair"));
    hairstyle.push_back(Ogre::DisplayString("LongHair"));
	OgreBites::SelectMenu *shair = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Hair", Ogre::DisplayString(L"��ѡ��"), 180, 10, hairstyle);
    shair->getOverlayElement()->setHeight(50);
    //shair->(0);
    shair->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(shair);
    left -= 50;
    top += 60;//200,270

    //����
    OgreBites::Label *lrings = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Rings", Ogre::DisplayString(L"����"), 50);
    lrings->getOverlayElement()->setPosition(left, top);
    left += 50;//250,270
    this->mWidget_vec.push_back(lrings);

    //����������
    Ogre::StringVector  ringstyle;
    ringstyle.push_back(Ogre::DisplayString(L"����"));
    ringstyle.push_back(Ogre::DisplayString(L"����"));
    OgreBites::SelectMenu *srings = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Rings", Ogre::DisplayString(L"��ѡ��"), 180, 10, ringstyle);
    srings->getOverlayElement()->setHeight(50);
    srings->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(srings);
    left -= 50;
    top += 60;//200,330

    //��װ
    OgreBites::Label *lshangzhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shangzhuang", Ogre::DisplayString(L"��װ"), 50);
    lshangzhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lshangzhuang);
    left += 50;//250,330

    //��װ
    Ogre::StringVector  shangstyle;
    shangstyle.push_back(Ogre::DisplayString("Overcoat"));
    shangstyle.push_back(Ogre::DisplayString("Sweater"));
    OgreBites::SelectMenu *shangzhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shangzhuang", Ogre::DisplayString(L"��ѡ��"), 180, 10, shangstyle);
    shangzhuang->getOverlayElement()->setHeight(50);
    shangzhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(shangzhuang);
    left -= 50;
    top += 60;//200,390

    //�����濪ʼ�������б�������ʾ�����ˣ��ҳ�������װѡ���ж�Ӽ���Ӷ�����ʾ���ĵ���Ҳ�ᱨ���ǲ����ڴ治����
    //��װ
    OgreBites::Label *lxiazhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Xiazhuang", Ogre::DisplayString(L"��װ"), 50);
    lxiazhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(lxiazhuang);
    left += 50;//250,330

    //��װ
    Ogre::StringVector  xiastyle;
    xiastyle.push_back(Ogre::DisplayString("Jeans"));
    xiastyle.push_back(Ogre::DisplayString("WhitePants"));
    OgreBites::SelectMenu *xiazhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Xiazhuang", Ogre::DisplayString(L"��ѡ��"), 180, 10, xiastyle);
    xiazhuang->getOverlayElement()->setHeight(50);
    xiazhuang->getOverlayElement()->setPosition(left, top);
    this->mWidget_vec.push_back(xiazhuang);
    left -= 50;
    top += 60;//200,390

    //Ь��
    Label *lshoes = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shoes", Ogre::DisplayString(L"Ь��"), 50);
    lshoes->getOverlayElement()->setPosition(left, top);
    left += 50;//250,450
    this->mWidget_vec.push_back(lshoes);

    Ogre::StringVector  shoestyle;
    shoestyle.push_back(Ogre::DisplayString("Leather"));
    shoestyle.push_back(Ogre::DisplayString("RunningShoes"));
    OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shoes", Ogre::DisplayString(L"��ѡ��"), 180, 10, shoestyle);
    sshoes->getOverlayElement()->setHeight(50);
    sshoes->getOverlayElement()->setPosition(left, top);
    left -= 50;
    top += 60;//200��510
    this->mWidget_vec.push_back(sshoes);

    //��ʾ��ǰ�����ǩ
    OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_ShowImage", Ogre::DisplayString(L"��ǰ����"), 100);
    showImage->getOverlayElement()->setPosition(630, 150);
    this->mWidget_vec.push_back(showImage);
    //��ʾ����ռ�
    OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Image", "");
    image->getOverlayElement()->setDimensions(210, 400);
    image->getOverlayElement()->setPosition(580, 130);
    this->mWidget_vec.push_back(image);
    //image->getOverlayElement()->setMaterialName("");

	//ʵʱ��ģ�Ϳ�ͨ����
	role_cartoon = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Cartoon_Role",Ogre::DisplayString(L"��ͨ����"),100);
	this->mWidget_vec.push_back(role_cartoon);
	role_cartoon->getOverlayElement()->setPosition(560,500);
	if(this->m_roleStyle == 1)
	role_cartoon->setChecked(true,false);

	role_real = mTrayMgr->createCheckBox(OgreBites::TL_NONE,"Real_Role",Ogre::DisplayString(L"ʵʱ��ģ"),100);
	this->mWidget_vec.push_back(role_real);
	role_real->getOverlayElement()->setPosition(700,500);
	if(this->m_roleStyle == 2)
	role_real->setChecked(true,false);


    //������ɫ ��ť
    OgreBites::Button *createRole_sig = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_sig", Ogre::DisplayString(L"������ɫ1"), 100);
    createRole_sig->getOverlayElement()->setDimensions(100, 50);
    createRole_sig->getOverlayElement()->setPosition(350, 570);
    this->mWidget_vec.push_back(createRole_sig);

    OgreBites::Button *createRole_mut = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_mut", Ogre::DisplayString(L"������ɫ2"), 100);
    createRole_mut->getOverlayElement()->setDimensions(100, 50);
    createRole_mut->getOverlayElement()->setPosition(350, 570);
    this->mWidget_vec.push_back(createRole_mut);
    createRole_mut->hide();
	//createRole_mut->getOverlayElement()->hide();

	//licorice ɾ����ʼ��Ϸ��ť
    //ֱ�ӿ�ʼ��Ϸ��ť
    /*OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_role", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(470, 570);
    this->mWidget_vec.push_back(startGame);*/

    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_role", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(590, 570);
    this->mWidget_vec.push_back(quitGame);

	//xuyunhan
	changgeScene("CreateRole");//����Ĭ�ϵ�Ԥ������

    //�����ؼ�
}//startgame createhouse createrole gameset housed

//xuyunhan
void DancingGuiSys::changgeScene(string widgetName)
{
	//������Ů�任ѡ��
	if (widgetName == "C_SexF" || widgetName == "C_SexM" || widgetName == "CreateRole")
	{
		//��ȡѡ��
		OgreBites::SelectMenu * hairSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Hair");
		OgreBites::SelectMenu * upSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Shangzhuang");
		OgreBites::SelectMenu * downSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Xiazhuang");
		OgreBites::SelectMenu * shoesSelect =(OgreBites::SelectMenu *) this->mTrayMgr->getWidget("S_Shoes");

		if (femaleBox->isChecked())//��Ů
		{
			//����
			upSelect->clearItems();//���
			//���
			upSelect->addItem("BrownSweater");
			upSelect->addItem("PinkSweater");

			//����
			downSelect->clearItems();
			downSelect->addItem("DarkPants");
			downSelect->addItem("WhitePants");

			//Ь��
			shoesSelect->clearItems();
			shoesSelect->addItem("Boots");
			shoesSelect->addItem("WhiteShoes");
		}
		else if (maleBox->isChecked())//����
		{
			//����
			upSelect->clearItems();
			upSelect->addItem("Overcoat");
			upSelect->addItem("Sweater");

			//����
			downSelect->clearItems();
			downSelect->addItem("Jeans");
			downSelect->addItem("WhitePants");

			//Ь��
			shoesSelect->clearItems();
			shoesSelect->addItem("Leather");
			shoesSelect->addItem("RunningShoes");
		}
		//��ȡ��ǰѡ��
		Ogre::DisplayString hairName = hairSelect->getSelectedItem();
		Ogre::DisplayString upName = upSelect->getSelectedItem();
		Ogre::DisplayString downName = downSelect->getSelectedItem();
		Ogre::DisplayString shoesName = shoesSelect->getSelectedItem();

		//����Ԥ����ɫ
		createPreviewImage(hairName,upName,downName,shoesName);

	}//��Ů�任end

	//��Ϊ����������
	else if (widgetName == "S_Rings")
	{
		;
	}
	//��Ϊ����任
	else
	{
		OgreBites::SelectMenu * widgetSelect = (OgreBites::SelectMenu *) this->mTrayMgr->getWidget(widgetName);//��ȡѡ��
		Ogre::DisplayString selectedName = widgetSelect->getSelectedItem();//��ȡ��ǰѡ��
		createPreviewImage(widgetName,selectedName);//�任ѡ�񲿷�
	}
}

void DancingGuiSys::createPreviewImage(Ogre::String widgetName,Ogre::String selectedName)
{
	if (femaleBox->isChecked())//��Ů
	{
		if (widgetName == "S_Hair")
		{
			selectedName.insert(0,"First.Woman.Hair.");//��0λ��Ҳ���ǿ�ͷ�������ַ���
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
	else if(maleBox->isChecked())//����
	{
		if (widgetName == "S_Hair")
		{
			selectedName.insert(0,"First.Man.Hair.");//��0λ��Ҳ���ǿ�ͷ�������ַ���
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
	//��ȡ����������
	Ogre::SceneManager * sceneMgr = this->mRoot->getSceneManager("SceneManager");

	if (entyReplaced != NULL)//�ж�Ҫ�滻��ʵ���Ƿ��Ѿ������죬��������������
	{
		entyReplaced->getParentSceneNode()->detachObject(entyReplaced->getName());//�����
		sceneMgr->destroyEntity(entyReplaced);//����ʵ��
	}

	entyReplaced = sceneMgr->createEntity(newEntyName);//����ʵ��
	sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(4.1,-2.5,60))->attachObject(entyReplaced);//��ʵ��
}