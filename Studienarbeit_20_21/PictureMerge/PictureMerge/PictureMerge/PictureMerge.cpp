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


PictureMerge::PictureMerge(cv::Mat imPerson, cv::Mat imUmgebung) :imP(imPerson), imU(imUmgebung) {

	mergePictures();
	savePictures();

}


void PictureMerge::mergePictures() {

	if (imP.rows== imU.rows&& imP.cols== imU.cols) {

		int rows = imP.rows;
		int cols = imP.cols;

		for (int x = 0; x <= rows; x++) {
			for (int y = 0; y <= cols; y++) {
				//Check color
				cv::Vec3b bgrP = imP.at<cv::Vec3b>(x, y);
				if (bgrP[0]==60&& bgrP[1]==20 && bgrP[2]==220) {

					imU.at<cv::Vec3b>(x, y) = imP.at<cv::Vec3b>(x, y);
				}

			}
		}
	}


}
void PictureMerge::savePictures() {

	imwrite("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\Merged\\Test1.png", imU);
}


