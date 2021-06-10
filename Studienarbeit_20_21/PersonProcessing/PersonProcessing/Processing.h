#pragma once

#ifndef PROCESSING_H
#define PROCESSING_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>
#include "Pixel.h"
#include "Person.h"

class Processing
{

public:
	Processing(cv::Mat im);

private:
	cv::Mat image;
	std::vector<std::vector<Pixel>> pixelmap;
	std::vector<Person> persons;

	void floodfill(int x, int y);
	void findPersons();


};
#endif
