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
	cvErode(source, target, NULL, 1);//침식 , 최소값 연산으로 밝은 영역이 줄어든다 (얼룩 잡음을 제거 하기위해 종종 쓰임)
	cvDilate(source, target2, NULL, 1);//팽창 , 최댓값 연산으로 어두운 영역이 줄어든다 (연결된 구성요소를 찾기위해 종종 쓰임)
}