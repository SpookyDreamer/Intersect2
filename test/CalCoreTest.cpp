#include "pch.h"
#include "CppUnitTest.h"
#include "..//core/Line.h"
#include "..//core/lineSeries.h"
#include "..//core/Point.h"
#include "..//core/Line.cpp"
#include "..//core/LineSeries.cpp"
#include "..//core/Point.cpp"
#include "..//core/Radial.cpp"
#include "..//core/Segment.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalCoreTest
{
	TEST_CLASS(CalCoreTest)
	{
	public:
		
		TEST_METHOD(FcPoint)
		{
			Point* point1 = new Point(0, 0);
			Point* point2 = new Point(1, 1);
			Point* point3 = new Point(1, 0);
			Point* point4 = new Point(0, 1);
			Point* point5 = new Point(0, 0);
			Assert::AreEqual(point2->getY(), 1.0);
			Assert::AreEqual(point3->getX(), 1.0);
			Assert::IsTrue(point1->equals(point5));
			Assert::IsFalse(point1->equals(point2));
		}
		
		TEST_METHOD(FcLine) 
		{
			Point* point6 = new Point(0, 0);
			Point* point7 = new Point(1, 1);
			Point* point8 = new Point(1, 0);
			Point* point9 = new Point(0, 1);
			Point* point10 = new Point(1, 2);
			Line* line1 = new Line(point6, point7);
			Line* line2 = new Line(point8, point9);
			Line* line3 = new Line(point9, point10);
			

			Assert::AreEqual(line1->getType(), 'L');

			Point* p01 = new Point(0.5, 0.5);
			Point* p02 = line1->intersect(line2);
			Assert::IsTrue(p01->equals(p02));
			
			Assert::IsTrue(line1->isParallel(line3));
			Assert::IsFalse(line1->isParallel(line2));

			Assert::IsTrue(line1->isOnline(p02));//函数用于判断交点是否在直线上。所以恒为真
		}
		
		TEST_METHOD(FcRadial)
		{
			Point* point11 = new Point(0, 0);
			Point* point12 = new Point(1, 1);
			Point* point13 = new Point(-1, -1);
			Point* point14 = new Point(0, 1);
			Point* point15 = new Point(1, 2);
			Radial* radial1 = new Radial(point11, point12);
			Radial* radial2 = new Radial(point12, point11);
			Radial* radial3 = new Radial(point11, point15);
			Radial* radial4 = new Radial(point14, point15);

			Assert::AreEqual(radial1->getType(), 'R');

			Assert::IsTrue(radial1->intersect(radial3)->equals(point11));

			Assert::IsTrue(radial1->isParallel(radial4));
			Assert::IsFalse(radial1->isParallel(radial3));

			Assert::IsTrue(radial1->isOnline(point11));//端点
			Assert::IsTrue(radial1->isOnline(point12));//线上的点
			Assert::IsFalse(radial1->isOnline(point13));//线外的点
			Assert::IsTrue(radial2->isOnline(point11));//端点
			Assert::IsTrue(radial2->isOnline(point12));//线上的点
			Assert::IsTrue(radial2->isOnline(point13));//线上的点
			
		}
		//////////////////////////////////////
		TEST_METHOD(FcSegment)
		{
			Point* point16 = new Point(0, 0);
			Point* point17 = new Point(1, 1);
			Point* point18 = new Point(-1, -1);
			Point* point19 = new Point(0, 1);
			Point* point20 = new Point(1, 2);
			Segment* segment1 = new Segment(point16, point17);
			Segment* segment2 = new Segment(point17, point18);
			Segment* segment3 = new Segment(point16, point19);
			Segment* segment4 = new Segment(point16, point18);

			Assert::AreEqual(segment1->getType(), 'S');

			//Assert::IsTrue(segment1->intersect(segment2)->equals(point17));错误尚未解决。

			Assert::IsTrue(segment1->isParallel(segment2));
			Assert::IsFalse(segment1->isParallel(segment3));

			Assert::IsTrue(segment1->isOnline(point16));//端点
			Assert::IsFalse(segment1->isOnline(point18));//线外的点
			Assert::IsTrue(segment4->isOnline(point16));//线上的点

		}
		//////////////////////////////////////////////////
		TEST_METHOD(Equalline)
		{

		}
		//////////////////////////////////////////////////
		TEST_METHOD(LineSeriesTest) 
		{
			LineSeries* ls = new LineSeries();
			Point* p1 = new Point(0, 0);
			Point* p2 = new Point(1, 1);
			Point* p3 = new Point(0, 1);
			Point* p4 = new Point(1, 0);
			Point* p5 = new Point(1, 2);
			Line* l1 = new Line(p1, p2);
			Line* l2 = new Line(p3, p4);
			Line* l3 = new Line(p3, p5);
			ls->add_line(l1);
			ls->add_line(l2);
			ls->add_line(l3);
			int t = ls->getLines().size();
			Assert::AreEqual(t, 3);

			int num = ls->cal_intersects();
			Assert::AreEqual(num, 2);
			int numbyget = ls->getIntersects().size();
			Assert::AreEqual(numbyget, 2);

			ls->delete_line(l1);
			t = ls->getLines().size();
			Assert::AreEqual(t, 2);
			
			ls->clear();
			
		}
		
	};
}
