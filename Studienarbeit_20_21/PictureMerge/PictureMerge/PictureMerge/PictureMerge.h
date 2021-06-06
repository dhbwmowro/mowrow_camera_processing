#pragma once

#ifndef PICTURE_MERGE_H
#define PICTURE_MERGE_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class PictureMerge{

public:
	PictureMerge(cv::Mat im1, cv::Mat im2) :im1(im1), im2(im2) {};

private:

	cv::Mat im1;
	cv::Mat im2;

	void mergePictures();
	void savePictures();


};



#endif // !1


