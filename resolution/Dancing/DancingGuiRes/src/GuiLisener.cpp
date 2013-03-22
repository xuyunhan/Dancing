#include "DancingGuiSys.h"
#include "ClientConnect.h"
#include "GuiLisener.h"


GuiLisener::GuiLisener(void)
{
    mWillHouse = "";
}

GuiLisener::~GuiLisener(void)
{
}
void GuiLisener::buttonHit(Button *button)
{


    if(button == NULL)
        return;


    /*******************************************************************
    * 功    能：单机版开始游戏点击创建房间按钮，则要保存一些信息
    *******************************************************************/
    /*******************************************************************
    * 功    能：点击创建房间按钮，则要保存一些信息,并联系服务端，newhouse.xml  myhouse.xml
    *******************************************************************/
    if(button->getName() == "CreateHouse"  || button->getName() == "StartGame_GameSet") //创建新房间的信息
    {
        //创建一个XML的文档对象。
        TiXmlDocument myDocument ;//= new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("houses");
        myDocument.LinkEndChild(RootElement);
        //创建一个Person元素并连接。
        TiXmlElement *PersonElement = new TiXmlElement("house");
        RootElement->LinkEndChild(PersonElement);
        //设置Person元素的属性。

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
            myDocument.SaveFile("newhouse.xml");//保存到文件
            ConnectManager::GetInstance()->Send("newhouse");
        }

    }
    /*******************************************************************
    * 功    能：保存本机角色信息，无论是单机模式还是其他模式，旨在保存role.xml，无需发送至服务器
    *******************************************************************/
    if( button->getName() == "createRole_mut" || button->getName() == "createRole_sig")
    {
        //创建一个XML的文档对象。
        TiXmlDocument myDocument;// = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("roles");
        myDocument.LinkEndChild(RootElement);
        //创建一个Person元素并连接。
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

        myDocument.SaveFile("myrole.xml");//保存到文件
    }
    /*******************************************************************
    * 功    能：退出用户信息GameStart->SetGame局域的 = nothing();   SelectHouse-》局域
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
    * 功    能：加入游戏  CreateHouse->StartGame_CreateHouse
    *******************************************************************/
    if(button->getName() == "StartGame_CreateHouse")
    {
        if(this->mWillHouse != "")
        {
            ConnectManager::GetInstance()->Send("login", this->mWillHouse);
        }
        else
        {
            mTrayMgr->showOkDialog(Ogre::DisplayString(L"请在房间列表选择房间或者新建房间！"), Ogre::DisplayString(""));
            //fux add没有选择房间的提示信息
            return;//应该直接return，这样就不会跳转界面
        }
    }

    DancingGuiSys::GetInstance()->executeFunction(button->getName());




}
void GuiLisener::itemSelected(SelectMenu *menu)
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
        //这些为createrole的界面上的下拉列表的名字，通过他们的改变人物应该也做相应的改变，故调用changgeScene函数
        DancingGuiSys::GetInstance()->changgeScene(menu->getName() );
    }
}
void GuiLisener::labelHit(Label *label)
{
    /*******************************************************************
    * 说    明：主要处理了房间列表的选取
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    string tempstring = label->getName();
    const char *tempchar = tempstring.c_str();
    if(tempchar[5]  == '_')
    {
        //还原上一个被点击的东东
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

        //获取房间名
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
}
void GuiLisener::sliderMoved(Slider *slider)
{
}
void GuiLisener::checkBoxToggled(CheckBox *box)
{
    /*******************************************************************
    * 说    明：处理了 男女选择  卡通实时建模选择 单机局域选择的相关信息
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    if(box == NULL)
        return;

    Ogre::String boxName = box->getName();

    //box->setChecked(true);
    //对checkbox进行判断，实现两者中只能点击一个以及必须有一个被选中
    if(boxName == Ogre::String("Box_Single"))
    {
        //设置为单机模式
        DancingGuiSys::GetInstance()->setGameStyle(1);        //this->m_gameStyle = 1;

        //licorice
        //转换到底显示哪个创建角色按钮,单机下显示单机的创建角色按钮

        this->mTrayMgr->getWidget("createRole_sig")->show();
        this->mTrayMgr->getWidget("createRole_mut")->hide();

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Box_Multi");
        tempCheckBox->setChecked(false, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Box_Single");
        tempCheckBox->setChecked(true, false);
    }
    else if(boxName == Ogre::String("Box_Multi"))
    {
        //设置为局域网模式
        DancingGuiSys::GetInstance()->setGameStyle(2);// this->m_gameStyle = 2;

        //licorice
        //转换到底显示哪个创建角色按钮
        this->mTrayMgr->getWidget("createRole_sig")->hide();
        this->mTrayMgr->getWidget("createRole_mut")->show();

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Box_Multi");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Box_Single");
        tempCheckBox->setChecked(false, false);
    }
    else if(boxName == Ogre::String("C_SexM"))
    {
        //待处理
        //处理显示男生形象，函数尚未添加
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("C_SexM");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("C_SexF");
        tempCheckBox->setChecked(false, false);

        DancingGuiSys::GetInstance()->changgeScene(box->getName() );
    }
    else if(boxName == Ogre::String("C_SexF"))
    {
        //待处理
        //处理显示女生形象，函数尚未添加

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("C_SexM");
        tempCheckBox->setChecked(false, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("C_SexF");
        tempCheckBox->setChecked(true, false);
        DancingGuiSys::GetInstance()->changgeScene(box->getName() );


    }
    else if(boxName == Ogre::String("Cartoon_Role"))
    {
        // this->m_roleStyle = 1;
        //处理卡通形象
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Cartoon_Role");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Real_Role");
        tempCheckBox->setChecked(false, false);


        //对应的操作

    }
    else if(boxName == Ogre::String("Real_Role"))
    {
        // this->m_roleStyle = 2;
        //处理实时建模

        //对应的操作
        //this->setRealRoleValue();
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Cartoon_Role");
        tempCheckBox->setChecked(false, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Real_Role");
        tempCheckBox->setChecked(true, false);
    }
}
void GuiLisener::okDialogClosed(const Ogre::DisplayString &message)
{
}
void GuiLisener::yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit)
{
}
