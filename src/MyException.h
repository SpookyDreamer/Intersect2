#pragma once

#include<exception>  
#include<iostream>  
using namespace std;

//customized exception class 'myException'  
class WrongFormatException :public exception
{
public:
	WrongFormatException() :exception("ERROR! The file contents are in the wrong format. Please check the file contents.\n")
	{
	}
};

class UnableToConstructException :public exception
{
public:
	UnableToConstructException() :exception("ERROR! Since the two points given coincide, we cannot construct a line.\n")
	{
	}
};

class CoordinateOutOfRangeException :public exception
{
public:
	CoordinateOutOfRangeException() :exception("ERROR! Both horizontal and vertical values should be within  (-100000, 100000).\n")
	{
	}
};

class InfiniteIntersectionPointsException :public exception
{
public:
	InfiniteIntersectionPointsException() :exception("ERROR!There are infinite points of intersection between geometric objects .\n")
	{
	}
};