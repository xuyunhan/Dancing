#include "fromCam.h"


int main()
{
    cvNamedWindow("fromCam", 1);
    //fromVideo
    cvMoveWindow("fromCam", 0, 0);

    IplImage *outFromCam ;


    fromCam fc;
    fc.init();
    fc.getBg();
    while(1)
    {
        outFromCam = fc.getOutputFromCam();

        cvShowImage("fromCam", outFromCam);
        if (cvWaitKey(2) >= 0)
            break;
    }

    return 0;
}

