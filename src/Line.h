#pragma once
#include "Point.h"

class Line
{
protected:
	double A = 0;
	double B = 0;
	double C = 0;

public:
	Line(Point* point1, Point* point2);

	virtual bool isParallel(Line* line);

	virtual Point* intersect(Line* line);

	virtual bool isOnline(Point* point);
};

class Radial :public Line
{
protected:
	double x1 = 0;
	double x2 = 0;

public:
	Radial(Point* point1, Point* point2) :Line(point1, point2) {
		x1 = point1->getX();
		x2 = point2->getX();
	}

	virtual bool isOnline(Point* point);
};

class Segment :public Radial
{
public:
	Segment(Point* point1, Point* point2) :Radial(point1, point2){}

	virtual bool isOnline(Point* point);
};