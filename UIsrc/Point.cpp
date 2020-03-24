#include "Point.h"
#include <math.h>

Point::Point(double xAxis, double yAxis)
{
	x = xAxis;
	y = yAxis;
}

double Point::getX()
{
	return x;
}

double Point::getY()
{
	return y;
}

bool Point::equals(Point *point)
{
	return fabs(x - point->x) < 1e-10 && fabs(y - point->y) < 1e-10;
}
