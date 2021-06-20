#pragma once

#ifndef NOISE_FILTER_H
#define NOISE_FILTER_H


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


class NoiseFilter
{
public:
	NoiseFilter(cv::Mat);

private:

	cv::Mat imP;
	cv::Mat imU;

	void mergePictures();
	void savePictures();


};

#endif // !1