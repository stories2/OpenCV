#include "highgui.h"

void process();
void input(IplImage *);
void output(IplImage *);
void release(IplImage *);

int main()
{
	process();
	return 0;
}


void process()
{
	IplImage *img = cvLoadImage("target.jpg");
	input(img);
	output(img);
	release(img);
}

void release(IplImage *target)
{
	cvReleaseImage(&target);
	cvDestroyAllWindows();
}

void output(IplImage *target)
{
	cvNamedWindow("ex1", CV_WINDOW_AUTOSIZE);
	cvShowImage("ex1", target);

	cvWaitKey(0);
}

void input(IplImage *target)
{
	//target = cvLoadImage("target.jpg");
}