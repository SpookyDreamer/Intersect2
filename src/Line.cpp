#include "Line.h"
#include "Point.h"
#include "MyException.h"

Line::Line(Point* point1, Point* point2)
{
	if (point1->equals(point2)) {
		throw UnableToConstructException();
	}
	int x1, y1, x2, y2;
	x1 = point1->getX();
	y1 = point1->getY();
	x2 = point2->getX();
	y2 = point2->getY();
	if (x1 >= 100000 || x1 <= -100000 || y1 >= 100000 || y1 <= -100000 || x2 >= 100000 || x2 <= -100000 || y2 >= 100000 || y2 <= -100000) {
		throw CoordinateOutOfRangeException();
	}

	type = 'L';
	A = point2->getY() - point1->getY();
	B = point1->getX() - point2->getX();
	double tmp = point2->getX() * point1->getY();
	C = tmp - point1->getX() * point2->getY();
}

bool Line::isParallel(Line *line)
{
	return A * line->B == B * line->A;
}

Point *Line::intersect(Line *line)//求不重合、不平行的两直线的交点
{
	//((b1*c2-b2*c1)/(a1*b2-a2*b1)，(a2*c1-a1*c2)/(a1*b2-a2*b1))
	double x = (B * line->C - line->B * C) / (A * line->B - line->A * B);
	double y = (line->A * C- A * line->C)/(A * line->B- line->A * B);
	Point *point = new Point(x, y);
	return point;
}

bool Line::isOnline(Point* point)
{
	return true;
}

bool Line::equals(Line* line)
{
	if (type != line->type) {
		return false;
	}
	if (!isParallel(line)) {
		return false;
	}
	return A * line->C == C * line->A;
}

char Line::getType()
{
	return type;
}

bool Line::inOneLine(Line* l) {
	if ((A * l->B == B * l->A) && (A * l->C == C * l->A)) {
		return true;
	}
	return false;
}