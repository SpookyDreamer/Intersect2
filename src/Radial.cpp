#include "Point.h"
#include "Line.h"


double Radial::getX1() {
	return x1;
}

double Radial::getY1() {
	return y1;
}

double Radial::getX2() {
	return x2;
}

double Radial::getY2() {
	return y2;
}



bool Radial::isOnline(Point* point)
{	
	if (x1 != x2) {
		double tmp1 = point->getX() - x1;//x-x1
		double tmp2 = x2 - x1;//x2-x1
		return tmp1 * tmp2 >= 0;//(x-x1)*(x2-x1)>=0
	}
	else {
		double tmp1 = point->getY() - y1;//y-y1
		double tmp2 = y2 - y1;//y2-y1
		return tmp1 * tmp2 >= 0;//(y-y1)*(y2-y1)>=0
	}
	
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
	if ((x1 != r->x1) || (y1 != r->y1)) {
		return false;
	}
	if (x1 != x2) {
		return (x1 - x2) * (r->x1 - r->x2) > 0;
	}
	else {
		return (y1 - y2) * (r->y1 - r->y2) > 0;
	}
	
}

bool Radial::inOneLine(Radial* r) {
	if ((A * r->B == B * r->A) && (A * r->C == C * r->A)) {
		return true;
	}
	return false;
}

/*
0:  0
1:  1
-1: INF
*/
int Radial::countIntersectinOneLine(Radial* r) {
	Point* r1 = new Point(r->x1, r->y1);
	Point* r2 = new Point(r->x2, r->y2);
	Point* this1 = new Point(x1, y1);
	
	double deltx1 = x2 - x1;
	double delty1 = y2 - y1;
	double deltx2 = r->x2 - r->x1;
	double delty2 = r->y2 - r->y1;
	double flag = deltx1 * deltx2 + delty1 * delty2;

	if (r->getType() == 'R') {//R-R
		if (flag > 0) {
			return -1;//同向，无数个
		}
		if (x1 == r->x1 && y1 == r->y1) {
			return 1;//恰好一个
		}
		double flag2 = (r->x1 - x1) * deltx1 + (r->y1 - y1) * delty1;
		if (flag2 > 0) {
			return -1;
		}
		else {
			return 0;
		}
	}
	else {//R-S
	
		if ((this->isOnline(r1)) && (this->isOnline(r2))) {
			return -1;
		}
		if (!(this->isOnline(r1)) && !(this->isOnline(r2))) {
			return 0;
		}
		if ((this->isOnline(r1)) && r1->equals(this1)) {
			return 1;
		}
		else if ((this->isOnline(r2)) && r2->equals(this1)) {
			return 1;
		}
		else {
			return -1;
		}
	}
	
}

