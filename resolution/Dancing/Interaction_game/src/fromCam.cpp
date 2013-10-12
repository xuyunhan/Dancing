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

    sourceImg  = NULL;//= //cvLoadImage("01.jpg", 0);
    targetImg  = NULL ;

    storage = cvCreateMemStorage(0);
    contours = 0;


    maxRect.height = 1;
    maxRect.width = 1;
    maxRect.x = 0;
    maxRect.y = 0;


}
fromCam::~fromCam()
{

}
void fromCam::init()
{

    /*******************************************************************
    * ˵    �����õ���Ӱ�Ķ�ֵͼ TMat
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/
    {
        Frame = cvQueryFrame(Capture);

        JyImg = cvLoadImage("01.jpg"); //����ͼƬ
        if(!JyImg)
            printf("��ȡͼƬ����");
        JyGrayImg = cvCreateImage(cvSize(JyImg->width, JyImg->height), IPL_DEPTH_8U, 1);
        JyMat = cvCreateMat(JyImg->height, JyImg->width, CV_32FC1);

        TImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);

        TMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        cvCvtColor(JyImg, JyGrayImg, CV_BGR2GRAY);
        cvResize(JyGrayImg, TImg, CV_INTER_LINEAR);
        cvConvert(TImg, TMat);
        cvThreshold(TMat, TImg, 60, 255.0, CV_THRESH_BINARY); //��ֵ��ǰ��ͼ
        cvConvert(TImg, TMat);
    }
    /*******************************************************************
    * ˵    ��������IMG��MAT
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/
    {
        BkImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
        FrImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
        AbsImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);

        BkMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        FrMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        FrameMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);
        AbsMat = cvCreateMat(Frame->height, Frame->width, CV_32FC1);

        sourceImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
        targetImg =  cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);

		outImg = cvCreateImage(cvSize(Frame->width, Frame->height), IPL_DEPTH_8U, 1);
    }

}
void fromCam::getBg()
{


    /*******************************************************************
    * ˵    �����õ�BkMat��BkImg
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
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

    cvAbsDiff(FrameMat, BkMat, FrMat); //��ǰ֡�뱳��ͼ���
    /*******************************************************************
    * ˵    ����AbsDiffS����������Ԫ��������֮���ľ���ֵ �����ټ�һ����ֵ ������pow�����ټ�

    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/
    /*******************************************************************
    * ˵    ����ģ��PS������������Աȣ�����ɫ��
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/

    /*******************************************************************
    * ˵    ����ɫ�ݲ�Ӧ����˴������й�
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��23��
    *******************************************************************/
    cvThreshold(FrMat, FrImg, 60, 255.0, CV_THRESH_BINARY); //��ֵ��ǰ��ͼ
    cvConvert(FrImg, FrMat);

    cvAbsDiff(FrMat, TMat, AbsMat);

    cvErode(FrImg, FrImg, 0, 1);   //��̬ѧ�˲���ȥ������
    cvDilate(FrImg, FrImg, 0, 1);
    //cvRunningAvg(FrameMat, BkMat, 0.03, 0);


    cvConvert(BkMat, BkImg); //������ת��Ϊͼ���ʽ
    cvConvert(AbsMat, AbsImg);

    BkImg->origin = 0; //У��ͼ��
    FrImg->origin = 0;




    cvCopy(FrImg, sourceImg);
    cvCopy(sourceImg, targetImg);

    /*******************************************************************
    * ˵    ����Ѱ�ұ�Ե�����ҵ����İ�Χ��
    * ��    �ߣ� grius
    * ��    �ڣ�2013��3��24��
    *******************************************************************/


	cvClearMemStorage( storage );///////�����ڴ�ܴ� ������
    cvFindContours(targetImg, storage, &contours, sizeof( CvContour ), CV_RETR_EXTERNAL    , CV_CHAIN_APPROX_NONE );

   


	maxRect.height = 1;
	maxRect.width = 1;
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
    cvSetImageROI(sourceImg, maxRect); //����Դͼ��ROI
	maxRect.x = 0;
	maxRect.y = 0;
	cvSetImageROI(outImg,maxRect);


	
    //outImg = cvCreateImage(cvSize(maxRect.width, maxRect.height), sourceImg->depth, sourceImg->nChannels); //����Ŀ��ͼ��

	
	//outImg->
    cvCopy(sourceImg, outImg); //����ͼ��
    cvResetImageROI(sourceImg);//Դͼ����������ROI
	cvResetImageROI(outImg);

    printf(":%d!\n", i);
    //////////////////////////////
	



    return outImg;
}





