#include "highgui.h"
#include "cv.h"

void process(IplImage *, IplImage *, IplImage *);
void output(IplImage *, IplImage *, IplImage *);
void release(IplImage *, IplImage *, IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg"), 
		*result = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3),
		*result2 = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,3);
	process(img, result,result2);
	output(img, result, result2);
	release(img, result, result2);
	return 0;
}

void release(IplImage *source, IplImage *target, IplImage *target2)
{
	cvReleaseImage(&source);
	cvReleaseImage(&target);
	cvReleaseImage(&target2);

	cvDestroyAllWindows();
}

void output(IplImage *source, IplImage *target, IplImage *target2)
{
	cvNamedWindow("ex8-1");
	cvNamedWindow("ex8-2");

	cvShowImage("ex8-1", target);
	cvShowImage("ex8-2", target2);


	cvWaitKey(0);
}

void process(IplImage *source, IplImage *target, IplImage *target2)
{
	cvErode(source, target, NULL, 1);//ħ�� , �ּҰ� �������� ���� ������ �پ��� (��� ������ ���� �ϱ����� ���� ����)
	cvDilate(source, target2, NULL, 1);//��â , �ִ� �������� ��ο� ������ �پ��� (����� ������Ҹ� ã������ ���� ����)
}