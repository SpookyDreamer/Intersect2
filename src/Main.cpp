#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Line.h"
#include "Point.h"
#include <unordered_set>

using namespace std;

class Hash_point
{
public:
	size_t operator()(Point *p) const
	{
		return std::hash<double>()(p->getX() + p->getY());
	}
};

class Equal_point {
public:
	bool operator()(Point *p1, Point *p2) const
	{
		return p1->equals(p2);
	}
};


int main(int argc, char* argv[])
{
	ifstream input;
	ofstream output;
	for (int i = 0; i < argc; i++) {
		if (strncmp(argv[i], "-i", 2) == 0) {
			input.open(argv[i + 1]);
		}
		else if (strncmp(argv[i], "-o", 2) == 0) {
			output.open(argv[i + 1]);
		}
	}
	
	unsigned int count;
	//input >> count;
	std::cin >> count;
	std::vector<Line*> lines;
	std::unordered_set<Point*, Hash_point, Equal_point> intersects;
	unsigned int i;
	for (i = 0; i < count; i++)
	{
		char type;
		double x1, y1, x2, y2;
		//input >> type >> x1 >> y1 >> x2 >> y2;
		std::cin >> type >> x1 >> y1 >> x2 >> y2;
		Point *point1 = new Point(x1, y1);
		Point *point2 = new Point(x2, y2);
		Line* line;
		if (type == 'L') {
			line = new Line(point1, point2);
		}
		else if (type == 'R') {
			line = new Radial(point1, point2);
		}
		else if (type == 'S') {
			line = new Segment(point1, point2);
		}
		else {
			return 1;
		}
		unsigned int j;
		unsigned int size = lines.size();
		for (j = 0; j < size; j++)
		{
			if (line->isParallel(lines[j]))
			{
				continue;
			}
			Point *p = line->intersect(lines[j]);
			if (line->isOnline(p) && lines[j]->isOnline(p)) {
				intersects.insert(p);
			}
		}
		lines.push_back(line);
	}

	/*int same = 0;
	unsigned int size = intersects.size();
	for (i = 0; i < size; i++)
	{
		Point* p = intersects[i];
		int j;
		for (j = i + 1;j < intersects.size();j++) {
			if (p->equals(intersects[j]))
			{
				same++;
				break;
			}
		}
		size = intersects.size();
	}*/
	
	std::wcout << intersects.size()  << std::endl;
	output << intersects.size();
	return 0;
}
