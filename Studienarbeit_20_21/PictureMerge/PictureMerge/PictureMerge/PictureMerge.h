#pragma once

#ifndef PICTURE_MERGE_H
#define PICTURE_MERGE_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class PictureMerge{

public:
	PictureMerge(cv::Mat, cv::Mat);

private:

	cv::Mat imP;
	cv::Mat imU;

	void mergePictures();
	void savePictures();


};



#endif // !1


