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
    * ��    �ܣ������濪ʼ��Ϸ����������䰴ť����Ҫ����һЩ��Ϣ
    *******************************************************************/
    /*******************************************************************
    * ��    �ܣ�����������䰴ť����Ҫ����һЩ��Ϣ,����ϵ����ˣ�newhouse.xml  myhouse.xml
    *******************************************************************/
    if(button->getName() == "CreateHouse"  || button->getName() == "StartGame_GameSet") //�����·������Ϣ
    {
        //����һ��XML���ĵ�����
        TiXmlDocument myDocument ;//= new TiXmlDocument();
        //����һ����Ԫ�ز����ӡ�
        TiXmlElement *RootElement = new TiXmlElement("houses");
        myDocument.LinkEndChild(RootElement);
        //����һ��PersonԪ�ز����ӡ�
        TiXmlElement *PersonElement = new TiXmlElement("house");
        RootElement->LinkEndChild(PersonElement);
        //����PersonԪ�ص����ԡ�

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
            myDocument.SaveFile("newhouse.xml");//���浽�ļ�
            ConnectManager::GetInstance()->Send("newhouse");
        }

    }
    /*******************************************************************
    * ��    �ܣ����汾����ɫ��Ϣ�������ǵ���ģʽ��������ģʽ��ּ�ڱ���role.xml�����跢����������
    *******************************************************************/
    if( button->getName() == "createRole_mut" || button->getName() == "createRole_sig")
    {
        //����һ��XML���ĵ�����
        TiXmlDocument myDocument;// = new TiXmlDocument();
        //����һ����Ԫ�ز����ӡ�
        TiXmlElement *RootElement = new TiXmlElement("roles");
        myDocument.LinkEndChild(RootElement);
        //����һ��PersonԪ�ز����ӡ�
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

        myDocument.SaveFile("myrole.xml");//���浽�ļ�
    }
    /*******************************************************************
    * ��    �ܣ��˳��û���ϢGameStart->SetGame����� = nothing();   SelectHouse-������
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
    * ��    �ܣ�������Ϸ  CreateHouse->StartGame_CreateHouse
    *******************************************************************/
    if(button->getName() == "StartGame_CreateHouse")
    {
        if(this->mWillHouse != "")
        {
            ConnectManager::GetInstance()->Send("login", this->mWillHouse);
        }
        else
        {
            mTrayMgr->showOkDialog(Ogre::DisplayString(L"���ڷ����б�ѡ�񷿼�����½����䣡"), Ogre::DisplayString(""));
            //fux addû��ѡ�񷿼����ʾ��Ϣ
            return;//Ӧ��ֱ��return�������Ͳ�����ת����
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
        //��ЩΪcreaterole�Ľ����ϵ������б�����֣�ͨ�����ǵĸı�����Ӧ��Ҳ����Ӧ�ĸı䣬�ʵ���changgeScene����
        DancingGuiSys::GetInstance()->changgeScene(menu->getName() );
    }
}
void GuiLisener::labelHit(Label *label)
{
    /*******************************************************************
    * ˵    ������Ҫ�����˷����б��ѡȡ
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    string tempstring = label->getName();
    const char *tempchar = tempstring.c_str();
    if(tempchar[5]  == '_')
    {
        //��ԭ��һ��������Ķ���
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

        //��ȡ������
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
    * ˵    ���������� ��Ůѡ��  ��ͨʵʱ��ģѡ�� ��������ѡ��������Ϣ
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    if(box == NULL)
        return;

    Ogre::String boxName = box->getName();

    //box->setChecked(true);
    //��checkbox�����жϣ�ʵ��������ֻ�ܵ��һ���Լ�������һ����ѡ��
    if(boxName == Ogre::String("Box_Single"))
    {
        //����Ϊ����ģʽ
        DancingGuiSys::GetInstance()->setGameStyle(1);        //this->m_gameStyle = 1;

        //licorice
        //ת��������ʾ�ĸ�������ɫ��ť,��������ʾ�����Ĵ�����ɫ��ť

        this->mTrayMgr->getWidget("createRole_sig")->show();
        this->mTrayMgr->getWidget("createRole_mut")->hide();

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Box_Multi");
        tempCheckBox->setChecked(false, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Box_Single");
        tempCheckBox->setChecked(true, false);
    }
    else if(boxName == Ogre::String("Box_Multi"))
    {
        //����Ϊ������ģʽ
        DancingGuiSys::GetInstance()->setGameStyle(2);// this->m_gameStyle = 2;

        //licorice
        //ת��������ʾ�ĸ�������ɫ��ť
        this->mTrayMgr->getWidget("createRole_sig")->hide();
        this->mTrayMgr->getWidget("createRole_mut")->show();

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Box_Multi");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Box_Single");
        tempCheckBox->setChecked(false, false);
    }
    else if(boxName == Ogre::String("C_SexM"))
    {
        //������
        //������ʾ�������󣬺�����δ���
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("C_SexM");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("C_SexF");
        tempCheckBox->setChecked(false, false);

        DancingGuiSys::GetInstance()->changgeScene(box->getName() );
    }
    else if(boxName == Ogre::String("C_SexF"))
    {
        //������
        //������ʾŮ�����󣬺�����δ���

        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("C_SexM");
        tempCheckBox->setChecked(false, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("C_SexF");
        tempCheckBox->setChecked(true, false);
        DancingGuiSys::GetInstance()->changgeScene(box->getName() );


    }
    else if(boxName == Ogre::String("Cartoon_Role"))
    {
        // this->m_roleStyle = 1;
        //����ͨ����
        CheckBox *tempCheckBox = (CheckBox *)this->mTrayMgr->getWidget("Cartoon_Role");
        tempCheckBox->setChecked(true, false);
        tempCheckBox = (CheckBox *) this->mTrayMgr->getWidget("Real_Role");
        tempCheckBox->setChecked(false, false);


        //��Ӧ�Ĳ���

    }
    else if(boxName == Ogre::String("Real_Role"))
    {
        // this->m_roleStyle = 2;
        //����ʵʱ��ģ

        //��Ӧ�Ĳ���
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
