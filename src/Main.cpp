#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Line.h"
#include "Point.h"
#include "Main.h"
#include <unordered_set>
#include "lineSeries.h"
#include "Myexception.h"
using namespace std;
ifstream input;
ofstream output;

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
	//std::cin >> count;
	std::string strLine;
	
	// 首行只有一个字符串，且为非负。
	try {
		if (getline(input, strLine)) {
			//split line
			vector<string> res;
			stringstream aline(strLine);
			string result;
			while (aline >> result)
				res.push_back(result);
			//exception
			if (res.size() != 1) {
				throw WrongFormatException();
			}
			stringstream countstr(res[0]);
			if (!(countstr >> count)) {
				throw WrongFormatException();
			}
			if (count < 0) {
				throw WrongFormatException();
			}
		}
		else {
			throw WrongFormatException();
		}
	}catch(WrongFormatException& e){
		std::wcout << e.what() << std::endl;
		exit(-1);
	}
	

	LineSeries* ls = new LineSeries();
	int i;
	for (i = 0; i < count; i++) {
		char type;
		double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		//必须有这一行、这一行中第一个参数为L、R、S；其余为整数
		try {
			if (getline(input, strLine)) {
				//split line
				vector<string> res;
				stringstream aline(strLine);
				string result;
				while (aline >> result)
					res.push_back(result);
				//exception
				if (res.size() != 5) {
					throw WrongFormatException();
				}
				stringstream countstr(res[0]);
				if (!(countstr >> type)) {
					throw WrongFormatException();
				}
				if ((type!='L') && (type != 'R') && (type != 'S')) {
					throw WrongFormatException();
				}
				stringstream x1str(res[1]), y1str(res[2]), x2str(res[3]), y2str(res[4]);
				if ((!(x1str >> x1)) || (!(y1str >> y1)) || (!(x2str >> x2)) || (!(y2str >> y2))) {
					throw WrongFormatException();
				}
			}
			else {
				throw WrongFormatException();
			}
		}catch (WrongFormatException& e) {
			std::wcout << e.what() << std::endl;
			exit(-1);
		}


		//input >> type >> x1 >> y1 >> x2 >> y2;
		//std::cin >> type >> x1 >> y1 >> x2 >> y2;
		Point* point1 = new Point(x1, y1);
		Point* point2 = new Point(x2, y2);
		Line* line;
		try {
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
		}
		catch (UnableToConstructException& e) {
			std::wcout << e.what() << std::endl;
			exit(-1);
		}
		catch (CoordinateOutOfRangeException& e) {
			std::wcout << e.what() << std::endl;
			exit(-1);
		}
		
		ls->add_line(line);
	}

	/* test
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
	ls->delete_line(line);
	*/
	
	int res = ls->cal_intersects();

	std::wcout << res  << std::endl;
	output << res;
	return 0;
}
