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
		
		cv::Mat Gras = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T4.png", cv::IMREAD_COLOR);
		cv::Mat Himmel = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T5.png", cv::IMREAD_COLOR);
		cv::Mat Weg = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T6.png", cv::IMREAD_COLOR);
		cv::Mat Sonne = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T1.png", cv::IMREAD_COLOR);
		cv::Mat Wolke = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T2.png", cv::IMREAD_COLOR);
		cv::Mat Vegetation = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T3.png", cv::IMREAD_COLOR);
		cv::Mat Person = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\T7.png", cv::IMREAD_COLOR);
		

		if (Gras.empty())
		{
			std::cout << "Could not read the image " << std::endl;
			return 1;
		}

		std::vector<cv::Mat> images;
		images.push_back(Gras);
		images.push_back(Himmel);
		images.push_back(Weg);
		images.push_back(Sonne);
		images.push_back(Wolke);
		images.push_back(Vegetation);
		images.push_back(Person);
		//cv::imshow("Display window", imP);
		PictureMerge p = PictureMerge(images);
		return 0;

	}
	catch (const std::exception e) {
		std::cout << e.what() << std::endl;
	}


}


PictureMerge::PictureMerge(std::vector<cv::Mat> images) :images(images) {

	
	mergePictures();
	//savePictures();

}


void PictureMerge::mergePictures() {

	if (checkImages()) {

		int cols = images[0].cols;
		int rows = images[0].rows;
		
		newImage.cols = cols;
		newImage.rows = rows;
		cv::Vec3b black;
		black[0] = 0;
		black[1] = 0;
		black[2] = 0;
		
		for (int x = 0; x <= cols; x++) {
			for (int y = 0; y <= rows; y++) {
				newImage.at<cv::Vec3b>(x, y) = black;
			}
		}

		
		for (cv::Mat img : images) {
			for (int x = 0; x <= cols; x++) {
				for (int y = 0; y <= rows; y++) {
					//Check color
					cv::Vec3b bgr = img.at<cv::Vec3b>(x, y);
					if (checkColor(bgr)) {
						
						newImage.at<cv::Vec3b>(x, y) = img.at<cv::Vec3b>(x, y);
					}

				}
			}
		}
	}


}
void PictureMerge::savePictures() {

	cv::imwrite("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\Merged\\Test1.png", newImage);
}

bool PictureMerge::checkImages() {
	int cols = images[0].cols;
	int rows = images[0].rows;
	for (cv::Mat img : images) {
		if (img.cols != cols || img.rows != rows) {
			return false;
		}
	}
	return true;
}

bool PictureMerge::checkColor(cv::Vec3b bgr) {
	//true when color isnt black (0,0,0)
	if (bgr[0] != 0 && bgr[1] != 0 && bgr[2] != 0) {
		return true;
	}
	return false;


}