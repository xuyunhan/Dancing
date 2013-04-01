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
        * 说    明：载入原图，并复制一张作为处理的备份
        * 作    者： grius
        * 日    期：2013年3月24日
        *******************************************************************/
	Capture = NULL;
	Capture = cvCaptureFromFile("test.avi");
	sourceImg = cvQueryFrame(Capture);

    //sourceImg = cvLoadImage("01.jpg", 0);//fux add 应该从视频中获取一帧
    targetImg =  cvCreateImage(cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1);
	forGeshiImg = cvCreateImage(cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1);
    //cvCopy(sourceImg, targetImg);
    outImg = cvCreateImage(cvSize(sourceImg->width, sourceImg->height),  IPL_DEPTH_8U, 1); //创建目标图像

    storage = cvCreateMemStorage(0);
    contours = 0;

    


}
          IplImage *fromVideo::getOutputFromVideo()
{
    /*******************************************************************
    * 说    明：寻找边缘，并找到最大的包围盒
    * 作    者： grius
    * 日    期：2013年3月24日
    *******************************************************************/
    //sourceImg = cvLoadImage("01.jpg", 0);//fux add应该从视频中获取一帧  主要是这块耗内存很大
	sourceImg = cvQueryFrame(Capture);
   // cvCopy(sourceImg, targetImg);
	cvCvtColor(sourceImg, targetImg, CV_BGR2GRAY);
	cvCvtColor(sourceImg, forGeshiImg, CV_BGR2GRAY);
	


    cvClearMemStorage( storage );///////这块耗内存很大 需清理
    cvFindContours(targetImg, storage, &contours, sizeof( CvContour ), CV_RETR_EXTERNAL    , CV_CHAIN_APPROX_NONE );

    //测试有几个轮廓
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

    //本是绘制矩形的函数，但此处并不需要绘制
    //cvRectangle( tarimg, cvPoint( maxRect.x, maxRect.y ), cvPoint( maxRect.x + maxRect.width, maxRect.y + maxRect.height ), cvScalar(255, 0, 0), 0 );

    cvZero(outImg);
    cvSetImageROI(forGeshiImg, maxRect); //设置源图像ROI
    maxRect.x = 0;
    maxRect.y = 0;
    cvSetImageROI(outImg, maxRect);


    //cvSetImageROI(sourceImg, maxRect); //设置源图像ROI
    // IplImage *outImg = cvCreateImage(cvSize(maxRect.width, maxRect.height), sourceImg->depth, sourceImg->nChannels); //创建目标图像
    cvCopy(forGeshiImg, outImg); //复制图像
    cvResetImageROI(forGeshiImg);//源图像用完后，清空ROI

    cvResetImageROI(outImg);

    printf(":%d!\n", i);

    return outImg;

}
