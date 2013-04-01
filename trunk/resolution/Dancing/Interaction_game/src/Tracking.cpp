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
        //cvResize(outFromVideo, forVideoScale, CV_INTER_LINEAR);//fux addĿǰ����һ���ģ�����Ҫ׼����

        /*******************************************************************
        * ˵    �����任cam�Ĵ�С��ʹ����video���ƥ��
        * ��    �ߣ� grius
        * ��    �ڣ�2013��3��25��
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
        * ˵    �������ǵ�����ͷ���ܲ���һ������Ȳ����꣬������Ҫ��������ü�video���°벿��
        * ��    �ߣ� grius
        * ��    �ڣ�2013��3��25��
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