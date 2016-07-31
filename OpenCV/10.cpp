/*
Flood Fill은 원하는 이미지의 한 좌표를 기준으로 loDiff <= scalar <= upDiff 인 경우 내가 원하는 색깔을
칠하는 기법이다
*/


#include "highgui.h"
#include "cv.h"

void SetImageFloodFill(IplImage *);
void ShowImage(IplImage *);
void ReleaseImage(IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg");
	SetImageFloodFill(img);
	ShowImage(img);
	ReleaseImage(img);
	return 0;
}

void SetImageFloodFill(IplImage *img)
{
	CvPoint *imgPoint = new CvPoint;
	imgPoint->x = img->width / 2;
	imgPoint->y = img->height / 2;

	CvScalar *imgScalar = new CvScalar;
	imgScalar->val[0] = 215; 
	imgScalar->val[1] = 59;
	imgScalar->val[2] = 62;

	cvFloodFill(img, *imgPoint, *imgScalar, cvScalarAll(7.0), cvScalarAll(7.0), NULL, 4, NULL);
}

void ReleaseImage(IplImage *img)
{
	cvReleaseImage(&img);
	cvDestroyAllWindows();
}

void ShowImage(IplImage *img)
{
	cvNamedWindow("Flood Fill");
	cvShowImage("Flood Fill", img);

	cvWaitKey(0);
}