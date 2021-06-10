#include "Person.h"

Person::Person(int cols, int rows) : cols(cols), rows(rows) {

	//pixelmap initialisieren
	pixelmap = std::vector<std::vector<Pixel>>();
	pixelmap.resize(rows);
	for (int i = 0; i < rows; ++i)
		pixelmap[i].resize(cols);

}


void Person::setPixel(Pixel p) {
	pixelmap[p.x][p.y] = p;
	
}
