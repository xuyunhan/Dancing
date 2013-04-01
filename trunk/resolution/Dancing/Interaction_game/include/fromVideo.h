
#include <stdio.h>
#include <tchar.h>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <conio.h>
#ifndef _WIN32_WINNT            // ָ��Ҫ������ƽ̨�� Windows Vista��
#define _WIN32_WINNT 0x0600     // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
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




