#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Line.h"
#include "Point.h"

using namespace std;

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
	input >> count;
	//std::cin >> count;
	std::vector<Line*> lines;
	std::vector<Point*> intersects;
	unsigned int i;
	for (i = 0; i < count; i++)
	{
		char type;
		double x1, y1, x2, y2;
		input >> type >> x1 >> y1 >> x2 >> y2;
		//std::cin >> type >> x1 >> y1 >> x2 >> y2;
		Point *point1 = new Point(x1, y1);
		Point *point2 = new Point(x2, y2);
		Line *line = new Line(point1, point2);
		unsigned int j;
		for (j = 0; j < lines.size(); j++)
		{
			if (line->isParallel(lines[j]))
			{
				continue;
			}
			Point *p = line->intersect(lines[j]);
			intersects.push_back(p);
		}
		lines.push_back(line);
	}

	int same = 0;
	for (i = 0; i < intersects.size(); i++)
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
	}
	
	std::wcout << intersects.size()  << std::endl;
	output << intersects.size() - same;
	return 0;
}
