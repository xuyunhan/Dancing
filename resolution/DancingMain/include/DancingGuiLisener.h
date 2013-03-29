#if !defined(_DancingGuiLisener_H)
#define _DancingGuiLisener_H
#include <SdkTrays.h>
#include <string>
using namespace OgreBites;
using namespace std;

/*******************************************************************
* 说    明：OgreTray的事件响应类
                       原本该类的功能集成在DancingGUISYS下，无奈那边函数太多，不好找，就抽出一部分放这
* 作    者： grius
* 日    期：2013年3月21日
*******************************************************************/
class DancingGuiLisener: public SdkTrayListener
{
public:
    DancingGuiLisener(void);
    ~DancingGuiLisener(void);

    /*******************************************************************
    * 说    明：继承SdkTrayListener接口需实现的函数
    * 作    者： grius
    * 日    期：2013年3月21日
    *******************************************************************/
    void buttonHit(Button *button) ;
    void itemSelected(SelectMenu *menu) ;
    void labelHit(Label *label) ;
    void sliderMoved(Slider *slider) ;
    void checkBoxToggled(CheckBox *box) ;
    void okDialogClosed(const Ogre::DisplayString &message) ;
    void yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit) ;


    ////清空以往已选房间的记录
    void clearInfo()
    {
        mWillHouse = "";//已选界面为空
        mWillHouseLabelName = "";
    }

    //setter
    void setTrayMgr(OgreBites::SdkTrayManager *paraTrayMgr)
    {
        mTrayMgr = paraTrayMgr;
    }

private:
    //从DancingGuiSys传过来的变量
    OgreBites::SdkTrayManager *mTrayMgr;

    //用于局域网模式，在已有的房间类表中选择房间的信息
    string mWillHouseLabelName;//已选择房间的label的名字
    string mWillHouse;//已选择的房间的名字
};
#endif
