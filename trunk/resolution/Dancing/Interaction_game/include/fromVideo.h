
#include <stdio.h>
#include <tchar.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <conio.h>
#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif
class fromVideo
{
public:
    fromVideo(void);
    ~fromVideo(void);

    void init();
    IplImage *getOutputFromVideo();
    CvRect getCvRect()
    {
        return maxRect;
    }
       private:
           IplImage *sourceImg ;
    IplImage *targetImg ;
    IplImage *forGeshiImg ;

    IplImage *outImg;

    CvMemStorage *storage ;
    CvSeq *contours ;

    CvRect maxRect;

    CvCapture *Capture ;



    int i;
};




