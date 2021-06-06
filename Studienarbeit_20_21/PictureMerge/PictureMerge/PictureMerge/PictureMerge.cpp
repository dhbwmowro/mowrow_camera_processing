// PictureMerge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PictureMerge.h"


int main()
{
   //Open Pictures

	cv::Mat im1 = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\PTest1.png");
	cv::Mat im2 = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\UTest1.png");

	PictureMerge p = PictureMerge(im1, im2);
}

void PictureMerge::mergePictures() {



}
void PictureMerge::savePictures() {

}


