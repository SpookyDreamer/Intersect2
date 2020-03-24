#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include "lineSeries.h"
#include <qguiapplication.h>
#include <qpushbutton.h>
#include <string.h>
#include "qcustomplot.h"
#include <qpainter.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Line.h"
#include "Point.h"
#include <unordered_set>
#include "Myexception.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFile>
#include <QVector>
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QTextEdit>
#include <QPixmap>

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);

private:

	LineSeries* ls = new LineSeries();

	Ui::QtGuiApplication1Class ui;

private slots:

	void init();

	void addLine();

	void deleteLine();

	void calculate();

	void readFile();

	void paintLine();

	//Line* getInput(char* str);
};
