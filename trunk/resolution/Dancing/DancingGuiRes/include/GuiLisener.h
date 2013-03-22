#if !defined(_GuiLisener_H)
#define _GuiLisener_H
#include <SdkTrays.h>
#include <string>
using namespace OgreBites;
using namespace std;

/*******************************************************************
* ˵    ����OgreTray���¼���Ӧ��
                       ԭ������Ĺ��ܼ�����DancingGUISYS�£������Ǳߺ���̫�࣬�����ң��ͳ��һ���ַ���
* ��    �ߣ� grius
* ��    �ڣ�2013��3��21��
*******************************************************************/
class GuiLisener: public SdkTrayListener
{
public:
    GuiLisener(void);
    ~GuiLisener(void);

    /*******************************************************************
    * ˵    �����̳�SdkTrayListener�ӿ���ʵ�ֵĺ���
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��21��
    *******************************************************************/
    void buttonHit(Button *button) ;
    void itemSelected(SelectMenu *menu) ;
    void labelHit(Label *label) ;
    void sliderMoved(Slider *slider) ;
    void checkBoxToggled(CheckBox *box) ;
    void okDialogClosed(const Ogre::DisplayString &message) ;
    void yesNoDialogClosed(const Ogre::DisplayString &question, bool yesHit) ;


    ////���������ѡ����ļ�¼
    void clearInfo()
    {
        mWillHouse = "";//��ѡ����Ϊ��
        mWillHouseLabelName = "";
    }

    //setter
    void setTrayMgr(OgreBites::SdkTrayManager *paraTrayMgr)
    {
        mTrayMgr = paraTrayMgr;
    }

private:
    //��DancingGuiSys�������ı���
    OgreBites::SdkTrayManager *mTrayMgr;

    //���ھ�����ģʽ�������еķ��������ѡ�񷿼����Ϣ
    string mWillHouseLabelName;//��ѡ�񷿼��label������
    string mWillHouse;//��ѡ��ķ��������
};
#endif
