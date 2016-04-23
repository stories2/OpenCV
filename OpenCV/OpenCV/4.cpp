#include "highgui.h"
#include "cv.h"

#define lowThresh 10
#define highThresh 100
#define aperture 3

void process(IplImage *, IplImage *);
void output(IplImage *, IplImage *);
void release(IplImage *, IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg",IPL_DEPTH_8U), //캐니 엣지 검출기는 그레이 스케일 영상만을 다룬다, 따라서 입력받을때 단일 채널로 받아들인다
		*out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	process(img, out);
	output(img, out);
	release(img, out);
	return 0;
}

void release(IplImage *source, IplImage *result)
{
	cvReleaseImage(&source);
	cvReleaseImage(&result);

	cvDestroyAllWindows();
}

void output(IplImage *source, IplImage *result)
{
	cvNamedWindow("ex4-1");
	cvNamedWindow("ex4-2");

	cvShowImage("ex4-1", source);
	cvShowImage("ex4-2", result);

	cvWaitKey(0);
}

void process(IplImage *input, IplImage *result)
{
	cvCanny(input, result, lowThresh, highThresh, aperture);
}