#include "Point.h"
#include "Line.h"

bool Radial::isOnline(Point* point)
{
	double tmp1 = point->getX() - x1;//x-x1
	double tmp2 = x2 - x1;//x2-x1
	return tmp1 * tmp2 >= 0;//(x-x1)*(x2-x1)>=0
}

bool Radial::equals(Line* line)
{
	if (type != line->getType()) {
		return false;
	}
	Radial* r = (Radial*)line;
	if (!isParallel(r)) {
		return false;
	}
	if (A * r->C != C * r->A) {
		return false;
	}
	if (x1 != r->x1) {
		return false;
	}
	return (x1 - x2) * (r->x1 - r->x2) > 0;
}