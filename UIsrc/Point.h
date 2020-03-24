#pragma once

class Point
{
private:
	double x = 0;
	double y = 0;

public:
	Point(double xAxis, double yAxis);

	virtual double getX();

	virtual double getY();

	virtual bool equals(Point *point);
};
