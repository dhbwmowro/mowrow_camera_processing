#pragma once
#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
public:
	Pixel(int x, int y) :x(x), y(y) {}
	int x, y;
	bool isPerson = false;
	bool marked = false;




};

#endif