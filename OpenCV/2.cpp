#include "highgui.h"
#include "cv.h"

void process(IplImage *, IplImage *);
void output(IplImage *, IplImage *);
void release(IplImage *, IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg"), *out = NULL;
	out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	process(img,out);
	output(img, out);
	release(img, out);
	return 0;
}

void release(IplImage *origin, IplImage *target)
{
	cvReleaseImage(&origin);
	cvReleaseImage(&target);

	cvDestroyAllWindows();
}

void output(IplImage *origin, IplImage *target)
{
	cvShowImage("ex2-1", origin);
	cvShowImage("ex2-2", target);

	cvWaitKey(0);
}

void process(IplImage *origin,IplImage *target)
{
	cvSmooth(origin, target, CV_GAUSSIAN, 3, 3);

}