#include "fromCam.h"

#include "fromVideo.h"

IplImage *outFromVideo;
fromVideo fv;

void onMouse(int Event,int x,int y,int flags,void* param)
{
	if(Event!=0)
	{
		if (Event==1)   	//������
		{
			outFromVideo =fv.getOutputFromVideo();
		}
		
	}
}
int main()
{
	//void onMouse(int Event,int x,int y,int flags,void* param);
	
    cvNamedWindow("fromCam", 1);
    cvNamedWindow("fromVideo", 1);
    cvNamedWindow("scaleCam", 1);
	cvNamedWindow("scaleVideo", 1);
	

    cvMoveWindow("fromCam", 0, 0);
    cvMoveWindow("fromVideo", 600, 0);
    cvMoveWindow("scaleCam", 600, 400);
	cvMoveWindow("scaleVideo", 0, 400);

    IplImage *outFromCam ;
   
    IplImage *themassforCam ;
    IplImage *themassforVideo ;

    IplImage *forVideoScale ;

    IplImage *AbsImg = NULL;
    CvMat *AbsMat = NULL;
	CvMat *themassforCamMat;
	CvMat *themassforVideoMat;
	CvMat *outputMat;

    CvRect forCamRect;

    CvRect forVideoRect;

	int count;
	float ppt;

	


    fromCam fc;
    fc.init();
    fc.getBg();

   // fromVideo fv;
    fv.init();

    outFromCam = fc.getOutputFromCam();
	outFromVideo =fv.getOutputFromVideo();

    forVideoScale = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    AbsImg = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    themassforCam = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);
    themassforVideo = cvCreateImage(cvSize(outFromCam->width, outFromCam->height), IPL_DEPTH_8U, 1);

	themassforCamMat=cvCreateMat(outFromCam->height,outFromCam->width,CV_32FC1);
	themassforVideoMat=cvCreateMat(outFromCam->height,outFromCam->width,CV_32FC1);
	outputMat=cvCreateMat(outFromCam->height,outFromCam->width,CV_32FC1);

  

    while(1)
    {
		outFromCam = fc.getOutputFromCam();
	
		cvSetMouseCallback("fromVideo",onMouse,0);
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
		temp.height = 1;
        temp.width = forVideoRect.width;
		if(forCamRect.width -0 <=1)
		{
        ;
		}
		else
		{
			temp.height = forVideoRect.width * forCamRect.height / forCamRect.width;
		}

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
        //temp.height = forCamRect.height;

		cvZero(themassforVideo);
        cvSetImageROI(themassforVideo, temp);
        cvSetImageROI(outFromVideo, temp);

		cvCopy(outFromVideo,themassforVideo);

		cvResetImageROI(themassforVideo);
		cvResetImageROI(outFromVideo);/**/
		/*******************************************************************
        * ˵    ���� �ڰײ��ְٷֱȼ���
       
        *******************************************************************/
		
		
		cvConvert(themassforVideo,themassforVideoMat);
		cvConvert(themassforCam,themassforCamMat);
		cvAbsDiff(themassforCamMat,themassforVideoMat,outputMat);
		count=cvCountNonZero(outputMat);
		ppt=((float)count/((outputMat->cols)*(outputMat->rows)))*100;
		printf("��ɫ����ٷֱȣ�%f%\n",ppt);


		cvShowImage("scaleVideo", themassforVideo);
        cvShowImage("scaleCam", themassforCam);
        cvShowImage("fromCam", outFromCam);
        cvShowImage("fromVideo", outFromVideo);
        if (cvWaitKey(2) >= 0)
            break;
  }

    return 0;
}
