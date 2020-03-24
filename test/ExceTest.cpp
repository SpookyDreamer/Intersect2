#include "pch.h"
#include "CppUnitTest.h"
#include "..//dealExp/Line.h"
#include "..//dealExp/lineSeries.h"
#include "..//dealExp/Point.h"
#include "..//dealExp/Line.cpp"
#include "..//dealExp/LineSeries.cpp"
#include "..//dealExp/Point.cpp"
#include "..//dealExp/Radial.cpp"
#include "..//dealExp/Segment.cpp"
#include "..///dealExp/MyException.h"

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
			Point* pp = segment1->intersect(segment3);
			
			Assert::IsTrue(pp->equals(point16));

			Assert::IsTrue(segment1->isParallel(segment2));
			Assert::IsFalse(segment1->isParallel(segment3));

			Assert::IsTrue(segment1->isOnline(point16));//端点
			Assert::IsFalse(segment1->isOnline(point18));//线外的点
			Assert::IsTrue(segment4->isOnline(point16));//线上的点
			Assert::IsTrue(segment3->isOnline(point16));//垂直x轴的线的判断

		}
		//////////////////////////////////////////////////
		TEST_METHOD(Equalline)
		{
			Point* point21 = new Point(0, 0);
			Point* point22 = new Point(1, 1);
			Point* point23 = new Point(-1, -1);
			Point* point24 = new Point(0, 1);
			Point* point25 = new Point(1, -1);
			Point* point26 = new Point(-1, 1);
			Point* point27 = new Point(0, -1);
			Point* point28 = new Point(1, 0);
			Point* point29 = new Point(-1, 0);
			Point* point30 = new Point(1, 2);
			Point* point31 = new Point(-2, -2);
			Line* line10 = new Line(point21, point22);
			Radial* radial10 = new Radial(point21, point22);
			Segment* segment10 = new Segment(point21, point22);
			Assert::IsFalse(line10->equals(radial10));// type
			Assert::IsFalse(line10->equals(segment10));
			Assert::IsFalse(radial10->equals(segment10));

			Line* line12 = new Line(point29, point24);
			Assert::IsFalse(line10->equals(line12));//parallel
			Line* line11 = new Line(point22, point23);
			Assert::IsTrue(line10->equals(line11));//

			Radial* radial11 = new Radial(point21, point24);
			Radial* radial12 = new Radial(point21, point27);
			Assert::IsFalse(radial11->equals(radial12));
			Assert::IsTrue(radial11->equals(radial11));

			Segment* segment11 = new Segment(point22, point23);
			Assert::IsTrue(segment11->equals(segment11));
			Assert::IsFalse(segment11->equals(segment10));

			//////////////////////
			Segment* segment12 = new Segment(point21, point22);
			Segment* segment13 = new Segment(point21, point23);
			Segment* segment14 = new Segment(point23, point31);
			Segment* segment15 = new Segment(point22, point21);
			Assert::AreEqual(radial10->countIntersectinOneLine(segment12), -1);
			Assert::AreEqual(radial10->countIntersectinOneLine(segment13), 1);
			Assert::AreEqual(radial10->countIntersectinOneLine(segment14), 0);
			Assert::AreEqual(radial10->countIntersectinOneLine(segment15), -1);

			Radial* radial13 = new Radial(point21, point22);
			Radial* radial14 = new Radial(point21, point23);
			Radial* radial15 = new Radial(point23, point31);
			Radial* radial16 = new Radial(point22, point21);
			Assert::AreEqual(radial10->countIntersectinOneLine(radial13), -1);
			Assert::AreEqual(radial10->countIntersectinOneLine(radial14), 1);
			Assert::AreEqual(radial10->countIntersectinOneLine(radial15), 0);
			Assert::AreEqual(radial10->countIntersectinOneLine(radial16), -1);


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

	
	TEST_CLASS(ExceptionTest) {
		TEST_METHOD(WF) {
			
		}

		TEST_METHOD(COOR) {
			Point* pe1 = new Point(0, 0);
			Point* pe2 = new Point(-100000, 0);
			Point* pe3 = new Point(0, -200000);
			try {
				Line* l1 = new Line(pe1, pe2);
				Assert::IsFalse(true);
			}
			catch (CoordinateOutOfRangeException& e) {
				Assert::AreEqual(e.what(), "ERROR! Both horizontal and vertical values should be within  (-100000, 100000).\n");
			}
			try {
				Line* l2 = new Line(pe1, pe3);
				Assert::IsFalse(true);
			}
			catch (CoordinateOutOfRangeException& e) {
				Assert::AreEqual(e.what(), "ERROR! Both horizontal and vertical values should be within  (-100000, 100000).\n");
			}
			
		}
		
		TEST_METHOD(UTC) {
			Point* pe4 = new Point(0, 0);
			try {
				Line* l3 = new Line(pe4, pe4);
				Assert::IsFalse(true);
			}
			catch (UnableToConstructException& e) {
				Assert::AreEqual(e.what(), "ERROR! Since the two points given coincide, we cannot construct a line.\n");
			}
		}

		TEST_METHOD(IIP) {
			LineSeries* ls0 = new LineSeries();
			Point* pe5 = new Point(0, 0);
			Point* pe6 = new Point(1, 1);
			Line* le1 = new Line(pe5, pe6);
			Radial* re1 = new Radial(pe5, pe6);
			Segment* se1 = new Segment(pe5, pe6);
			ls0->add_line(se1);
			try {
				ls0->add_line(le1);
				Assert::IsFalse(true);
			}
			catch (InfiniteIntersectionPointsException& e) {
				Assert::AreEqual(e.what(), "ERROR!There are infinite points of intersection between geometric objects .\n");
			}
			try {
				ls0->add_line(re1);
				Assert::IsFalse(true);
			}
			catch (InfiniteIntersectionPointsException& e) {
				Assert::AreEqual(e.what(), "ERROR!There are infinite points of intersection between geometric objects .\n");
			}
		}
	};
	
}
