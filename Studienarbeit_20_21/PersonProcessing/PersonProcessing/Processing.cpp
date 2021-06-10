#include "Processing.h"



Processing::Processing(cv::Mat im):image(im) {
	
	findPersons();

}

void Processing::findPersons() {
	//rows and cols
	pixelmap = std::vector<std::vector<Pixel>>();

	//Fill pixelmap
	for(int x = 0; x<image.cols; x++)
	{
		for (int y = 0; y < image.rows; y++)
		{
			Pixel p = Pixel(x, y);
			cv::Vec3b bgrP = image.at<cv::Vec3b>(x, y);
			if (bgrP[0]==60&& bgrP[1]==20 && bgrP[2]==220)
			{
				p.isPerson = true;
			}
			pixelmap[x][y] = p;

		}
	}

	for (std::vector<Pixel> vec : pixelmap) {
		for (Pixel pixel : vec) {
			if (pixel.isPerson) {
				pixel.marked = true;
				floodfill(pixel.x, pixel.y);
			}
		}
	}


}
void Processing::floodfill(int x, int y) {




}
