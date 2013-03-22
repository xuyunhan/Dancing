#include "Dancing.h"
#include "DotSceneLoader.h"


Dancing::Dancing(void)
{
}

Dancing::~Dancing(void)
{
}



bool Dancing::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    // don't do all these calculations when sample's running or when in configuration screen or when no samples loaded
    BasicApplication::frameRenderingQueued(evt);

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
{}
void Dancing::createSceneForCreateRole()
{
    mSceneMgr->destroyAllEntities();
    mSceneMgr->clearScene();//getRootSceneNode()->();
    Ogre::Entity *tempEntity;
    //tempEntity->;
    //mSceneMgr->
    //mRoot ->
    //tempEntity = mSceneMgr->getEntity("lefthead");

}
void Dancing::createSceneForCreateHouse()
{}
void Dancing::createSceneForGameSet()
{}

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

    /*******************************************************************
    * 说    明：设置场景
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    DotSceneLoader loader;
    loader.parseDotScene("aaa.scene", "General", mSceneMgr);

    Ogre::SceneNode *leftPeopleSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode *rightPeopleSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

    leftPeopleSceneNode->setPosition(-2.5, 0, 0);
    rightPeopleSceneNode->setPosition(2.5, 0, 0);

    Ogre::Entity *tempEntity;
    Ogre::SceneNode *tempSceneNode;
    {
        //left
        tempEntity = mSceneMgr->createEntity("lefthead", "First.Man.Hair.LongHair.mesh");
        tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("leftwear", "First.Man.Up.Overcoat.mesh");
        tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("leftpant", "First.Man.Down.Jeans.mesh");
        tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("leftshoe", "First.Man.Shoes.Leather.L.mesh");
        tempSceneNode = leftPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);
    }
    {
        //right
        tempEntity = mSceneMgr->createEntity("righthead", "First.Woman.Head.ShortHair.mesh");
        tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("rightwear", "First.Woman.Up.BrownSweater.mesh");
        tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("rightpant", "First.Woman.Down.WhitePants.mesh");
        tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);

        tempEntity = mSceneMgr->createEntity("rightshoe", "First.Woman.Shoes.WhiteShoes.R.mesh");
        tempSceneNode = rightPeopleSceneNode->createChildSceneNode();
        tempSceneNode->attachObject(tempEntity);
    }


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

