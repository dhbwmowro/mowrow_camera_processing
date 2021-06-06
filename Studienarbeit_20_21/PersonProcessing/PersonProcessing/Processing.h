#pragma once

#ifndef PROCESSING_H
#define PROCESSING_H

class Processing
{

public:
	Processing(cv::Mat im);

private:
	cv::Mat image;
	void floodfill();
	void findPersons();


};
#endif
