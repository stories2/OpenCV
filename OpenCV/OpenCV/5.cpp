#include "highgui.h"
#include "cv.h"

struct update_pixel
{
	int x, y, width, height, add;
};

void init(update_pixel *);
void process(IplImage *, update_pixel *);
void output(IplImage *);
void release(IplImage *);

int main()
{
	IplImage *img = cvLoadImage("target.jpg");
	update_pixel *pixel = new update_pixel;
	init(pixel);
	process(img, pixel);
	output(img);
	release(img);
	return 0;
}

void release(IplImage *img)
{
	cvReleaseImage(&img);

	cvDestroyAllWindows();
}

void output(IplImage *img)
{
	cvNamedWindow("ex5");
	cvShowImage("ex5", img);

	cvWaitKey(0);
}

void process(IplImage *img, update_pixel *update)
{
	cvSetImageROI(img, cvRect(update->x, update->y, update->width, update->height));
	cvAddS(img, cvScalar(update->add), img);
	cvResetImageROI(img);
}

void init(update_pixel *target)
{
	target->x = 100;
	target->y = 200;
	target->width = 300;
	target->height = 300;
	target->add = 100;
}