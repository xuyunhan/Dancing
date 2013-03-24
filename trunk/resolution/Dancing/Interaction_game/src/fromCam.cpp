#include "fromCam.h"
fromCam::fromCam()
{
    Frame = NULL;
    FrameMat = NULL;

    FrImg = NULL;
    FrMat = NULL;

    BkImg = NULL;
    BkMat = NULL;

    JyImg = NULL;
    JyMat = NULL;

    JyGrayImg = NULL;

    TImg = 0;
    TMat = NULL;

    AbsImg = NULL;
    AbsMat = NULL;

    Capture = NULL;
    Capture = cvCaptureFromCAM(-1);

    //IplImage *outImg;
}
fromCam::~fromCam()
{

}
void fromCam::init()
{

    /*******************************************************************
    * 说    明：得到剪影的二值图 TMat
    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/
    {
        Frame = cvQueryFrame(Capture);

        JyImg = cvLoadImage("01.jpg"); //加载图片
        if(!JyImg)
            printf("读取图片错误！");
        JyGrayImg = cvCreateImage(cvSize(JyImg->width, JyImg->height), IPL_DEPTH_8U, 1);
        JyMat = cvCreateMat(JyImg->height, JyImg->width, CV_32FC1);

        TImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);

        TMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        cvCvtColor(JyImg, JyGrayImg, CV_BGR2GRAY);
        cvResize(JyGrayImg, TImg, CV_INTER_LINEAR);
        cvConvert(TImg, TMat);
        cvThreshold(TMat, TImg, 60, 255.0, CV_THRESH_BINARY); //二值化前景图
        cvConvert(TImg, TMat);
    }
    /*******************************************************************
    * 说    明：创建IMG、MAT
    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/
    {
        BkImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
        FrImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
        AbsImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);

        BkMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        FrMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        FrameMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        AbsMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
    }

}
void fromCam::getBg()
{


    /*******************************************************************
    * 说    明：得到BkMat、BkImg
    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/
    Frame = cvQueryFrame(Capture);
    cvCvtColor(Frame, BkImg, CV_BGR2GRAY);
    cvConvert(BkImg, BkMat);
}
IplImage *fromCam::getOutputFromCam()
{

    //cvReleaseImage(&Frame);
    Frame = cvQueryFrame(Capture);
    cvCvtColor(Frame, FrImg, CV_BGR2GRAY);



    cvConvert(FrImg, FrameMat);

    cvAbsDiff(FrameMat, BkMat, FrMat); //当前帧与背景图相减
    /*******************************************************************
    * 说    明：AbsDiffS：计算数组元素与数量之间差的绝对值 可以再减一个数值 可以下pow几次再减

    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/
    /*******************************************************************
    * 说    明：模仿PS的做法，增大对比，调节色阶
    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/

    /*******************************************************************
    * 说    明：色容差应当与此处参数有关
    * 作    者： grius
    * 日    期：2013年3月23日
    *******************************************************************/
    cvThreshold(FrMat, FrImg, 60, 255.0, CV_THRESH_BINARY); //二值化前景图
    cvConvert(FrImg, FrMat);

    cvAbsDiff(FrMat, TMat, AbsMat);

    cvErode(FrImg, FrImg, 0, 1);   //形态学滤波，去掉噪音
    cvDilate(FrImg, FrImg, 0, 1);
    //cvRunningAvg(FrameMat, BkMat, 0.03, 0);


    cvConvert(BkMat, BkImg); //将背景转化为图像格式
    cvConvert(AbsMat, AbsImg);

    BkImg->origin = 0; //校正图像
    FrImg->origin = 0;


    IplImage *sourceImg ;//= //cvLoadImage("01.jpg", 0);
    sourceImg = cvCreateImage(cvSize(AbsImg->width, AbsImg->height), IPL_DEPTH_8U, 1);
    cvCopy(FrImg, sourceImg);


    IplImage *targetImg ;
    targetImg =  cvCreateImage(cvSize(sourceImg->width, sourceImg->height), IPL_DEPTH_8U, 1);
    cvCopy(sourceImg, targetImg);

    /*******************************************************************
    * 说    明：寻找边缘，并找到最大的包围盒
    * 作    者： grius
    * 日    期：2013年3月24日
    *******************************************************************/
    CvMemStorage *storage = cvCreateMemStorage(0);
    CvSeq *contours = 0;

    cvFindContours(targetImg, storage, &contours, sizeof( CvContour ), CV_RETR_EXTERNAL    , CV_CHAIN_APPROX_NONE );

    int i;//测试有几个轮廓
    CvRect maxRect;
    maxRect.height = 1;
    maxRect.width = 1;
    maxRect.x = 0;
    maxRect.y = 0;
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



    cvSetImageROI(sourceImg, maxRect); //设置源图像ROI
    IplImage *outImg = cvCreateImage(cvSize(maxRect.width, maxRect.height), sourceImg->depth, sourceImg->nChannels); //创建目标图像
    cvCopy(sourceImg, outImg); //复制图像
    cvResetImageROI(sourceImg);//源图像用完后，清空ROI

    printf(":%d!\n", i);
    //////////////////////////////

    //显示图像

    //cvShowImage("back", BkImg);
    //cvShowImage("front", FrImg);
    //cvShowImage("abs", AbsImg);


    return outImg;
}






