#include "QtGuiApplication1.h"
#include <qstring.h>
#include <qfile.h>
#include <ui_QtGuiApplication1.h>
#include <AclUI.h>

QtGuiApplication1::QtGuiApplication1(QWidget* parent):
	QMainWindow(parent)
	//ui(new Ui::QtGuiApplication1Class)
{
	ui.setupUi(this);
	connect(ui.btnInit, SIGNAL(clicked(bool)), this, SLOT(init()));
	connect(ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(addLine()));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(deleteLine()));
	connect(ui.btnCalculate, SIGNAL(clicked(bool)), this, SLOT(calculate()));
	connect(ui.btnFile, SIGNAL(clicked(bool)), this, SLOT(readFile()));
	connect(ui.btnPaint, SIGNAL(clicked(bool)), this, SLOT(paintLine()));
	//QObject::connect(ui.lineInput, SIGNAL());
	//QObject::connect(this,SIGNAL(calculate()),ui.lineOutput,SLOT(show()));
	//Point* point1 = new Point(0, 0);
	//Point* point2 = new Point(1, 1);
	//Line* line = new Segment(point1, point2);
	//ls->add_line(line);
	//paintLine();
}

void QtGuiApplication1::init()
{
	ls->clear();
	paintLine();
	calculate();
}

void QtGuiApplication1::addLine()
{
	QString str = ui.text->toPlainText();//读取textedit中的内容
	QStringList list = str.split(" ");//用空格将读取到的字符串分割

	double x1 = list.at(1).toDouble();
	double y1 = list.at(2).toDouble();
	double x2 = list.at(3).toDouble();
	double y2 = list.at(4).toDouble();
	Point* point1 = new Point(x1, y1);
	Point* point2 = new Point(x2, y2);//创建Point类对象
	
	//分类讨论直线类型，创建相应的对象，并将其加入到容器中
	if (QString::compare(list.at(0), "L") == 0) {
		Line* line = new Line(point1, point2);
		ls->add_line(line);
	}
	else if (QString::compare(list.at(0), "S") == 0) {
		Line* line = new Segment(point1, point2);
		ls->add_line(line);
	}
	else if (QString::compare(list.at(0), "R") == 0) {
		Line* line = new Radial(point1, point2);
		ls->add_line(line);
	}
	//更新calculate和paint的结果
	calculate();
	paintLine();
}

void QtGuiApplication1::deleteLine()
{
	//ls->delete_line(line);
	QString str = ui.text->toPlainText();
	QStringList list = str.split(" ");

	double x1 = list.at(1).toDouble();
	double y1 = list.at(2).toDouble();
	double x2 = list.at(3).toDouble();
	double y2 = list.at(4).toDouble();
	Point* point1 = new Point(x1, y1);
	Point* point2 = new Point(x2, y2);

	if (QString::compare(list.at(0), "L") == 0) {
		Line* line = new Line(point1, point2);
		ls->delete_line(line);
	}
	else if (QString::compare(list.at(0), "S") == 0) {
		Line* line = new Segment(point1, point2);
		ls->delete_line(line);
	}
	else if (QString::compare(list.at(0), "R") == 0) {
		Line* line = new Radial(point1, point2);
		ls->delete_line(line);
	}
	calculate();
	paintLine();
}

void QtGuiApplication1::calculate()
{
	int res = ls->cal_intersects();
	std::stringstream ssTemp;
	ssTemp << res;
	std::string strDst = ssTemp.str();
	QString str = QString::fromStdString(strDst);
	ui.intersectNum->setText(str);
}

void QtGuiApplication1::readFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("打开文件"), ".", tr("文件类型(*.txt)"));
	QFile file(filename);
	QVector<double> array;
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Error" << endl;
	}

	QString res = file.readLine();    // 读第一行

	QByteArray t;
	while (!file.atEnd())
	{
		QString str = file.readLine();
		t += str;

		str.remove("\r\n");
		QStringList list = str.split(" ");

		double x1 = list.at(1).toDouble();
		double y1 = list.at(2).toDouble();
		double x2 = list.at(3).toDouble();
		double y2 = list.at(4).toDouble();
		Point* point1 = new Point(x1, y1);
		Point* point2 = new Point(x2, y2);

		if (QString::compare(list.at(0), "L") == 0) {
			Line* line = new Line(point1, point2);
			ls->add_line(line);
		}
		else if (QString::compare(list.at(0), "S") == 0) {
			Line* line = new Segment(point1, point2);
			ls->add_line(line);
		}
		else if (QString::compare(list.at(0), "R") == 0) {
			Line* line = new Radial(point1, point2);
			ls->add_line(line);
		}
	}

	ui.label->setText(QString(t));

	file.close();
}

void QtGuiApplication1::paintLine()
{
	std::vector<Line*> lines= ls->getLines();
	QCustomPlot* customPlot = ui.customPlot;
	customPlot->clearItems();
	customPlot->clearGraphs();
	ui.customPlot->addGraph();
	ui.customPlot->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
	ui.customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	ui.customPlot->axisRect()->setupFullAxesBox();
	ui.customPlot->rescaleAxes();
	ui.customPlot->xAxis->setRange(-5, 5);
	ui.customPlot->yAxis->setRange(-5, 5);

	int i;
	for (i = 0; i < lines.size(); i++) {
		Point* point1 = lines[i]->getPoint1();
		Point* point2 = lines[i]->getPoint2();
		double x1 = point1->getX();
		double y1 = point1->getY();
		double x2 = point2->getX();
		double y2 = point2->getY();
		if (lines[i]->getType() == 'L') {
			QCPItemStraightLine* line = new QCPItemStraightLine(customPlot);
			line->point1->setCoords(x1, y1);
			line->point2->setCoords(x2, y2);
		}
		else if (lines[i]->getType() == 'R') {
			QCPItemLine* line = new QCPItemLine(customPlot);
			line->start->setCoords(x1, y1);
			line->end->setCoords(x2 * 5000 - x1 * 4999, y2 * 5000 - y1 * 4999);
		}
		else if (lines[i]->getType() == 'S') {
			QCPItemLine* line = new QCPItemLine(customPlot);
			line->start->setCoords(x1, y1);
			line->end->setCoords(x2, y2);
		}
	}

	customPlot->replot();
	customPlot->show();
}


