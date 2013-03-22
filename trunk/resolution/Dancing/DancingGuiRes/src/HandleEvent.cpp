#include "BasicApplication.h"
#include "ClientConnect.h"
using namespace OgreBites;

/*******************************************************************
* ˵    ������BasicApplication�ĸ��ּ����ص�����ʵ���ڴ��ļ�
* ��    �ߣ� grius
* ��    �ڣ�2013��3��22��
*******************************************************************/
/*-----------------------------------------------------------------------------
| Extends frameRenderingQueued to update tray manager and carousel.
-----------------------------------------------------------------------------*/
bool BasicApplication::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    // don't do all these calculations when sample's running or when in configuration screen or when no samples loaded

    mKeyboard->capture();
    mMouse->capture();
    ConnectManager::GetInstance()->Receive();

    mTrayMgr->frameRenderingQueued(evt);

    return true;
}


/*-----------------------------------------------------------------------------
| Handles keypresses.
-----------------------------------------------------------------------------*/
bool BasicApplication::keyPressed(const OIS::KeyEvent &evt)
{
    DancingGuiSys::GetInstance()->keyPressed(evt);
    if (mTrayMgr->isDialogVisible()) return true;  // ignore keypresses when dialog is showing
    return true;
}
/*-----------------------------------------------------------------------------
| Extends mousePressed to inject mouse press into tray manager, and to check
| for thumbnail clicks, just because we can.
-----------------------------------------------------------------------------*/

bool BasicApplication::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)

{


    OIS::MouseState state = evt.state;
    OIS::MouseEvent orientedEvt((OIS::Object *)evt.device, state);

    if (mTrayMgr->injectMouseDown(orientedEvt, id)) return true;


    return true;
}


bool BasicApplication::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{


    OIS::MouseState state = evt.state;
    OIS::MouseEvent orientedEvt((OIS::Object *)evt.device, state);

    if (mTrayMgr->injectMouseUp(orientedEvt, id)) return true;

    return true;
}



bool BasicApplication::mouseMoved(const OIS::MouseEvent &evt)

{


    OIS::MouseState state = evt.state;

    OIS::MouseEvent orientedEvt((OIS::Object *)evt.device, state);


    if (mTrayMgr->injectMouseMove(orientedEvt)) return true;



    return true;
}


/*-----------------------------------------------------------------------------
| Extends windowResized to best fit menus on screen. We basically move the
| menu tray to the left for higher resolutions and move it to the center
| for lower resolutions.
-----------------------------------------------------------------------------*/
void BasicApplication::windowResized(Ogre::RenderWindow *rw)
{

    DancingGuiSys::GetInstance()->setVerticalCenter(rw->getHeight() / 2);
    DancingGuiSys::GetInstance()->setHorizontalCenter(rw->getWidth() / 2);
    if (!mTrayMgr) return;

    Ogre::OverlayContainer *center = mTrayMgr->getTrayContainer(TL_CENTER);
    Ogre::OverlayContainer *left = mTrayMgr->getTrayContainer(TL_LEFT);

    if (center->isVisible() && rw->getWidth() < 1280 - center->getWidth())
    {
        while (center->isVisible())
        {
            mTrayMgr->moveWidgetToTray(mTrayMgr->getWidget(TL_CENTER, 0), TL_LEFT);
        }
    }
    else if (left->isVisible() && rw->getWidth() >= 1280 - left->getWidth())
    {
        while (left->isVisible())
        {
            mTrayMgr->moveWidgetToTray(mTrayMgr->getWidget(TL_LEFT, 0), TL_CENTER);
        }
    }

    //BasicApplication::windowResized(rw);
    // manually call sample callback to ensure correct order
    //  if (mCurrentSample && !mSamplePaused) mCurrentSample->windowResized(rw);

#if OGRE_PLATFORM != OGRE_PLATFORM_IPHONE
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = rw->getWidth();
    ms.height = rw->getHeight();
#endif
    //end
}
bool BasicApplication::frameStarted(const Ogre::FrameEvent &evt)
{
    //captureInputDevices();      // capture input

    //endcaptureInputDevices

    // manually call sample callback to ensure correct order(mCurrentSample && !mSamplePaused) ? mCurrentSample->frameStarted(evt) :
    return  true;
}

/*-----------------------------------------------------------------------------
| Processes frame ended events.
-----------------------------------------------------------------------------*/
bool BasicApplication::frameEnded(const Ogre::FrameEvent &evt)
{
    // manually call sample callback to ensure correct order
    // if (mCurrentSample && !mSamplePaused && !mCurrentSample->frameEnded(evt)) return false;
    // quit if window was closed
    if (mWindow->isClosed()) return false;
    // go into idle mode if current sample has ended
    // if (mCurrentSample && mCurrentSample->isDone()) runSample(0);

    return true;
}


// window event callbacks which manually call their respective sample callbacks to ensure correct order

void BasicApplication::windowMoved(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) mCurrentSample->windowMoved(rw);
}

bool BasicApplication::windowClosing(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) return mCurrentSample->windowClosing(rw);
    return true;
}

void BasicApplication::windowClosed(Ogre::RenderWindow *rw)
{
    //  if (mCurrentSample && !mSamplePaused) mCurrentSample->windowClosed(rw);
}

void BasicApplication::windowFocusChange(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) mCurrentSample->windowFocusChange(rw);
}


bool BasicApplication::keyReleased(const OIS::KeyEvent &evt)
{
    DancingGuiSys::GetInstance()->keyReleased(evt);
    //  if (mCurrentSample && !mSamplePaused) return mCurrentSample->keyReleased(evt);
    return true;
}