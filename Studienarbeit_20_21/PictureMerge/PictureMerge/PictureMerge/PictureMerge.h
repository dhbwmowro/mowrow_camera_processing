#pragma once

#ifndef PICTURE_MERGE_H
#define PICTURE_MERGE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>


class PictureMerge{

public:
	PictureMerge(std::vector<cv::Mat> images);

private:

	std::vector<cv::Mat> images;
	cv::Mat newImage;
	
	void mergePictures();
	void savePictures();

	bool checkImages();
	bool checkColor(cv::Vec3b bgr);

};



#endif // !1


