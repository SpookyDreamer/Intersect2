#include "Line.h"
#include "Point.h"

bool Segment::isOnline(Point* point)
{
	if (x1 != x2) {
		double tmp1 = point->getX() - x1;//x-x1
		double tmp2 = point->getX() - x2;//x-x2
		return tmp1 * tmp2 <= 0;//(x-x1)*(x-x2)<=0
	}
	else {
		double tmp1 = point->getY() - y1;//x-x1
		double tmp2 = point->getY() - y2;//x-x2
		return tmp1 * tmp2 <= 0;//(x-x1)*(x-x2)<=0
	}
	
}

bool Segment::equals(Line* line)
{
	if (type != line->getType()) {
		return false;
	}
	Segment* s = (Segment*)line;
	if (!isParallel(s)) {
		return false;
	}
	if (A * s->C != C * s->A) {
		return false;
	}
	return (((x1 == s->x1) && (y1 == s->y1) && (x2 == s->x2) && (y2 == s->y2)) 
			|| ((x1 == s->x2) && (y1 == s->y2) && (x2 == s->x1) && (y2 == s->y1)));
}

int Segment::countIntersectinOneLine(Radial* r) {
	Point* this1 = new Point(x1, y1);
	Point* this2 = new Point(x2, y2);
	Point* r1 = new Point(r->getX1(), r->getY1());
	Point* r2 = new Point(r->getX2(), r->getY2());
	if (r->getType() == 'R') {
		if (r->isOnline(this1) && r->isOnline(this2)) {
			return -1;
		}
		if (!(r->isOnline(this1)) && !(r->isOnline(this2))) {
			return 0;
		}
		if (r->isOnline(this1) && r1->equals(this1)) {
			return 1;
		}
		else if (r->isOnline(this2) && r1->equals(this2)) {
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		if (r->isOnline(this1) && r->isOnline(this2)) {
			return -1;
		}
		if (!(r->isOnline(this1)) && !(r->isOnline(this2))) {
			return 0;
		}
		if (r->isOnline(this1) && (r1->equals(this1) || r2->equals(this1))) {
			return 1;
		}
		else if (r->isOnline(this2) && (r1->equals(this2) || r2->equals(this2 ))){
			return 1;
		}
		else {
			return -1;
		}
	}
}