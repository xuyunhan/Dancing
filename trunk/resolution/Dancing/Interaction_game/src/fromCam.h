#include <stdio.h>
#include <tchar.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <conio.h>
#ifndef _WIN32_WINNT            // ָ��Ҫ������ƽ̨�� Windows Vista��
#define _WIN32_WINNT 0x0600     // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif
/*******************************************************************
    * ˵    ������������
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/
class fromCam
{
private:
    IplImage *Frame ;
    CvMat *FrameMat ;

    IplImage *FrImg ;
    CvMat *FrMat;

    IplImage *BkImg ;
    CvMat *BkMat ;

    IplImage *JyImg ;
    CvMat *JyMat ;

    IplImage *JyGrayImg ;

    IplImage *TImg ;
    CvMat *TMat ;

    IplImage *AbsImg ;
    CvMat *AbsMat ;


    //
    CvCapture *Capture ;


    IplImage *outImg;
public:
    fromCam();
    ~fromCam();
    void init();
    void getBg();

    IplImage *getOutputFromCam();


};
