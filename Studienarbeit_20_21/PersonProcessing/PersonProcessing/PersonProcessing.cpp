
#include <iostream>
#include"Processing.h"
#include <opencv2/opencv.hpp>

int main()
{
	//Open Pictures

	cv::Mat im1 = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PersonProcessing\\Test1.png");
	

	Processing p = Processing(im1);
}