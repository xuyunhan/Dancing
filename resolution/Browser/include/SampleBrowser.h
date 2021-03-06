#ifndef __SampleBrowser_H__
#define __SampleBrowser_H__

#include "SampleContext.h"

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
    //endshutdownInput

    // unloadSamples();

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
    mDancingGuiSys = 0;
}

SampleContext::~SampleContext()
{
    OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
}

/*-----------------------------------------------------------------------------
| This function encapsulates the entire lifetime of the context.
-----------------------------------------------------------------------------*/
void SampleContext::go(Sample *initialSample)
{
    Ogre::String pluginsPath = Ogre::StringUtil::BLANK;

    pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");
    mRoot = OGRE_NEW Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"),
                                mFSLayer->getWritablePath("ogre.log"));
    //endcreateroot

    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        // mWindow = mRoot->initialise(true, "DancingMain Render Window");
        mWindow = mRoot->initialise(true, "��������");
        // Let's add a nice window icon
        //   HWND hwnd;
        // mWindow->getCustomAttribute("WINDOW", (void *)&hwnd);
        // LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
        // SetClassLong( hwnd, GCL_HICON, iconID );
        // return true;
    }

    //	return mRoot->showConfigDialog();
   // mRoot->restoreConfig();

    //setup();
    //createWindow();
   // mWindow = mRoot->initialise(true, "��������");
	
    //endcreateWindow


    /*******************************************************************
    *******************************************************************/
    //scenemgr//
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    //-------------------------------------------------------------------------------------
    // create camera
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 0, 80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);

    //        mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
    //-------------------------------------------------------------------------------------
    // create viewports
    // Create one viewport, entire window
    Ogre::Viewport *vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    // Alter the camera aspect ratio to match the viewport
	//licorice
	//mCamera->setAspectRatio(1.3333);
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    //-------------------------------------------------------------------------------------
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    //-------------------------------------------------------------------------------------
    // Create any resource listeners (for loading screens)
    //createResourceListener();
    //-------------------------------------------------------------------------------------
    // load resources
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    //-------------------------------------------------------------------------------------


    /*******************************************************************
    *******************************************************************/

    //setupInput();
    OIS::ParamList pl;
    size_t winHandle = 0;
    std::ostringstream winHandleStr;
    mWindow->getCustomAttribute("WINDOW", &winHandle);
    winHandleStr << winHandle;
    pl.insert(std::make_pair("WINDOW", winHandleStr.str()));
    mInputMgr = OIS::InputManager::createInputSystem(pl);

    //createInputDevices();      // create the specific input devices
    mKeyboard = static_cast<OIS::Keyboard *>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse *>(mInputMgr->createInputObject(OIS::OISMouse, true));
    mKeyboard->setEventCallback(this);
    mMouse->setEventCallback(this);
    //endcreateInputDevices

    windowResized(mWindow);    // do an initial adjustment of mouse area
    //endsetupInput

    // locateResources();
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
    mTrayMgr = new SdkTrayManager("BrowserControls", mWindow, mMouse, this);

    // mTrayMgr->showBackdrop("SdkTrays/Bands");
    //mTrayMgr->getTrayContainer(TL_NONE)->hide();
    //loadResources();
    mTrayMgr->showLoadingBar(1, 0);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Popular");
    mTrayMgr->hideLoadingBar();
    //loadResources


    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    // create template material for sample thumbnails
    Ogre::MaterialPtr thumbMat = Ogre::MaterialManager::getSingleton().create("SampleThumbnail", "Essential");
    thumbMat->getTechnique(0)->getPass(0)->createTextureUnitState();

    setupWidgets();

    mDancingGuiSys = new DancingGuiSys(mTrayMgr, mRoot,mWindow);
    mDancingGuiSys->setWidgetBaseState();
    //mDancingGuiSys->setWidgetGameSet();

    windowResized(mWindow);   // adjust menus for resolution
    createScene();

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
#endif
