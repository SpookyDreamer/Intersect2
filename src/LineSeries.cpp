#include "lineSeries.h"
#include "MyException.h"
LineSeries::LineSeries(){}

void LineSeries::add_line(Line* line)
{
	
	int lineNum = lines.size();
	int i;
	for (i = 0; i < lineNum; i++) {
		Line* l = lines[i];
		char type1 = l->getType();
		if (!line->inOneLine(l)) {
			continue;
		}
		if (line->getType() == 'L' || l->getType() == 'L') {
			throw InfiniteIntersectionPointsException();
		}
		Radial* r0 = (Radial*)line;
		Radial* r1 = (Radial*)l;
		int tmp = r0->countIntersectinOneLine(r1);
		if (tmp < 0) {
			throw InfiniteIntersectionPointsException();
		}
	}

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
			if (lines[i]->isParallel(lines[j]) ){
				if ((lines[i]->getType() == 'L' || lines[j]->getType() == 'L')) {
					continue;
				}
				Radial* line1 = (Radial*)lines[i];
				Radial* line2 = (Radial*)lines[j];
				if (!line1->inOneLine(line2)) {
					continue;
				}
				if (line1->countIntersectinOneLine(line2) == 0) {
					continue;
				}
				Point* line1_1 = new Point(line1->getX1(), line1->getY1());
				Point* line1_2 = new Point(line1->getX2(), line1->getY2());
				if (line2->isOnline(line1_1)) {
					intersects.insert(line1_1);
				}
				else {
					intersects.insert(line1_2);
				}
			}
			
			Point* p = lines[i]->intersect(lines[j]);
			if (lines[i]->isOnline(p) && lines[j]->isOnline(p)) {
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

int LineSeries::get_lines_num() {
	return intersects.size();
}