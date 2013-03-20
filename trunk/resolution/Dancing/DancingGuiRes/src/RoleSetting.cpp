#include "DancingGuiSys.h"
#include "ClientConnect.h"
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
    mTextBox->setText( Ogre::DisplayString("wo"));
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
    hairstyle.push_back(Ogre::DisplayString("shorthire"));
    hairstyle.push_back(Ogre::DisplayString("longhire"));
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
    ringstyle.push_back(Ogre::DisplayString(L"earring"));
    ringstyle.push_back(Ogre::DisplayString(L"earstick"));
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
    shangstyle.push_back(Ogre::DisplayString(L"shiirt"));
    shangstyle.push_back(Ogre::DisplayString(L"Tshiirt"));
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
    xiastyle.push_back(Ogre::DisplayString(L"mini-Skirt"));
    xiastyle.push_back(Ogre::DisplayString(L"Boshimiya-Skirt"));
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
    shoestyle.push_back(Ogre::DisplayString(L"song"));
    shoestyle.push_back(Ogre::DisplayString(L"gao"));
    OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shoes", Ogre::DisplayString(L"��ѡ��"), 180, 10, shoestyle);
    sshoes->getOverlayElement()->setHeight(50);
    sshoes->getOverlayElement()->setPosition(left, top);
    left -= 50;
    top += 60;//200��510
    this->mWidget_vec.push_back(sshoes);

    //��ʾ��ǰ�����ǩ
    OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_ShowImage", Ogre::DisplayString(L"��ǰ����"), 100);
    showImage->getOverlayElement()->setPosition(630, 100);
    this->mWidget_vec.push_back(showImage);
    //��ʾ����ռ�
    OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Image", "");
    image->getOverlayElement()->setDimensions(210, 350);
    image->getOverlayElement()->setPosition(580, 130);
    this->mWidget_vec.push_back(image);
    //image->getOverlayElement()->setMaterialName("");


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

    //ֱ�ӿ�ʼ��Ϸ��ť
    OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_role", Ogre::DisplayString(L"��ʼ��Ϸ"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(470, 570);
    this->mWidget_vec.push_back(startGame);

    //startGame->getOverlayElement()->setp
    //�˳���ť
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_role", Ogre::DisplayString(L"�˳�"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(590, 570);
    this->mWidget_vec.push_back(quitGame);

    //�����ؼ�
}//startgame createhouse createrole gameset housed
void DancingGuiSys::changgeScene(string widgetName)
{

}