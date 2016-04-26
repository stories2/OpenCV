#include "highgui.h"
#include "cv.h"

void process(IplImage *, IplImage *, IplConvKernel *);
void output(IplImage *);
void close(IplImage *, IplImage *, IplConvKernel *);

int main()
{
	IplConvKernel *kernel = cvCreateStructuringElementEx(8, 8, 1, 1, CV_SHAPE_RECT, NULL);//col,row 사각형을 의미,x,y 고정점의 좌표
	IplImage *img = cvLoadImage("target.jpg"),
		*result = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);

	process(img, result, kernel);
	output(result);
	close(img, result, kernel);
	return 0;
}

void close(IplImage *src, IplImage *target, IplConvKernel *kernel)
{
	cvReleaseImage(&src);
	cvReleaseImage(&target);
	cvReleaseStructuringElement(&kernel);

	cvDestroyAllWindows();
}

void output(IplImage *target)
{
	cvNamedWindow("ex9");
	cvShowImage("ex9", target);

	cvWaitKey(0);
}

void process(IplImage *src, IplImage *target, IplConvKernel *kernel)
{
	cvMorphologyEx(src, target, NULL, kernel, CV_MOP_OPEN, 1);//OPEN , CLOSE는 NULL해도 됨
}