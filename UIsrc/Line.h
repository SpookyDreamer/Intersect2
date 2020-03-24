#pragma once
#include "Point.h"

class Line
{
protected:
	char type;
	double A = 0;
	double B = 0;
	double C = 0;
	Point* point1;
	Point* point2;

public:
	Line(Point* point1, Point* point2);

	virtual bool isParallel(Line* line);

	virtual Point* intersect(Line* line);

	virtual bool isOnline(Point* point);

	virtual bool equals(Line* line);

	virtual char getType();

	virtual bool inOneLine(Line* l);

	virtual Point* getPoint1();

	virtual Point* getPoint2();
};

class Radial :public Line
{
protected:
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;

public:
	Radial(Point* point1, Point* point2) :Line(point1, point2) {
		type = 'R';
		x1 = point1->getX();
		x2 = point2->getX();
		y1 = point1->getY();
		y2 = point2->getY();
	}

	virtual bool isOnline(Point* point);

	virtual bool equals(Line* line);

	virtual bool inOneLine(Radial* r);

	virtual int countIntersectinOneLine(Radial* r);

	virtual double getX1();
	virtual double getY1();
	virtual double getX2();
	virtual double getY2();

};

class Segment :public Radial
{
public:
	Segment(Point* point1, Point* point2) :Radial(point1, point2){
		type = 'S';
	}

	virtual bool isOnline(Point* point);

	virtual bool equals(Line* line);

	virtual int countIntersectinOneLine(Radial* r);

};