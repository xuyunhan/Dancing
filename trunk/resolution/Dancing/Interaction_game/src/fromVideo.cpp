#include "fromVideo.h"

fromVideo::fromVideo(void)
{
}

fromVideo::~fromVideo(void)
{
}
void fromVideo::init()
{
    /*******************************************************************
        * ˵    ��������ԭͼ��������һ����Ϊ����ı���
        * ��    �ߣ� grius
        * ��    �ڣ�2013��3��24��
        *******************************************************************/
	Capture = NULL;
	Capture = cvCaptureFromFile("test.avi");
	sourceImg = cvQueryFrame(Capture);

    //sourceImg = cvLoadImage("01.jpg", 0);//fux add Ӧ�ô���Ƶ�л�ȡһ֡
    targetImg =  cvCreateImage(cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1);
	forGeshiImg = cvCreateImage(cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1);
    //cvCopy(sourceImg, targetImg);
    outImg = cvCreateImage(cvSize(sourceImg->width, sourceImg->height),  IPL_DEPTH_8U, 1); //����Ŀ��ͼ��

    storage = cvCreateMemStorage(0);
    contours = 0;

    


}
          IplImage *fromVideo::getOutputFromVideo()
{
    /*******************************************************************
    * ˵    ����Ѱ�ұ�Ե�����ҵ����İ�Χ��
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��24��
    *******************************************************************/
    //sourceImg = cvLoadImage("01.jpg", 0);//fux addӦ�ô���Ƶ�л�ȡһ֡  ��Ҫ�������ڴ�ܴ�
	sourceImg = cvQueryFrame(Capture);
   // cvCopy(sourceImg, targetImg);
	cvCvtColor(sourceImg, targetImg, CV_BGR2GRAY);
	cvCvtColor(sourceImg, forGeshiImg, CV_BGR2GRAY);
	


    cvClearMemStorage( storage );///////�����ڴ�ܴ� ������
    cvFindContours(targetImg, storage, &contours, sizeof( CvContour ), CV_RETR_EXTERNAL    , CV_CHAIN_APPROX_NONE );

    //�����м�������
    maxRect.height = 0;
    maxRect.width = 0;
    for( i = 0; contours != NULL; contours = contours -> h_next, i++ )
    {
        CvRect rect = cvBoundingRect( contours, 0 );
        if((rect.height * rect.width) > (maxRect.height * maxRect.width) )
        {
            maxRect = rect;
        }
    }

    //���ǻ��ƾ��εĺ��������˴�������Ҫ����
    //cvRectangle( tarimg, cvPoint( maxRect.x, maxRect.y ), cvPoint( maxRect.x + maxRect.width, maxRect.y + maxRect.height ), cvScalar(255, 0, 0), 0 );

    cvZero(outImg);
    cvSetImageROI(forGeshiImg, maxRect); //����Դͼ��ROI
    maxRect.x = 0;
    maxRect.y = 0;
    cvSetImageROI(outImg, maxRect);


    //cvSetImageROI(sourceImg, maxRect); //����Դͼ��ROI
    // IplImage *outImg = cvCreateImage(cvSize(maxRect.width, maxRect.height), sourceImg->depth, sourceImg->nChannels); //����Ŀ��ͼ��
    cvCopy(forGeshiImg, outImg); //����ͼ��
    cvResetImageROI(forGeshiImg);//Դͼ����������ROI

    cvResetImageROI(outImg);

    printf(":%d!\n", i);

    return outImg;

}
