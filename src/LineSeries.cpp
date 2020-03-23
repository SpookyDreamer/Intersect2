#include "lineSeries.h"

LineSeries::LineSeries(){}

void LineSeries::add_line(Line* line)
{
	lines.push_back(line);
	return;
}

void LineSeries::delete_line(Line* line) 
{
	int i;
	for (i = 0; i < lines.size(); i++) {
		if (lines[i]->equals(line)) {
			lines.erase(lines.begin() + i);
		}
	}
}

int LineSeries::cal_intersects()
{
	int i;
	for (i = 0; i < lines.size(); i++) {
		int j;
		for (j = i + 1; j < lines.size(); j++) {
			Line* line1 = lines[i];
			Line* line2 = lines[j];
			if (line1->isParallel(line2)){
				continue;
			}
			Point* p = line1->intersect(line2);
			if (line1->isOnline(p) && line2->isOnline(p)) {
				intersects.insert(p);
			}
		}
	}
	return intersects.size();
}

void LineSeries::clear()
{
	lines.clear();
	intersects.clear();
	return;
}

std::vector<Line*> LineSeries::getLines()
{
	return lines;
}

std::unordered_set<Point*, Hash_point, Equal_point> LineSeries::getIntersects()
{
	return intersects;
}