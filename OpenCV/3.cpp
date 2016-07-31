#include "highgui.h"
#include "cv.h"

void process(IplImage *, IplImage *);
void output(IplImage *, IplImage *);
void release(IplImage *, IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg"), 
		*out = cvCreateImage(cvSize(img->width / 2, img->height / 2), img->depth, img->nChannels);
	process(img, out);
	output(img, out);
	release(img,out);
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
	cvNamedWindow("ex3-1");
	cvNamedWindow("ex3-2");

	cvShowImage("ex3-1", origin);
	cvShowImage("ex3-2", target);

	cvWaitKey(0);
}

void process(IplImage *origin, IplImage *target)
{
	cvPyrDown(origin, target);
}