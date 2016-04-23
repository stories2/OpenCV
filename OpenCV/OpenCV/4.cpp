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
	IplImage *img = cvLoadImage("target.jpg",IPL_DEPTH_8U), //ĳ�� ���� ������ �׷��� ������ ������ �ٷ��, ���� �Է¹����� ���� ä�η� �޾Ƶ��δ�
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