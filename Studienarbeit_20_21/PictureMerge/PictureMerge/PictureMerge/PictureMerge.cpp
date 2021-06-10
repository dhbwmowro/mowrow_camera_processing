// PictureMerge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PictureMerge.h"


int main()
{
   //Open Pictures
	std::cout << "Hello World" << std::endl;
	std::string pathP = "C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\PTest1.png"; //C:\Users\debinkli\Documents\DHBW\Studienarbeit\PictureMerge
	std::string pathU = ".\\UTest1.png";//"C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\UTest1.png";
	cv::Mat imP = cv::imread(pathP);
	cv::Mat imU = cv::imread(pathU, cv::IMREAD_COLOR);


	if (imU.empty())
	{
		std::cout << "Could not read the image: " << std::endl;
		return 1;
	}

	//cv::imshow("Display window", imP);
	PictureMerge p = PictureMerge(imP, imU);
}


PictureMerge::PictureMerge(cv::Mat imP, cv::Mat imU) :imP(imP), imU(imU) {

	mergePictures();
	//savePictures();

}


void PictureMerge::mergePictures() {

	//if (imP.rows== imU.rows&& imP.cols== imU.cols) {

	//	int cols = imP.cols;
	//	int rows = imP.rows;
	//	

	//	for (int x = 0; x <= cols; x++) {
	//		for (int y = 0; y <= rows; y++) {
	//			//Check color
	//			cv::Vec3b bgrP = imP.at<cv::Vec3b>(x, y);
	//			if (bgrP[0]==60&& bgrP[1]==20 && bgrP[2]==220) {

	//				imU.at<cv::Vec3b>(x, y) = imP.at<cv::Vec3b>(x, y);
	//			}

	//		}
	//	}
	//}


}
void PictureMerge::savePictures() {

	//cv::imwrite("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\Merged\\Test1.png", imU);
}


