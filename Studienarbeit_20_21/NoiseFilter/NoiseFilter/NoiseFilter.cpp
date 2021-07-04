
#include "NoiseFilter.h"
#include <iostream>



int main() {

	std::cout << "Hello World" << std::endl;

	cv::Mat img = cv::imread("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\NoiseFilter\\NoiseTest1.png", cv::IMREAD_COLOR);//cv::samples::findFile(

	if (img.empty())
	{
		std::cout << "Could not read the image " << std::endl;
		return 1;
	}
	NoiseFilter nf = NoiseFilter(img);

	return 0;
}

NoiseFilter::NoiseFilter(cv::Mat img):img(img) {
	filter();
	saveImage();
}


void NoiseFilter::filter() {

		cv::medianBlur(img, dst, 5);


}
//int NoiseFilter::display_dst(int delay)
//{
//	//cv::imshow(window_name, dst);
//	int c = cv::waitKey(delay);
//	if (c >= 0) { return -1; }
//	return 0;
//}

void NoiseFilter::saveImage() {

	cv::imwrite("C:\\Users\\debinkli\\Documents\\DHBW\\Studienarbeit\\PictureMerge\\Filterd\\FiltertTest1.png", dst);
}