#include "pch.h"
#include "CppUnitTest.h"
#include "..//intersect/Line.h"
#include "..//intersect/Point.h"
#include "..//intersect/Radial.cpp"
#include "..//intersect/Segment.cpp"
#include "..//intersect/Main.cpp"
#include <vector>
#include <iostream>
#include <unordered_set>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace intersectTest
{
	TEST_CLASS(intersectTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Point* point1 = new Point(0, 0);
			Point* point2= new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 0);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 0.5);
			Assert::AreEqual(res->getY(), 0.5);
		}

		TEST_METHOD(TestMethod2)
		{
			Point* point1 = new Point(1, 0);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 1.0);
			Assert::AreEqual(res->getY(), 2.0);
		}

		TEST_METHOD(TestMethod3)
		{
			Point* point1 = new Point(0, 0);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Assert::AreEqual(line1->isParallel(line2), true);
		}

		TEST_METHOD(TestMethod4)
		{
			Point* point1 = new Point(0, 1);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 0.0);
			Assert::AreEqual(res->getY(), 1.0);
		}

		TEST_METHOD(TestMethod5)
		{
			Point* point1 = new Point(4321, 4324);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(543, 3422);
			Point* point4 = new Point(4321, 4324);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 4321.0);
			Assert::AreEqual(res->getY(), 4324.0);
		}

		TEST_METHOD(TestMethod6)
		{
			Point* point1 = new Point(2, 0);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 0.5);
			Assert::AreEqual(res->getY(), 1.5);
		}

		TEST_METHOD(TestMethod7)
		{
			Point* point1 = new Point(0, 0);
			Point* point2 = new Point(-1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), -0.5);
			Assert::AreEqual(res->getY(), 0.5);
		}

		TEST_METHOD(TestMethod8)
		{
			Point* point1 = new Point(13222, 0);
			Point* point2 = new Point(5123, 0);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), -1.0);
			Assert::AreEqual(res->getY(), 0.0);
		}

		TEST_METHOD(TestMethod9)
		{
			Point* point1 = new Point(15123, 122);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(1, 2);
			Point* point4 = new Point(15123, 122);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 15123.0);
			Assert::AreEqual(res->getY(), 122.0);
		}

		TEST_METHOD(TestMethod10)
		{
			Point* point1 = new Point(31315, 1223);
			Point* point2 = new Point(1, 1);
			Line* line1 = new Line(point1, point2);
			Point* point3 = new Point(31315, 1223);
			Point* point4 = new Point(0, 1);
			Line* line2 = new Line(point3, point4);
			Point* res = line1->intersect(line2);
			Assert::AreEqual(res->getX(), 31315.0);
			Assert::AreEqual(res->getY(), 1223.0);
		}

		TEST_METHOD(TestMethod11)
		{
			Point* point1 = new Point(0, 0);
			Point* point2 = new Point(0, 0);
			Assert::AreEqual(point1->equals(point2), true);
		}

		TEST_METHOD(TestMethod12)
		{
			unsigned int count = 3;
			int res = calculate(count);
			Assert::AreEqual(res, 1);
		}
	};
}
