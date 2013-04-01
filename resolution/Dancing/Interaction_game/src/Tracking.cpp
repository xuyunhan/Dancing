#include "fromCam.h"

#include "fromVideo.h"
int main()
{
    /**/cvNamedWindow("fromCam", 1);
    cvNamedWindow("fromVideo", 1);
    cvNamedWindow("scaleCam", 1);
    cvNamedWindow("scaleVideo", 1);


    cvMoveWindow("fromCam", 0, 0);
    cvMoveWindow("fromVideo", 600, 0);
    cvMoveWindow("scaleCam", 600, 400);
    cvMoveWindow("scaleVideo", 0, 400);

    IplImage *outFromCam ;
    IplImage *outFromVideo ;
    IplImage *themassforCam ;
    IplImage *themassforVideo ;

    IplImage *forVideoScale ;

    IplImage *AbsImg = NULL;
    CvMat *AbsMat = NULL;

    CvRect forCamRect;

    CvRect forVideoRect;






    fromCam fc;
    fc.init();
    fc.getBg();

    fromVideo fv;
    fv.init();

    outFromCam = fc.getOutputFromCam();

    forVideoScale = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    AbsImg = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    themassforCam = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    themassforVideo = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);

    while(1)
    {
        outFromCam = fc.getOutputFromCam();
        outFromVideo = fv.getOutputFromVideo();
        //cvResize(outFromVideo, forVideoScale, CV_INTER_LINEAR);//fux add目前是以一样的，但需要准备着

        /*******************************************************************
        * 说    明：变换cam的大小，使其与video宽度匹配
        * 作    者： grius
        * 日    期：2013年3月25日
        *******************************************************************/
         forVideoRect = fv.getCvRect();
        forCamRect = fc.getCvRect();

        CvRect temp;
        temp.x = 0;
        temp.y = 0;
        temp.width = forVideoRect.width;
        temp.height = forVideoRect.width * forCamRect.height / forCamRect.width;

        cvZero(themassforCam);
        cvSetImageROI(themassforCam, temp);
        cvSetImageROI(outFromCam, forCamRect);

        cvResize(outFromCam, themassforCam, CV_INTER_LINEAR);

        cvResetImageROI(themassforCam);
        cvResetImageROI(outFromCam);
        /*******************************************************************
        * 说    明：考虑到摄像头可能并不一定会把腿部照完，所以需要按照坐标裁减video的下半部分
        * 作    者： grius
        * 日    期：2013年3月25日
        *******************************************************************/
        temp.x = 0;
        temp.y = 0;
        temp.width = forVideoRect.width;
        temp.height = forCamRect.height;

        cvZero(themassforVideo);
        cvSetImageROI(themassforVideo, temp);
        cvSetImageROI(outFromVideo, temp);

        cvCopy(outFromVideo, themassforVideo);

        cvResetImageROI(themassforVideo);
        cvResetImageROI(outFromVideo);/**/




        cvShowImage("scaleVideo", themassforVideo);
        cvShowImage("scaleCam", themassforCam);
        cvShowImage("fromCam", outFromCam);
        cvShowImage("fromVideo", outFromVideo);
        if (cvWaitKey(2) >= 0)
            break;
    }

    return 0;
}