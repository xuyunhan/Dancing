#include "DancingGuiSys.h"
#include "ClientConnect.h"
#include "Ogre.h"
#include "OgrePlugin.h"

/*******************************************************************
* 说    明：将DancingGuiSys的setWidgetCreateRole函数与changgeScene函数提了出来，单独为一个文件
                       该文件则主要负责角色设置部分的界面设定与模型显示
* 作    者： grius
* 日    期：2013年3月22日
*******************************************************************/
void DancingGuiSys::setWidgetCreateRole()
{
    //把局域网和单人模式的控件设为成员变量，控制界面跳转方式
    CheckBox  *singleBox;
    CheckBox  *multiBox;

    //男生角色，还是女生角色，决定游戏服装的选择
    CheckBox  *maleBox;
    CheckBox  *femaleBox;

    //卡通形象、实时建模的复选框
    CheckBox *role_cartoon;
    CheckBox *role_real;
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



    //局域网/单机模式的选择
    singleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Single", Ogre::DisplayString(L"单机模式"));
    singleBox->getOverlayElement()->setDimensions(100, 30);
    singleBox->getOverlayElement()->setPosition(this->mHorizontalCenter + 338, this->mVerticalCenter - 335);
    this->mWidget_vec.push_back(singleBox);
    if(this->m_gameStyle == 1)
        singleBox->setChecked(true, false);

    multiBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Box_Multi", Ogre::DisplayString(L"局域网模式"));
    multiBox->getOverlayElement()->setDimensions(100, 30);
    multiBox->getOverlayElement()->setPosition(this->mHorizontalCenter + 338, this->mVerticalCenter - 295);
    this->mWidget_vec.push_back(multiBox);
    if(this->m_gameStyle == 2)
        multiBox->setChecked(true, false);




    //licorice
    //角色预制信息
    Label *lrolePre = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_RolePreSet", Ogre::DisplayString(L"已有角色"), 100);
    lrolePre->getOverlayElement()->setPosition(this->mHorizontalCenter - 62,  this->mVerticalCenter - 295);
    this->mWidget_vec.push_back(lrolePre);

    //先暂时用着这个，之后应该是从文件中读取已经存在的角色的名字，显示在下拉列表中
    Ogre::StringVector roleVector;
    roleVector.push_back("Nancy");
    roleVector.push_back("Lucy");
    SelectMenu *srolePre = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_RolePreSet", Ogre::DisplayString(L"请选择"), 180, 5, roleVector);
    srolePre->getOverlayElement()->setPosition(this->mHorizontalCenter + 38, this->mVerticalCenter - 295);
    this->mWidget_vec.push_back(srolePre);

    //昵称标签
    OgreBites::Label *lname = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Name", Ogre::DisplayString(L"昵称"), 50);
    lname->getOverlayElement()->setPosition(this->mHorizontalCenter - 312, this->mVerticalCenter - 295 );
    this->mWidget_vec.push_back(lname);



    mTextBox = mTrayMgr->createTextBox(OgreBites::TL_NONE, "T_Name",  Ogre::DisplayString(L"请输入"), 180, 100);
    mTextBox->getOverlayElement()->setPosition(this->mHorizontalCenter - 265, this->mVerticalCenter - 295 );
    mTextBox->setText( Ogre::DisplayString("wo"));
    this->mWidget_vec.push_back(mTextBox);



    //性别标签
    OgreBites::Label *lsex = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Sex", Ogre::DisplayString(L"性别"), 50);
    lsex->getOverlayElement()->setPosition(this->mHorizontalCenter - 312, this->mVerticalCenter - 185);
    this->mWidget_vec.push_back(lsex);


    //性别checkbox
    maleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexM", Ogre::DisplayString(L"男"), 60);
    maleBox->getOverlayElement()->setPosition(this->mHorizontalCenter - 265, this->mVerticalCenter - 185);
    maleBox->setChecked(true, false);
    this->mWidget_vec.push_back(maleBox);


    femaleBox = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "C_SexF", Ogre::DisplayString(L"女"), 60);
    femaleBox->getOverlayElement()->setPosition(this->mHorizontalCenter - 142, this->mVerticalCenter - 185);
    this->mWidget_vec.push_back(femaleBox);


    //发型标签
    OgreBites::Label *lhair = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Hair", Ogre::DisplayString(L"发型"), 50);
    lhair->getOverlayElement()->setPosition(this->mHorizontalCenter - 312,  this->mVerticalCenter - 125);
    this->mWidget_vec.push_back(lhair);


    //发型下拉框
    Ogre::StringVector  hairstyle;
    hairstyle.push_back(Ogre::DisplayString("shorthire"));
    hairstyle.push_back(Ogre::DisplayString("longhire"));
    OgreBites::SelectMenu *shair = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Hair", Ogre::DisplayString(L"请选择"), 180, 10, hairstyle);
    shair->getOverlayElement()->setHeight(50);
    //shair->(0);
    shair->getOverlayElement()->setPosition(this->mHorizontalCenter - 265,  this->mVerticalCenter - 125);
    this->mWidget_vec.push_back(shair);


    //配饰
    OgreBites::Label *lrings = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Rings", Ogre::DisplayString(L"配饰"), 50);
    lrings->getOverlayElement()->setPosition(this->mHorizontalCenter - 312,  this->mVerticalCenter - 65);

    this->mWidget_vec.push_back(lrings);

    //配饰下拉框
    Ogre::StringVector  ringstyle;
    ringstyle.push_back(Ogre::DisplayString(L"earring"));
    ringstyle.push_back(Ogre::DisplayString(L"earstick"));
    OgreBites::SelectMenu *srings = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Rings", Ogre::DisplayString(L"请选择"), 180, 10, ringstyle);
    srings->getOverlayElement()->setHeight(50);
    srings->getOverlayElement()->setPosition(this->mHorizontalCenter - 265,  this->mVerticalCenter - 65);
    this->mWidget_vec.push_back(srings);


    //上装
    OgreBites::Label *lshangzhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shangzhuang", Ogre::DisplayString(L"上装"), 50);
    lshangzhuang->getOverlayElement()->setPosition(this->mHorizontalCenter - 312,  this->mVerticalCenter - 5);
    this->mWidget_vec.push_back(lshangzhuang);


    //上装
    Ogre::StringVector  shangstyle;
    shangstyle.push_back(Ogre::DisplayString(L"shiirt"));
    shangstyle.push_back(Ogre::DisplayString(L"Tshiirt"));
    OgreBites::SelectMenu *shangzhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shangzhuang", Ogre::DisplayString(L"请选择"), 180, 10, shangstyle);
    shangzhuang->getOverlayElement()->setHeight(50);
    shangzhuang->getOverlayElement()->setPosition(this->mHorizontalCenter - 265,  this->mVerticalCenter - 5);
    this->mWidget_vec.push_back(shangzhuang);



    //从下面开始，下拉列表不能再显示中文了，我尝试在上装选项中多加几项，加多了显示中文的项也会报错，是不是内存不够？
    //下装
    OgreBites::Label *lxiazhuang = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Xiazhuang", Ogre::DisplayString(L"下装"), 50);
    lxiazhuang->getOverlayElement()->setPosition(this->mHorizontalCenter - 312,  this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(lxiazhuang);


    //下装
    Ogre::StringVector  xiastyle;
    xiastyle.push_back(Ogre::DisplayString(L"mini-Skirt"));
    xiastyle.push_back(Ogre::DisplayString(L"Boshimiya-Skirt"));
    OgreBites::SelectMenu *xiazhuang = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Xiazhuang", Ogre::DisplayString(L"请选择"), 180, 10, xiastyle);
    xiazhuang->getOverlayElement()->setHeight(50);
    xiazhuang->getOverlayElement()->setPosition(this->mHorizontalCenter - 265,  this->mVerticalCenter + 55);
    this->mWidget_vec.push_back(xiazhuang);


    //鞋子
    Label *lshoes = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Shoes", Ogre::DisplayString(L"鞋子"), 50);
    lshoes->getOverlayElement()->setPosition(this->mHorizontalCenter - 312,  this->mVerticalCenter + 115);

    this->mWidget_vec.push_back(lshoes);

    Ogre::StringVector  shoestyle;
    shoestyle.push_back(Ogre::DisplayString(L"song"));
    shoestyle.push_back(Ogre::DisplayString(L"gao"));
    OgreBites::SelectMenu *sshoes = mTrayMgr->createThickSelectMenu(OgreBites::TL_NONE, "S_Shoes", Ogre::DisplayString(L"请选择"), 180, 10, shoestyle);
    sshoes->getOverlayElement()->setHeight(50);
    sshoes->getOverlayElement()->setPosition(this->mHorizontalCenter - 265,  this->mVerticalCenter + 115);

    this->mWidget_vec.push_back(sshoes);

    //显示当前形象标签
    OgreBites::Label *showImage = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_ShowImage", Ogre::DisplayString(L"当前形象"), 100);
    showImage->getOverlayElement()->setPosition(this->mHorizontalCenter + 118,  this->mVerticalCenter - 215);
    this->mWidget_vec.push_back(showImage);
    //显示形象空间
    OgreBites::Label *image = mTrayMgr->createLabel(OgreBites::TL_NONE, "L_Image", "");
    image->getOverlayElement()->setDimensions(210, 350);
    image->getOverlayElement()->setPosition(this->mHorizontalCenter + 68,  this->mVerticalCenter - 195);
    this->mWidget_vec.push_back(image);
    //image->getOverlayElement()->setMaterialName("");

    //实时建模和卡通形象
    role_cartoon = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Cartoon_Role", Ogre::DisplayString(L"卡通形象"), 100);
    this->mWidget_vec.push_back(role_cartoon);
    role_cartoon->getOverlayElement()->setPosition(this->mHorizontalCenter + 48,  this->mVerticalCenter + 155);
    // if(this->m_roleStyle == 1)
    role_cartoon->setChecked(true, false);

    role_real = mTrayMgr->createCheckBox(OgreBites::TL_NONE, "Real_Role", Ogre::DisplayString(L"实时建模"), 100);
    this->mWidget_vec.push_back(role_real);
    role_real->getOverlayElement()->setPosition(this->mHorizontalCenter + 188,  this->mVerticalCenter + 155);
    //if(this->m_roleStyle == 2)
    role_real->setChecked(false, false);


    //创建角色 按钮

    OgreBites::Button *createRole_sig = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_sig", Ogre::DisplayString(L"创建角色1"), 100);
    createRole_sig->getOverlayElement()->setDimensions(100, 50);
    createRole_sig->getOverlayElement()->setPosition(this->mHorizontalCenter - 162,  this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(createRole_sig);



    OgreBites::Button *createRole_mut = mTrayMgr->createButton(OgreBites::TL_NONE, "createRole_mut", Ogre::DisplayString(L"创建角色2"), 100);
    createRole_mut->getOverlayElement()->setDimensions(100, 50);
    createRole_mut->getOverlayElement()->setPosition(this->mHorizontalCenter - 162,  this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(createRole_mut);
    if(m_gameStyle == 1)
    {
        createRole_mut->hide();
    }
    if(m_gameStyle == 2)
    {
        createRole_sig->hide();

    }

    //直接开始游戏按钮
    /*OgreBites::Button *startGame = mTrayMgr->createButton(OgreBites::TL_NONE, "StartGame_role", Ogre::DisplayString(L"开始游戏"), 100);
    startGame->getOverlayElement()->setDimensions(100, 50);
    startGame->getOverlayElement()->setPosition(470, 570);
    this->mWidget_vec.push_back(startGame);*/

    //startGame->getOverlayElement()->setp
    //退出按钮
    OgreBites::Button *quitGame = mTrayMgr->createButton(OgreBites::TL_NONE, "QuitGame_role", Ogre::DisplayString(L"退出"), 100);
    quitGame->getOverlayElement()->setDimensions(100, 50);
    quitGame->getOverlayElement()->setPosition(this->mHorizontalCenter + 78,  this->mVerticalCenter + 275);
    this->mWidget_vec.push_back(quitGame);

    //其他控件
}//startgame createhouse createrole gameset housed
void DancingGuiSys::changgeScene(string widgetName)
{

}