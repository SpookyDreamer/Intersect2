#include "Line.h"
#include "Point.h"

bool Segment::isOnline(Point* point)
{
	double tmp1 = point->getX() - x1;//x-x1
	double tmp2 = point->getX() - x2;//x-x2
	return tmp1 * tmp2 <= 0;//(x-x1)*(x-x2)<=0
}