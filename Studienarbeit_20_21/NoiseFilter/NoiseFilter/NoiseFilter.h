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
	int MAX_KERNEL_LENGTH = 31;


	void filter();
	void saveImage();


};

#endif // !1