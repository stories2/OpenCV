#include "highgui.h"
#include "cv.h"

#define pic_width	15000
#define pic_height	500
#define limit		10

struct database
{
	float data[limit];
	struct database *link;
};

void load(database *,char *, int *, int *);
void draw_img(IplImage *, database *, int, int);
float get_y(int, float);
float get_x(int, float);
void output(IplImage *);
void release(IplImage *);

int main()
{
	int height = 0, width = 0;
	IplImage *target = cvCreateImage(cvSize(pic_width,pic_height),IPL_DEPTH_8U,3);
	struct database *db = new database;
	load(db, "output.txt", &width, &height);
	draw_img(target, db, width, height);
	output(target);
	release(target);
	printf("debug\n");
	return 0;
}

void release(IplImage *target)
{
	cvSaveImage("output.jpg", target);
	cvDestroyAllWindows();
	cvReleaseImage(&target);
}

void output(IplImage *target)
{
	cvNamedWindow("result");
	cvShowImage("result", target);

	cvWaitKey(0);
}

void draw_img(IplImage *target, database *db, int width, int height)
{
	int threshold = 500, line_width = 2;
	db = db->link;
	cvLine(target, cvPoint(0, get_y(height, threshold)), cvPoint(get_x(width, pic_width), get_y(height, threshold)), cvScalar(50, 150, 250), line_width);
	while (db->link)
	{
		int x, y;
		x = get_x(width, db->data[3]);//카운트 변수
		y = get_y(height, db->data[0]);//압전센서
		//1 : 압력센서

		//cvSet2D(target,y , x, cvScalar(255,0,0));
		cvLine(target, cvPoint(x, y), cvPoint(get_x(width, db->link->data[3]), get_y(height, db->link->data[0])), cvScalar(255, 0, 0), line_width);
		cvLine(target, cvPoint(x, get_y(height, db->data[1])), cvPoint(get_x(width, db->link->data[3]), get_y(height, db->link->data[1])), cvScalar(100, 100, 100), line_width);
		//cvLine(target, cvPoint(get_x(width, db->link->data[3]), get_y(height, db->link->data[1])), cvPoint(get_x(width, db->data[3]), get_y(height, db->data[1])), cvScalar(0, 0, 0), 1);
		if (db->data[6])
		{
			cvLine(target, cvPoint(x, 0), cvPoint(x, pic_height), cvScalar(0, 255, 0), line_width);
		}
		if (db->data[7])
		{
			cvLine(target, cvPoint(x, 0), cvPoint(x, pic_height), cvScalar(0, 0, 255), line_width);
		}
		if (db->data[8])
		{
			cvLine(target, cvPoint(x, 0), cvPoint(x, pic_height), cvScalar(223, 78, 204), line_width);
		}
		if (db->data[9])
		{
			cvLine(target, cvPoint(x, 0), cvPoint(x, pic_height), cvScalar(106, 226, 186), line_width);
		}

		db = db->link;
	}

	printf("test");
}

float get_x(int width, float target)
{
	return (float)pic_width / width * target;
}

float get_y(int height, float target)
{
	return pic_height - ((float)pic_height / height * target);
}

void load(database *target, char *path, int *width, int *height)
{
	freopen(path, "r", stdin);
	int i;
	bool running = true; 
	database *node = NULL, *temp = target;
	while (running)
	{
		node = new database;
		for (i = 0; i < limit; i += 1)
		{
			scanf("%f", &node->data[i]);
			if (i == 0 && node->data[i] == -1)
			{
				running = false;
				break;
			}
		}

		if ((int)node->data[0] > *height)
		{
			*height = (int)node->data[0];
		}

		if ((int)node->data[1] > *height)
		{
			*height = (int)node->data[1];
		}
		*width = *width + 1;
		node->link = NULL;
		
		temp->link = node;
		temp = node;		
	}
}