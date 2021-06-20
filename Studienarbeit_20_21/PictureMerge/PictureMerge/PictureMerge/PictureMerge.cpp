// PictureMerge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PictureMerge.h"


int main(int argc, char** argv)
{
	//std::ofstream myfile;
	//myfile.open("PTest1.png");
	////myfile << "Writing this to a file.\n";
	//myfile.close();

   //Open Pictures
	std::cout << "Hello World" << std::endl;	//"C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\UTest1.png";
	try {

		//std::string pathP = cv::samples::findFile("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\PTest1.png"); //"C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\PTest1.png"; 
		//std::string pathU = cv::samples::findFile("UTest1.png");
		
		cv::Mat imP = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\PTest1.png", cv::IMREAD_COLOR);
		cv::Mat imU = cv::imread("UTest1.png", cv::IMREAD_COLOR);//cv::samples::findFile(

		if (imU.empty())
		{
			std::cout << "Could not read the image " << std::endl;
			return 1;
		}

		//cv::imshow("Display window", imP);
		PictureMerge p = PictureMerge(imP, imU);
		return 0;

	}
	catch (const std::exception e) {
		std::cout << e.what() << std::endl;
	}


}


PictureMerge::PictureMerge(cv::Mat imP, cv::Mat imU) :imP(imP), imU(imU) {

	mergePictures();
	//savePictures();

}


void PictureMerge::mergePictures() {

	if (imP.rows== imU.rows&& imP.cols== imU.cols) {

		int cols = imP.cols;
		int rows = imP.rows;
		

		for (int x = 0; x <= cols; x++) {
			for (int y = 0; y <= rows; y++) {
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

	cv::imwrite("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\Merged\\Test1.png", imU);
}


