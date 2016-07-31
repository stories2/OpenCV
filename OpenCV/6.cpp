#include "highgui.h"
#include "cv.h"

struct update_data
{
	int x, y, width, height;
	double alpha, beta;
};

void init(IplImage *, char *);
void process(IplImage *, IplImage *, update_data *);
void data_set(update_data *);
void output(IplImage *, IplImage *);
void release(IplImage *, IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg"), *img2 = cvLoadImage("target2.jpg");
	update_data *data = new update_data;

	//init(img, "target.jpg");
	//init(img2, "target2.jpg");
	data_set(data);

	process(img, img2, data);
	output(img, img2);
	release(img, img2);
}

void release(IplImage *src1, IplImage *src2)
{
	cvReleaseImage(&src1);
	cvReleaseImage(&src2);

	cvDestroyAllWindows();
}

void output(IplImage *src1, IplImage *src2)
{
	cvNamedWindow("ex6");
	cvShowImage("ex6", src1);

	cvWaitKey(0);
}

void process(IplImage *src1, IplImage *src2, update_data *data)
{
	cvSetImageROI(src1, cvRect(data->x, data->y, data->width, data->height));
	cvSetImageROI(src2, cvRect(data->x, data->y, data->width, data->height));
	cvAddWeighted(src1, data->alpha, src2, data->beta, 0, src1);
	cvResetImageROI(src1);
}

void data_set(update_data *target)
{
	target->x = 100;
	target->y = 100;
	target->width = 300;
	target->height = 300;
	target->alpha = 0.5;
	target->beta = 0.5;
}

void init(IplImage *target , char *path)
{
	target = cvLoadImage(path);
}