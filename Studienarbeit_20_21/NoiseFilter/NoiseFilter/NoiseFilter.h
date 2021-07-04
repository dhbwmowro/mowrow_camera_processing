#pragma once

#ifndef NOISE_FILTER_H
#define NOISE_FILTER_H


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"



class NoiseFilter
{
public:
	NoiseFilter(cv::Mat);

private:

	cv::Mat img;
	cv::Mat dst;
	int MAX_KERNEL_LENGTH = 31;
	int DELAY_BLUR = 100;


	int display_dst(int delay);


	void filter();
	void saveImage();


};

#endif // !1