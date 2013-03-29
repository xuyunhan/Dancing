#include "Dancing.h"
#include "DotSceneLoader.h"
#include "Timer.h"

Dancing::Dancing(void)
{
    mSoundMgr = SoundManager::createManager();
    mSoundMgr->init();

}

Dancing::~Dancing(void)
{
}



bool Dancing::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    // don't do all these calculations when sample's running or when in configuration screen or when no samples loaded
    BasicApplication::frameRenderingQueued(evt);
    /*******************************************************************
    * 说    明：判断是否以开始游戏，若开始则多少秒后停止，多少秒取决于舞曲的长短
    * 作    者： grius
    * 日    期：2013年3月27日
    *******************************************************************/
    if (DancingGuiSys::GetInstance()->getIsOnGame())
    {
        int i = DancingTimer::timerForReady->getMilliseconds() * 0.001;
        if(i > 10) //10代表舞曲的长短
        {
            mSoundMgr->stopAudio(mAudioId  );
            mSoundMgr->releaseAudio( mAudioId );
            DancingGuiSys::GetInstance()->setIsOnGame(false);
			for(int i = 0; i < 5; i++)
            {
				mAnimState[i]->setTimePosition(0);//(evt.timeSinceLastFrame);//动画动起来
            }
        }
        else
        {
            for(int i = 0; i < 5; i++)
            {
                mAnimState[i]->addTime(evt.timeSinceLastFrame);//动画动起来
            }
        }
    }
    /*******************************************************************
    * 说    明：判断是否已经准备，若准备则开始倒计时，并在倒计时结束时开始动画，音乐等元素
    * 作    者： grius
    * 日    期：2013年3月27日
    *******************************************************************/
    if (DancingGuiSys::GetInstance()->getIsSingleReady()  ||
            DancingGuiSys::GetInstance()->getIsMutiOtherReady() ||
            (DancingGuiSys::GetInstance()->getIsMutiReady() && DancingGuiSys::GetInstance()->getIsHaveOtherRole()))
    {
        int i = DancingTimer::timerForReady->getMilliseconds() * 0.001;
        //Ogre::MovableText *tempText = (Ogre::MovableText *) this->mTrayMgr->getWidget("readyText");
        if ( i < 10)
        {
            i = 10 - i;
            char a[3];
            itoa(i, a, 10);
            mTextForReady->setCaption ( Ogre::DisplayString(a));
        }
        else
        {
            DancingGuiSys::GetInstance()->setIsSingleReady(false);
            DancingGuiSys::GetInstance()->setIsMutiReady(false);
            DancingGuiSys::GetInstance()->setIsMutiOtherReady(false);
            mTextForReady->setPositionOffset(Ogre::Vector3(100, 100, 100));
            DancingTimer::timerForReady->reset();//准备正式开场

            // mAudioId = 1;

            mSoundMgr->loadAudio( "three.ogg", &mAudioId, true);
            mSoundMgr->playAudio( mAudioId, true );

            DancingGuiSys::GetInstance()->setIsOnGame(true);

        }
    }
    /*******************************************************************
    * 说    明：跳转场景
    * 作    者： grius
    * 日    期：2013年3月27日
    *******************************************************************/
    if (DancingGuiSys::GetInstance()->getCurrentTypeChanged())
    {

        switch(DancingGuiSys::GetInstance()->getCurrentWidgetType())
        {
        case BaseState:
            break;

        case  CreateRole:
            this->createSceneForCreateRole();
            break;

        case  GameSet:
            this->createSceneForGameSet();
            break;

        case  CreateHouse:
            this->createSceneForCreateHouse();
            break;

        case  GameStart:
            this->createSceneForGameStart();


            break;

        case  GamePractise:
            this->createSceneForGamePractise();
            break;

        case GameOver:
            break;
        default:
            break;
        }

        DancingGuiSys::GetInstance()->setCurrentTypeChanged(false);
    }

    return true;
}
void Dancing::createSceneForGamePractise()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();//getRootSceneNode()->();
}
void Dancing::createSceneForCreateRole()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->destroyAllLights();
    mSceneMgr->clearScene();//getRootSceneNode()->();

    DancingGuiSys::GetInstance()->clearEntityPoint();




    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 0, 80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);

    Ogre::Light *l = mSceneMgr->createLight("MainLigh1t");
    l->setPosition(20, 80, 50);
    Ogre::Light *lightForPreview = mSceneMgr->createLight("LightForPreview");
    lightForPreview->setPosition(25, 75, 110);

    /*    //xuyunhan

       Ogre::Entity *house = mSceneMgr->createEntity("House", "Box33.mesh");

       mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(house);
       //缩放
       house->getParentSceneNode()->scale(0.0035, 0.0035, 0.0035);
       //旋转

       Ogre::Quaternion x( Ogre::Degree( 20 ), Ogre::Vector3::UNIT_X ); //左到右为轴
       Ogre::Quaternion y( Ogre::Degree( -45 ), Ogre::Vector3::UNIT_Y );
       house->getParentSceneNode()->rotate(x);
       house->getParentSceneNode()->rotate(y);
       //给太暗的招牌补光
       Ogre::Light *lightForLogo = mSceneMgr->createLight("LightForLogo");
       lightForLogo->setPosition(-20, 0, 20);
      */
    //xuyunhan
    DancingGuiSys::GetInstance()->changgeScene("CreateRole");//生成默认的预览形象


}
void Dancing::createSceneForWelcome()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();//getRootSceneNode()->();

    /* Ogre::Entity *tempEntity = mSceneMgr->createEntity("start", "Box33.mesh");
     this->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(tempEntity);
     //场景实体的缩放：
     // tempEntity->getParentSceneNode()->scale(0.1, 0.1, 0.1);

     //摄影机的位置：
     mCamera->setPosition(Ogre::Vector3(1500, 600, 1600));

     //摄影机lookat的位置
     mCamera->lookAt(Ogre::Vector3(50, -40, 50));

     //增加的灯光的位置：
     Ogre::Light *PointLight = mSceneMgr->createLight("PointLight");
     PointLight->setPosition(500, 0, 1100);  */


}
void Dancing::createSceneForCreateHouse()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();//getRootSceneNode()->();
}
void Dancing::createSceneForGameSet()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();//getRootSceneNode()->();
}

void Dancing::createSceneForGameStart()
{

    /*******************************************************************
    * 说    明：设置镜头
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    mCamera->setPosition(Ogre::Vector3(0, 3, 10));
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);

    Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("start");

    // 设置关键帧之间的插值方法为样条插值
    Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_SPLINE);

    /*******************************************************************
    * 说    明：设置场景 从XML中读取信息
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    {
        TiXmlDocument  myDocument ;//= new TiXmlDocument();
        myDocument.LoadFile("myhouse.xml");
        TiXmlElement *RootElement = myDocument.RootElement();
        TiXmlElement *FirstPerson = RootElement->FirstChildElement();
        string tempHouseName;
        if(FirstPerson != 0)
        {
            tempHouseName = FirstPerson->Attribute("dancescene");
            DotSceneLoader loader;
            loader.parseDotScene(tempHouseName + ".scene", "General", mSceneMgr);

        }
    }
    /*******************************************************************
    * 说    明：从XML中读取角色信息
    * 作    者： grius
    * 日    期：2013年3月26日
    *******************************************************************/
    Ogre::SceneNode *leftPeopleSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *rightPeopleSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    leftPeopleSceneNode->setPosition(-2.5, 0, 0);
    rightPeopleSceneNode->setPosition(2.5, 0, 0);

    /*
    First.Man.Hair.ShortHair
    First.Man.Hair.LongHair
    First.Man.Up.Sweater
    First.Man.Up.Overcoat
    First.Man.Down.Jeans
    First.Man.Down.WhitePants
    First.Man.Shoes.Leather.R
    First.Man.Shoes.Leather.L
    First.Man.Shoes.RunningShoes.R
    First.Man.Shoes.RunningShoes.L

    First.Woman.Head.LongHair
    First.Woman.Head.ShortHair
    First.Woman.Hair.PartforLongHair
    First.Woman.Up.PinkSweater
    First.Woman.Up.BrownSweater
    First.Woman.Down.DarkPants
    First.Woman.Down.WhitePants
    First.Woman.Shoes.WhiteShoes.L
    First.Woman.Shoes.WhiteShoes.R
    First.Woman.Shoes.Boots.L
    First.Woman.Shoes.Boots.R
    */

    Ogre::Entity *tempEntity;
    Ogre::SceneNode *tempSceneNode;
    string tempRoleName;
    string tempRoleSex;
    string tempRoleHire;
    string tempRoleUpware;
    string tempRoleDownware;
    string tempRoleShoe;
    string tempForEntity;

    {
        //myrole


        TiXmlDocument  myDocument ;//= new TiXmlDocument();
        myDocument.LoadFile("myrole.xml");
        TiXmlElement *RootElement = myDocument.RootElement();
        if(RootElement)
        {
            TiXmlElement *FirstPerson = RootElement->FirstChildElement();

            if(FirstPerson != 0)
            {
                //tempHouseName = FirstPerson->Attribute("dancescene");
                tempRoleName = FirstPerson->Attribute("name");
                tempRoleSex = FirstPerson->Attribute("sex");
                tempRoleHire = FirstPerson->Attribute("hire");
                tempRoleUpware = FirstPerson->Attribute("upware");
                tempRoleDownware = FirstPerson->Attribute("downware");
                tempRoleShoe = FirstPerson->Attribute("shoe");

                if(tempRoleSex == "1" )
                    tempForEntity = "Man";
                else
                    tempForEntity = "Woman";
                //left
                tempEntity = mSceneMgr->createEntity("lefthead",  tempForEntity + ".Hair." + tempRoleHire + ".mesh");
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[0] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[0]->setLoop(true);
                mAnimState[0]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("leftwear",  tempForEntity + ".Up." + tempRoleUpware + ".mesh");
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[1] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[1]->setLoop(true);
                mAnimState[1]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("leftpant",  tempForEntity + ".Down." + tempRoleDownware + ".mesh");
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[2] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[2]->setLoop(true);
                mAnimState[2]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("leftshoeR",  tempForEntity + ".Shoes." + tempRoleShoe + ".R.mesh");
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[3] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[3]->setLoop(true);
                mAnimState[3]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("leftshoeL",  tempForEntity + ".Shoes." + tempRoleShoe + ".L.mesh");
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[4] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[4]->setLoop(true);
                mAnimState[4]->setEnabled(true);

                //licorice--显示人物名字
                Vector3 temp = leftPeopleSceneNode->getPosition();
                Vector3 name ;
                name.x = temp.x + 2.7;
                name.y = temp.y + 6.0;
                name.z = temp.z;

                Ogre::MovableText *roleLeft = new Ogre::MovableText("RoleLeft", tempRoleName, "SdkTrays/Caption", 0.3f);
                roleLeft->showOnTop(true);
                roleLeft->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE);
                //Vector3(0.5,6.1,0)
                tempSceneNode = leftPeopleSceneNode->createChildSceneNode(name);
                tempSceneNode->attachObject(roleLeft);
            }
        }



    }
    {
        TiXmlDocument  myDocument ;//= new TiXmlDocument();
        myDocument.LoadFile("otherrole.xml");
        TiXmlElement *RootElement = myDocument.RootElement();
        if(RootElement)
        {
            TiXmlElement *FirstPerson = RootElement->FirstChildElement();

            if(FirstPerson != 0)
            {
                //tempHouseName = FirstPerson->Attribute("dancescene");
                tempRoleName = FirstPerson->Attribute("name");
                tempRoleSex = FirstPerson->Attribute("sex");
                tempRoleHire = FirstPerson->Attribute("hire");
                tempRoleUpware = FirstPerson->Attribute("upware");
                tempRoleDownware = FirstPerson->Attribute("downware");
                tempRoleShoe = FirstPerson->Attribute("shoe");

                if(tempRoleSex == "1" )
                    tempForEntity = "Man";
                else
                    tempForEntity = "Woman";
                //left
                tempEntity = mSceneMgr->createEntity("righthead",  tempForEntity + ".Hair." + tempRoleHire + ".mesh");
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[0] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[0]->setLoop(true);
                mAnimState[0]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("rightwear",  tempForEntity + ".Up." + tempRoleUpware + ".mesh");
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[1] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[1]->setLoop(true);
                mAnimState[1]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("rightpant", tempForEntity + ".Down." + tempRoleDownware + ".mesh");
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[2] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[2]->setLoop(true);
                mAnimState[2]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("rightshoeR",  tempForEntity + ".Shoes." + "Leather" + ".R.mesh");
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[3] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[3]->setLoop(true);
                mAnimState[3]->setEnabled(true);

                tempEntity = mSceneMgr->createEntity("rightshoeL",  tempForEntity + ".Shoes." + "Leather" + ".L.mesh");
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
                tempSceneNode->attachObject(tempEntity);

                mAnimState[4] = tempEntity->getAnimationState("test");
                // “Enable”（起始）该动作
                mAnimState[4]->setLoop(true);
                mAnimState[4]->setEnabled(true);

                //licorice--显示人物名字
                Vector3 temp = leftPeopleSceneNode->getPosition();
                Vector3 name ;
                name.x = temp.x + 3.1;
                name.y = temp.y + 6.0;
                name.z = temp.z;

                Ogre::MovableText *roleRight = new Ogre::MovableText("RoleRight", tempRoleName, "SdkTrays/Caption", 0.3f);
                roleRight->showOnTop(true);
                roleRight->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE);
                //Vector3(0.5,6.1,0)
                tempSceneNode = rightPeopleSceneNode->createChildSceneNode(name);
                tempSceneNode->attachObject(roleRight);
            }
        }
    }

    //delete mTextForReady

    mTextForReady = new Ogre::MovableText("readyText", "Watting for Ready!", "SdkTrays/Caption", 2, Ogre::ColourValue(0.8, 0.8, 0.8));
    mTextForReady->showOnTop(true);
    mTextForReady->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE);
    this->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 6, 0))->attachObject(mTextForReady);








    /*
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

        Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
               plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

        Ogre::Entity *entGround = mSceneMgr->createEntity("GroundEntity", "ground");
        mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

        entGround->setMaterialName("Examples/Rockwall");
        entGround->setCastShadows(false);*/


    // Create a light
    Ogre::Light *l = mSceneMgr->createLight("MainLight");
    l->setPosition(20, 80, 50);

    /*ParticleUniverse::ParticleSystemManager* pManager = ParticleUniverse::ParticleSystemManager::getSingletonPtr();
    ParticleUniverse::ParticleSystem* pSys = pManager->createParticleSystem("mySys","spiralStars",mSceneMgr);
    mSceneMgr->getRootSceneNode()->attachObject(pSys);
    pSys->setDebugDisplayEnabled(true);

    pSys->start();*/

}

