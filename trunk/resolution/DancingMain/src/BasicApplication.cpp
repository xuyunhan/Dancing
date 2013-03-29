#include "BasicApplication.h"

using namespace OgreBites;


void BasicApplication::shutdown()
{
    if (mTrayMgr)
    {
        delete mTrayMgr;
        mTrayMgr = 0;
    }

    // remove window event listener before shutting down OIS
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

    //shutdownInput();
    if (mInputMgr)
    {
        mInputMgr->destroyInputObject(mKeyboard);

        mInputMgr->destroyInputObject(mMouse);

        OIS::InputManager::destroyInputSystem(mInputMgr);
        mInputMgr = 0;
    }
}

BasicApplication::BasicApplication()
{
    mFSLayer = OGRE_NEW_T(FileSystemLayerImpl, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
    mRoot = 0;
    mWindow = 0;
    mInputMgr = 0;
    mKeyboard = 0;
    mMouse = 0;
    mTrayMgr = 0;

	mTimer=NULL;
}

BasicApplication::~BasicApplication()
{
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
}

/*******************************************************************
* ˵    ����һ���Ƚ���Ҫ�ĺ�����ʵ��
* ��    �ߣ� grius
* ��    �ڣ�2013��3��22��
*******************************************************************/
void BasicApplication::go(Sample *initialSample)
{
    /*******************************************************************
    * ˵    ����mRoot������Ӧ�õ���Ҫ����
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    Ogre::String pluginsPath = Ogre::StringUtil::BLANK;

    pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");
    mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"),
                                mFSLayer->getWritablePath("ogre.log"));
    //end create mroot

    /*******************************************************************
    * ˵    �����������ʾ���ô��ڣ���������ע�ͣ����������ע�͵�
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
     if(mRoot->showConfigDialog())
    {
        mWindow = mRoot->initialise(true, "��������");
    }
   /*mRoot->restoreConfig();
    mWindow = mRoot->initialise(true, "��������");*/
    //end create mWindow


    /*******************************************************************
    * ˵    ����mSceneMgr mCamera Viewport
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "dancingscenemanager");

    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0, 0, 80));
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);

    Ogre::Viewport *vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    //end



    //some loader
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);//��ɶ�ģ�
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    //some setter
    OIS::ParamList pl;
    size_t winHandle = 0;
    std::ostringstream winHandleStr;
    mWindow->getCustomAttribute("WINDOW", &winHandle);
    winHandleStr << winHandle;
    pl.insert(std::make_pair("WINDOW", winHandleStr.str()));

    /*******************************************************************
    * ˵    ����OIS ����ϵͳ
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    mInputMgr = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard *>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse *>(mInputMgr->createInputObject(OIS::OISMouse, true));
    mKeyboard->setEventCallback(this);
    mMouse->setEventCallback(this);
    //end create InputDevices




    windowResized(mWindow);    // do an initial adjustment of mouse area


    /*******************************************************************
    * ˵    ����locateResources
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    Ogre::ConfigFile cf;
    cf.load(mFSLayer->getConfigFilePath("resources.cfg"));// load resource paths from config file

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;

    while (seci.hasMoreElements())// go through all specified resource groups
    {
        sec = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;

        // go through all resource paths
        for (i = settings->begin(); i != settings->end(); i++)
        {
            type = i->first;
            arch = i->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
        }
    }
    //endlocateResources
    //endsetup

    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");



    //createDummyScene();
    mTrayMgr = new SdkTrayManager("BrowserControls", mWindow, mMouse, DancingGuiSys::GetInstance()->getDancingGuiLisener());


    mTrayMgr->showLoadingBar(1, 0);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("start");
	
    mTrayMgr->hideLoadingBar();
    //loadResources


    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    // create template material for sample thumbnails
    //Ogre::MaterialPtr thumbMat = Ogre::MaterialManager::getSingleton().create("SampleThumbnail", "Essential");
    //thumbMat->getTechnique(0)->getPass(0)->createTextureUnitState();



    /*******************************************************************
    * ˵    ������DancingGuiSys�ݲ�
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    DancingGuiSys::GetInstance()->setTrayMgr(mTrayMgr);
    DancingGuiSys::GetInstance()->setRoot(mRoot);
    DancingGuiSys::GetInstance()->setWidgetBaseState();

    windowResized(mWindow);   // adjust menus for resolution


	createSceneForWelcome();
    /*******************************************************************
    * ˵    ������ѭ����ʼ
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��22��
    *******************************************************************/
    mRoot->startRendering();    // start the render loop

    mRoot->saveConfig();
    shutdown();
    if (mRoot)
        OGRE_DELETE mRoot;
}



