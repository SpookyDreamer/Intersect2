#include "Point.h"
#include "Line.h"

bool Radial::isOnline(Point* point)
{
	double tmp1 = point->getX() - x1;//x-x1
	double tmp2 = x2 - x1;//x2-x1
	return tmp1 * tmp2 >= 0;//(x-x1)*(x2-x1)>=0
}