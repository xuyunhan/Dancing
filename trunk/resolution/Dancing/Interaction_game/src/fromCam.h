#include <stdio.h>
#include <tchar.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <conio.h>
#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif
/*******************************************************************
    * 说    明：声明变量
    * 作    者： grius
    * 日    期：2013年3月23日
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
