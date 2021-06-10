#pragma once

#ifndef PERSON_H
#define PERSON_H

#include"Pixel.h"
#include <vector>

class Person
{

public:
	Person(int cols, int rows);
	void setPixel(Pixel p);


private:

	std::vector<std::vector<Pixel>> pixelmap;

	int cols;
	int rows;


};
#endif
