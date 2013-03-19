/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/

 Copyright (c) 2000-2011 Torus Knot Software Ltd

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#ifndef __SampleContext_H__
#define __SampleContext_H__

#include "Ogre.h"
#include "OgrePlugin.h"
#include "Sample.h"
#include "FileSystemLayerImpl.h"

#include "SamplePlugin.h"
#include "SdkTrays.h"

#include "OgreTimer.h"
#include "DancingGuiSys.h"


#include "OIS.h"
using namespace Ogre;

/*=============================================================================
| Base class responsible for setting up a common context for samples.
| May be subclassed for specific sample types (not specific samples).
| Allows one sample to run at a time, while maintaining a sample queue.
=============================================================================*/
class SampleContext :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public OIS::KeyListener,
    public OIS::MouseListener,
    public SdkTrayListener
{
public:
    void shutdown();//只在go中有
    void setupWidgets();//只在go中有

    //void createInputDevices();
    //void captureInputDevices();
    //Ogre::RenderWindow *getRenderWindow();

    void go(Sample *initialSample = 0);
    /////////////////////////////



    //over mTrayMgr = new SdkTrayManager("BrowserControls", mWindow, mMouse, this);
    void labelHit(Label *label) ;
    void checkBoxToggled(CheckBox *box) ;
    void okDialogClosed(const Ogre::DisplayString &message);
    void sliderMoved(Slider *slider);
    void itemSelected(SelectMenu *menu);
    void buttonHit(Button *b);
    void yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit);
    //over
    ~SampleContext();
    SampleContext();
    //over mMouse->setEventCallback(this);
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseMoved(const OIS::MouseEvent &evt);
    //over mKeyboard->setEventCallback(this);
    bool keyPressed(const OIS::KeyEvent &evt);
    bool keyReleased(const OIS::KeyEvent &evt);
    //over Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
    void windowFocusChange(Ogre::RenderWindow *rw);
    void windowClosed(Ogre::RenderWindow *rw);
    bool windowClosing(Ogre::RenderWindow *rw);
    void windowMoved(Ogre::RenderWindow *rw);
    void windowResized(Ogre::RenderWindow *rw);
    //over mRoot->addFrameListener(this);
    bool frameEnded(const Ogre::FrameEvent &evt);
    bool frameStarted(const Ogre::FrameEvent &evt);
    bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    void createScene();
protected:

    SdkTrayManager *mTrayMgr;                      // SDK tray interface

    FileSystemLayer *mFSLayer; 		// File system abstraction layer
    Ogre::Root *mRoot;              // OGRE root
    Ogre::RenderWindow *mWindow;    // render window
    OIS::InputManager *mInputMgr;   // OIS input manager

    OIS::Keyboard *mKeyboard;       // keyboard device
    OIS::Mouse *mMouse;             // mouse device

    Ogre::String mNextRenderer;     // name of renderer used for next run

    Ogre::Camera *mCamera;
    Ogre::SceneManager *mSceneMgr;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    //
    DancingGuiSys *mDancingGuiSys;
};


#endif
