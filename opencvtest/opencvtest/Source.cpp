#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/video/video.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <time.h>
#include <fstream>

using namespace cv;
using namespace std;

#pragma warning(disable : 4996) 

int main(int argc, char* argv[])
{
	cv::VideoCapture capture("rtsp://192.168.1.1:9099/stream");
	//cv::VideoCapture capture("b.avi");

	if (!capture.isOpened())
	{
		std::cout << "Read video Failed !" << std::endl;
	}

	cv::Mat frame;
	//cv::namedWindow("video test");

	int frame_num = capture.get(cv::CAP_PROP_FRAME_COUNT);
	std::cout << "total frame number is: " << frame_num << std::endl;

	time_t rawtimeFileName;
	time(&rawtimeFileName);
	char *timeFileName = ctime(&rawtimeFileName);
	char a[] = ".avi";
	char *b;
	b = a;

	std::string src1(timeFileName);
	std::string src2(b);
	std::string dest = src1 + src2;
	std::replace(dest.begin(), dest.end(), ' ', '_');
	std::replace(dest.begin(), dest.end(), ':', '_');
	std::replace(dest.begin(), dest.end(), '\n', '_');
	dest.c_str();
	
	int width = (int)capture.get(cv::CAP_PROP_FRAME_WIDTH);
	int height = (int)capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	int fps = (int)capture.get(cv::CAP_PROP_FPS);

	VideoWriter writer(dest, 
						CV_FOURCC('H','2','6','4'), 
						50, 
						Size(width, height)
						);

	cv::Point origin;
	origin.x = 100;
	origin.y = 100;

	for (int i = 0; i < 1000; ++i)
	{
		capture >> frame;
		//std::string s = std::to_string(i);
		//char const *pchar = s.c_str();

		time_t rawtime;
		time(&rawtime);
		char const *time = ctime(&rawtime);
		cv::putText(frame, time, origin, cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 255), 2, 8, 0);
		writer << frame;

		//imshow("video test", frame);
		/*if (cv::waitKey(30) == 'q')
		{
			break;
		}*/
	}

	writer.release();
	//cv::destroyWindow("video test");
	capture.release();
	return 0;
}