#pragma once
#include "Point.h"
#include "Line.h"
#include <vector>
#include <unordered_set>

class Hash_point
{
public:
	size_t operator()(Point* p) const
	{
		return std::hash<double>()(p->getX() + p->getY());
	}
};

class Equal_point {
public:
	bool operator()(Point* p1, Point* p2) const
	{
		return p1->equals(p2);
	}
};

class LineSeries
{
private:
	std::vector<Line*> lines;
	std::unordered_set<Point*, Hash_point, Equal_point> intersects;

public:
	LineSeries();

	virtual void add_line(Line* line);

	virtual void delete_line(Line* line);

	virtual void clear();

	virtual int cal_intersects();

	virtual std::unordered_set<Point*, Hash_point, Equal_point> getIntersects();

	virtual std::vector<Line*> getLines();

	virtual int get_lines_num();
};
