#include <stdio.h>
#include <Windows.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define _CLASSIFIER "../Debug/haarcascades/aGest.xml"
#define _CAPTURE_NAME "CAM"

using namespace cv;
using namespace std;

int cascadeDetect(cv::VideoCapture capture, cv::CascadeClassifier cascade)
{
	int frameValid = 1;
	int det;
	cv::Mat frame;
	cv::Mat croppedFrame;

	int iLowH = 102;
	int iHighH = 150;

	int iLowS = 129;
	int iHighS = 255;

	int iLowV = 95;
	int iHighV = 255;

	try {
		capture >> frame; // get a new frame from webcam
		cv::resize(frame, frame, cv::Size(frame.cols, frame.rows), 0, 0, CV_INTER_NN); // downsample 1/2x
	}
	catch (cv::Exception& e) {
		std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
		frameValid = 0;
	}

	if (frameValid)
	{
		try {
			Mat grayframe;
			cvtColor(frame, grayframe, CV_BGR2GRAY);
			equalizeHist(grayframe, grayframe);

			std::vector<cv::Rect> faces;

			cascade.detectMultiScale(grayframe, faces,
				1.1, // increase search scale by 10% each pass
				3,   // merge groups of three detections
				CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
				cv::Size(30, 30));

			if (faces.size() > 0)
			{
				for (int i = 0; i < (signed)faces.size(); i++) {
					cv::Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
					cv::Point tr(faces[i].x, faces[i].y);

					croppedFrame = frame(faces[i]).clone();

					cv::Mat imgHSV;

					cvtColor(croppedFrame, imgHSV, COLOR_BGR2HSV); //imgOriginal�� BGR�̹����� HSV�̹����� ��ȯ�Ѵ�. imgHSV�� ��ȯ�� �̹��� �̴�. 

					cv::Mat imgThresholded;

					inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
					//imgHSV�̹����� HSV�̹����ε� �� �̹������� �ּ� HSV~ �ִ� HSV ���̿� �ִ� ���� ã�´�. ã�� �̹����� imgThresholded�� �ȴ�. �������̿� �ش�Ǵ� ��쿡 �Ͼ������ ��Ÿ����. 

					//morphological opening (removes small objects from the foreground)
					//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
					//dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

					//morphological closing (removes small holes from the foreground)
					//dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
					//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

					vector<vector<Point>> contours;

					findContours(imgThresholded, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
					//HSV�� �ش��ϴ� ��ü�� �������� ã�� �Լ��̴�. 

					int maxX = 0, minX = imgThresholded.cols, maxY = 0, minY = imgThresholded.rows;
					// �ʱ� ���� ǥ���ϴ� ȭ���� �ִ� ũ��� �����Ѵ�. 

					for (int i = 0; i<contours.size(); i++)               // ������ ������ ��ǥ���� ���� �Ʒ���ǥ�� ������ �� ��ǥ�� �̾Ƴ���. -> (minX,minY), (maxX,maxY)
					for (int j = 0; j<contours[i].size(); j++)
					{
						Point p = contours[i][j];

						maxX = max(maxX, p.x);
						minX = min(minX, p.x);

						maxY = max(maxY, p.y);
						minY = min(minY, p.y);
					}

					if (maxX == 0 || minX == imgThresholded.cols || maxY == 0 || minY == imgThresholded.rows)  //��ü�� ��Ƴ��� ���Ұ�쿡 �׸� �׸��� ���ϰ� �Ͽ���. 
					{
					}

					else{                 //�ʱⰪ�� ���ߴٴ� ���� ��ü�� ��Ƴ´ٴ� ���̹Ƿ� �׸� �׸��� �Ͽ���. 
						rectangle(frame, Point(faces[i].x + minX, faces[i].y + minY), Point(faces[i].x + maxX, faces[i].y + maxY), CV_RGB(0, 0, 255), 2.5, 8, 0);
						int x = faces[i].x + (maxX + minX) / 2;
						int y = faces[i].y + (maxY + minY) / 2;

						int w, h;

						int coordinates_x = int(65535 * x / (frame.cols * 0.8));
						int coordinates_y = int(65535 * y / (frame.rows * 0.8));
						
						//int coordinates_x = int(65535 * x / (faces[i].x + imgThresholded.cols));
						//int coordinates_y = int(65535 * maxY / (faces[i].y + imgThresholded.rows));

						//  y -> 540    x-> 960  
						//printf("(x,y) = ( %d , %d )\n", coordinates_x, coordinates_y);

						if (coordinates_x > 32768) coordinates_x = 32768 - (coordinates_x - 32768);
						else if (coordinates_x < 32768) coordinates_x = (32768 - coordinates_x) + 32768;
						
						/*
						if (coordinates_y > 32768) coordinates_y = 32768 - (coordinates_y - 32768);
						else if (coordinates_y < 32768) coordinates_y = (32768 - coordinates_y) + 32768;
						*/

						//printf("(x,y) = ( %d , %d )\n", coordinates_x, coordinates_y);
						printf("(x,y) = ( %d , %d ), ( %d , %d )\n", x, y, frame.cols, frame.rows);
						//printf("ȯ�� ��(x,y) = ( %d , %d )\n", coordinates_x, coordinates_y);

						mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, coordinates_x, coordinates_y, 0, 0);

						//printf("blue detect\n");
					}

					cv::rectangle(frame, lb, tr, cv::Scalar(0, 255, 0), 3, 4, 0);
				}
				// print the output
			}
			else{
				det = 0;
			}
			cv::imshow(_CAPTURE_NAME, frame);
		}
		catch (cv::Exception& e) {
			std::cerr << "Exception occurred. Ignoring frame... " << e.err << std::endl;
		}
	}
	return 0;
}

int main()
{
	cv::CascadeClassifier cascade;
	int result;

	cascade.load(_CLASSIFIER);
	if (cascade.empty()){
		printf("Cascade ������ �о�� �� �����ϴ�.\n");
		return -1;
	}

	IplImage* image = 0;
	cv::VideoCapture capture(0);
	cv::namedWindow(_CAPTURE_NAME, 0);
	cv::resizeWindow(_CAPTURE_NAME, 640, 480);

	while (true)
	{
		cascadeDetect(capture, cascade);

		if (cvWaitKey(30) >= 0){
			break;
		}
	}

	cvDestroyWindow(_CAPTURE_NAME);

	return 0;
}