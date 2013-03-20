#include "SampleContext.h"
#include "ClientConnect.h"
using namespace OgreBites;
/*-----------------------------------------------------------------------------
| Extends frameRenderingQueued to update tray manager and carousel.
-----------------------------------------------------------------------------*/
bool SampleContext::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    // don't do all these calculations when sample's running or when in configuration screen or when no samples loaded

    ConnectManager::GetInstance()->Receive();

    mTrayMgr->frameRenderingQueued(evt);

    return true;
}
/*-----------------------------------------------------------------------------
| Handles confirmation dialog responses.
-----------------------------------------------------------------------------*/
void SampleContext::yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit)
{
    this->mDancingGuiSys->yesNoDialogClosed(question, yesHit);

}

/*-----------------------------------------------------------------------------
| Handles button widget events.
-----------------------------------------------------------------------------*/
void SampleContext::buttonHit(Button *b)
{
    this->mDancingGuiSys->buttonHit(b);

}

/*-----------------------------------------------------------------------------
| Handles menu item selection changes.
-----------------------------------------------------------------------------*/
void SampleContext::itemSelected(SelectMenu *menu)
{
    this->mDancingGuiSys->itemSelected(menu);

}

/*-----------------------------------------------------------------------------
| Handles sample slider changes.
-----------------------------------------------------------------------------*/
void SampleContext::sliderMoved(Slider *slider)
{
    this->mDancingGuiSys->sliderMoved(slider);

}
void SampleContext::labelHit(Label *label)
{
    this->mDancingGuiSys->labelHit(label);
}
void SampleContext::checkBoxToggled(CheckBox *box)
{
    this->mDancingGuiSys->checkBoxToggled(box);
}
void SampleContext::okDialogClosed(const Ogre::DisplayString &message)
{
    this->mDancingGuiSys->okDialogClosed(message);
}

/*-----------------------------------------------------------------------------
| Handles keypresses.
-----------------------------------------------------------------------------*/
bool SampleContext::keyPressed(const OIS::KeyEvent &evt)
{
    this->mDancingGuiSys->keyPressed(evt);
    if (mTrayMgr->isDialogVisible()) return true;  // ignore keypresses when dialog is showing
    return true;
}
/*-----------------------------------------------------------------------------
| Extends mousePressed to inject mouse press into tray manager, and to check
| for thumbnail clicks, just because we can.
-----------------------------------------------------------------------------*/

bool SampleContext::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)

{
    this->mDancingGuiSys->mousePressed(evt, id);

    OIS::MouseState state = evt.state;
    OIS::MouseEvent orientedEvt((OIS::Object *)evt.device, state);

    if (mTrayMgr->injectMouseDown(orientedEvt, id)) return true;


    return true;
}


bool SampleContext::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    this->mDancingGuiSys->mouseReleased(evt, id);

    OIS::MouseState state = evt.state;
    OIS::MouseEvent orientedEvt((OIS::Object *)evt.device, state);

    if (mTrayMgr->injectMouseUp(orientedEvt, id)) return true;

    return true;
}



bool SampleContext::mouseMoved(const OIS::MouseEvent &evt)

{
    this->mDancingGuiSys->mouseMoved(evt);

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
void SampleContext::windowResized(Ogre::RenderWindow *rw)
{
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

    //SampleContext::windowResized(rw);
    // manually call sample callback to ensure correct order
    //  if (mCurrentSample && !mSamplePaused) mCurrentSample->windowResized(rw);

#if OGRE_PLATFORM != OGRE_PLATFORM_IPHONE
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = rw->getWidth();
    ms.height = rw->getHeight();
#endif
    //end
}
bool SampleContext::frameStarted(const Ogre::FrameEvent &evt)
{
    //captureInputDevices();      // capture input
    mKeyboard->capture();
    mMouse->capture();
    //endcaptureInputDevices

    // manually call sample callback to ensure correct order(mCurrentSample && !mSamplePaused) ? mCurrentSample->frameStarted(evt) :
    return  true;
}

/*-----------------------------------------------------------------------------
| Processes frame ended events.
-----------------------------------------------------------------------------*/
bool SampleContext::frameEnded(const Ogre::FrameEvent &evt)
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

void SampleContext::windowMoved(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) mCurrentSample->windowMoved(rw);
}

bool SampleContext::windowClosing(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) return mCurrentSample->windowClosing(rw);
    return true;
}

void SampleContext::windowClosed(Ogre::RenderWindow *rw)
{
    //  if (mCurrentSample && !mSamplePaused) mCurrentSample->windowClosed(rw);
}

void SampleContext::windowFocusChange(Ogre::RenderWindow *rw)
{
    // if (mCurrentSample && !mSamplePaused) mCurrentSample->windowFocusChange(rw);
}


bool SampleContext::keyReleased(const OIS::KeyEvent &evt)
{
    this->mDancingGuiSys->keyReleased(evt);
    //  if (mCurrentSample && !mSamplePaused) return mCurrentSample->keyReleased(evt);
    return true;
}