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

/*******************************************************************
* 说    明：本应用程序主要的类，一些关键的信息皆由此维护，或由此委托别的类维护
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
class SampleContext :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public OIS::KeyListener,
    public OIS::MouseListener
{
public:
    //over
    ~SampleContext();
    SampleContext();

    void shutdown();//退出应用程序用



    //巨多关键的配置信息皆在此种，建议分开
    void go(Sample *initialSample = 0);

    //创建场景
    void createScene();


    /*******************************************************************
    * 说    明：此类派生自一些监听器，故需要实现一些接口
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
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
};


#endif
