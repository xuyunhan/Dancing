#include "DancingGuiSys.h"

DancingGuiSys::DancingGuiSys(void)
{
}

DancingGuiSys::~DancingGuiSys(void)
{
}

DancingGuiSys::DancingGuiSys(OgreBites::SdkTrayManager *sdktraymanager)
{
    this->mTrayMgr = sdktraymanager;
    //默认状态
    mCurrentWidgetType = BaseState;
    this->ConfigGuiInfo();
}
void DancingGuiSys::setWidgetBaseState()
{
    this->mCurrentWidgetType = BaseState;
    this->mTrayMgr->destroyAllWidgets();
    mTrayMgr->showLogo(OgreBites::TL_TOPLEFT);



    Button *tempButton = this->mTrayMgr->createButton(OgreBites::TL_NONE, "startgame", "startgame");
    this->mWidget_vec.push_back(tempButton);

    this->mOverlayElement = tempButton->getOverlayElement();
    mOverlayElement->setPosition(100, 100);

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


    //新建控件
    Button *tempButton = this->mTrayMgr->createButton(OgreBites::TL_NONE, "createrole", "createrole");
    //置入界面控件列表
    this->mWidget_vec.push_back(tempButton);
    //设置控件位置
    tempButton->getOverlayElement()->setPosition(300, 300);


    //其他控件


}//startgame createhouse createrole gameset housed
void DancingGuiSys::setWidgetGameSet()
{
    this->mCurrentWidgetType = GameSet;
    this->mTrayMgr->destroyWidget(mButton);

    mButton = this->mTrayMgr->createButton(OgreBites::TL_NONE, "gameset", "gameset");

    mOverlayElement = mButton->getOverlayElement();
    mOverlayElement->setPosition(400, 400);


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


    Button *tempButton = this->mTrayMgr->createButton(OgreBites::TL_NONE, "createhouse", "createhouse");
    this->mWidget_vec.push_back(tempButton);

    mOverlayElement = tempButton->getOverlayElement();
    mOverlayElement->setPosition(200, 200);



}//startgame createhouse createrole gameset housed
void DancingGuiSys::setWidgetHoused()
{
    this->mCurrentWidgetType = Housed;
    this->mTrayMgr->destroyWidget(mButton);

    mButton = this->mTrayMgr->createButton(OgreBites::TL_NONE, "housed", "housed");

    mOverlayElement = mButton->getOverlayElement();
    mOverlayElement->setPosition(100, 100);

}

WidgetType DancingGuiSys::getCurrentWidgetType()
{
    return this->mCurrentWidgetType;
}
void DancingGuiSys::setCurrentWidgetType()
{
}


void DancingGuiSys::buttonHit(Button *button)
{
    mPair.first = this->mCurrentWidgetType;
    mPair.second = button->getName();
    functionPoint temp = this->mMap[mPair];
    (this->*temp)();
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
    //
    mPair.first =  BaseState;
    mPair.second = "startgame";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;
    //
    mPair.first =  CreateHouse;
    mPair.second = "createhouse";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetCreateHouse;
    //
    mPair.first =  CreateRole;
    mPair.second = "createrole";
    this->mMap[mPair]  =  &DancingGuiSys::setWidgetCreateRole;
    //
    mPair.first =  GameSet;
    mPair.second = "gameset";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetGameSet;
    //
    mPair.first =  Housed;
    mPair.second = "housed";
    this->mMap[mPair]  = &DancingGuiSys::setWidgetHoused;


}
