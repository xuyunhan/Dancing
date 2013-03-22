#include "OgrePlatform.h"

#include "SampleContext.h"
#include "ClientConnect.h"
#include "DancingGuiSys.h"

using namespace OgreBites;


void SampleContext::shutdown()
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

SampleContext::SampleContext()
{
    mFSLayer = OGRE_NEW_T(FileSystemLayerImpl, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
    mRoot = 0;
    mWindow = 0;
    mInputMgr = 0;
    mKeyboard = 0;
    mMouse = 0;
    mTrayMgr = 0;
}

SampleContext::~SampleContext()
{
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
}

/*******************************************************************
* 说    明：一个比较重要的函数的实现
* 作    者： grius
* 日    期：2013年3月22日
*******************************************************************/
void SampleContext::go(Sample *initialSample)
{
    /*******************************************************************
    * 说    明：mRoot是整个应用的主要对象
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    Ogre::String pluginsPath = Ogre::StringUtil::BLANK;

    pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");
    mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"),
                                mFSLayer->getWritablePath("ogre.log"));
    //end create mroot

    /*******************************************************************
    * 说    明：如果想显示配置窗口，则打开上面的注释，并把下面的注释掉
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    /*if(mRoot->showConfigDialog())
    {
        mWindow = mRoot->initialise(true, "不如跳舞");
    }*/
    mRoot->restoreConfig();
    mWindow = mRoot->initialise(true, "不如跳舞");
    //end create mWindow


    /*******************************************************************
    * 说    明：mSceneMgr mCamera Viewport
    * 作    者： grius
    * 日    期：2013年3月22日
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
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);//干啥的？
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    //some setter
    OIS::ParamList pl;
    size_t winHandle = 0;
    std::ostringstream winHandleStr;
    mWindow->getCustomAttribute("WINDOW", &winHandle);
    winHandleStr << winHandle;
    pl.insert(std::make_pair("WINDOW", winHandleStr.str()));

    /*******************************************************************
    * 说    明：OIS 输入系统
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    mInputMgr = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard *>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse *>(mInputMgr->createInputObject(OIS::OISMouse, true));
    mKeyboard->setEventCallback(this);
    mMouse->setEventCallback(this);
    //end create InputDevices




    windowResized(mWindow);    // do an initial adjustment of mouse area


    /*******************************************************************
    * 说    明：locateResources
    * 作    者： grius
    * 日    期：2013年3月22日
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
    mTrayMgr = new SdkTrayManager("BrowserControls", mWindow, mMouse, DancingGuiSys::GetInstance()->getGuiLisener());


    mTrayMgr->showLoadingBar(1, 0);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
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
    * 说    明：给DancingGuiSys递参
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    DancingGuiSys::GetInstance()->setTrayMgr(mTrayMgr);
    DancingGuiSys::GetInstance()->setRoot(mRoot);
    DancingGuiSys::GetInstance()->setWidgetBaseState();

    windowResized(mWindow);   // adjust menus for resolution




    /*******************************************************************
    * 说    明：创建场景
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    createScene();

    /*******************************************************************
    * 说    明：主循环开始
    * 作    者： grius
    * 日    期：2013年3月22日
    *******************************************************************/
    mRoot->startRendering();    // start the render loop

    mRoot->saveConfig();
    shutdown();
    if (mRoot)
        OGRE_DELETE mRoot;
}
void SampleContext::createScene()
{
    /*******************************************************************
    *******************************************************************/


    // Create the scene
    Ogre::Entity *ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

    Ogre::SceneNode *headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light *l = mSceneMgr->createLight("MainLight");
    l->setPosition(20, 80, 50);
    //-------------------------------------------------------------------------------------


    /*******************************************************************
    *******************************************************************/

}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include "SampleBrowser_OSX.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
#include "SampleBrowser_iOS.h"
#endif


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
#elif OGRE_PLATFORM == OGRE_PLATFORM_SYMBIAN
int mainWithTrap();
int main()
{
    int res = 0;
    __UHEAP_MARK;

    // Create the control environment.
    CCoeEnv *environment = new (ELeave) CCoeEnv();

    TRAPD( err, environment->ConstructL( ETrue, 0 ) );

    if( err != KErrNone )
    {
        printf( "Unable to create a CCoeEnv!\n" );
        getchar();
    }

    TRAP( err, res = mainWithTrap());

    // Close the stdout & stdin, else printf / getchar causes a memory leak.
    fclose( stdout );
    fclose( stdin );

    // Cleanup
    CCoeEnv::Static()->DestroyEnvironment();
    delete CCoeEnv::Static();

    __UHEAP_MARKEND;

    return res;
}

int mainWithTrap()

#else

int main(int argc, char *argv[])
#endif
{
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, @"UIApplication", @"AppDelegate");
    [pool release];
    return retVal;
#elif (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    mAppDelegate = [[AppDelegate alloc] init];
[[NSApplication sharedApplication] setDelegate: mAppDelegate];
    int retVal = NSApplicationMain(argc, (const char **) argv);

    [pool release];

    return retVal;
#else

    try
    {
        SampleContext sb;


        ConnectManager::GetInstance();
        DancingGuiSys::GetInstance();
        ConnectManager::GetInstance()->ConfigClient();
        ConnectManager::GetInstance()->StartUpClient();

        /*while (1)
        {
            Sleep(30);
            //send倒可以不用
            ConnectManager::GetInstance()->Send();
            ConnectManager::GetInstance()->Receive();
        }*/
        sb.go();
    }
    catch (Ogre::Exception &e)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_SYMBIAN
        getchar();
#endif

    }

#endif
    return 0;
}

