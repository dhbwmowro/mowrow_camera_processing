#include "Person.h"

Person::Person(int cols, int rows) : cols(cols), rows(rows) {

	init();

}

void Person::init() {
	//pixelmap initialisieren
	pixelmap = std::vector<std::vector<Pixel>>();
	pixelmap.resize(rows);
	for (int i = 0; i < rows; ++i)
		pixelmap[i].resize(cols);

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			pixelmap[x][y] = Pixel(x, y);

		}
	}
}

void Person::setPixel(Pixel p) {
	pixelmap[p.x][p.y] = p;
	
}
