#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Line.h"
#include "Point.h"
#include "Main.h"
#include <unordered_set>
#include "lineSeries.h"

using namespace std;
ifstream input;
ofstream output;

int calculate(unsigned int count)
{
	//std::cin >> count;
	std::vector<Line*> lines;
	std::unordered_set<Point*, Hash_point, Equal_point> intersects;
	unsigned int i;
	for (i = 0; i < count; i++)
	{
		char type;
		double x1, y1, x2, y2;
		input >> type >> x1 >> y1 >> x2 >> y2;
		//std::cin >> type >> x1 >> y1 >> x2 >> y2;
		Point* point1 = new Point(x1, y1);
		Point* point2 = new Point(x2, y2);
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
			Point* p = line->intersect(lines[j]);
			if (line->isOnline(p) && lines[j]->isOnline(p)) {
				intersects.insert(p);
			}
		}
		lines.push_back(line);
	}
	return intersects.size();
}


int main(int argc, char* argv[])
{
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
	
	LineSeries* ls = new LineSeries();
	int i;
	for (i = 0; i < count; i++) {
		char type;
		double x1, y1, x2, y2;
		//input >> type >> x1 >> y1 >> x2 >> y2;
		std::cin >> type >> x1 >> y1 >> x2 >> y2;
		Point* point1 = new Point(x1, y1);
		Point* point2 = new Point(x2, y2);
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
		ls->add_line(line);
	}
	int res = ls->cal_intersects();

	std::wcout << res  << std::endl;
	output << res;
	return 0;
}
