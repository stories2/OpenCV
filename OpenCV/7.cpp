#include "highgui.h"
#include "cv.h"

void process(IplImage * , IplImage *);
void output(IplImage *, IplImage *);
void release(IplImage *, IplImage *);

int main()
{
	IplImage *src = cvLoadImage("target.jpg"), *result = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);
	process(src,result);
	output(src, result);
	release(src, result);

	return 0;
}

void release(IplImage *target, IplImage *result)
{
	cvReleaseImage(&target);
	cvReleaseImage(&result);

	cvDestroyAllWindows();
}

void output(IplImage *target, IplImage *result)
{
	cvNamedWindow("original");
	cvNamedWindow("smooth");

	cvShowImage("original", target);
	cvShowImage("smooth", result);

	cvWaitKey(0);
}

void process(IplImage *target, IplImage *result)
{
	cvSmooth(target, result, CV_GAUSSIAN, 3, 0, 0, 0);
}