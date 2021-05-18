#pragma once

#include <QtWidgets>

#include "qcustomplot.h"

class GraphDrawer : public QObject
{
	Q_OBJECT
public:
	GraphDrawer(QWidget* parent = Q_NULLPTR);
	void demo();

	void setData(int graph, QVector<double> x, QVector<double> y);

	void addData(int graph, double x, double y);

	void setPlot(QCustomPlot* plot);

	void setRangeX(double lower, double upper);
	void setRangeY(double lower, double upper);

	void setLabelX(QString label);
	void setLabelY(QString label);

	void rescaleAxis();

	double getYfromX(int graph, double x);

	void setUpdateTime(int timems);
	int getUpdateTime();

	void showTracer(bool show);
	void setTracerLabel2(QLabel* label);

	void replot();

public slots:
	void showPointToolTip(QMouseEvent* event);
	void resetView();
	void removeTracer();

	void addData(QVector<QPair<double, double>> data);

signals:
	void redraw();

private:
	int index;
	const QColor Colors[7] = {
		QColorConstants::Blue,
		QColorConstants::Red,
		QColorConstants::Green,
		QColorConstants::Yellow,
		QColorConstants::Cyan,
		QColorConstants::Magenta,
		QColorConstants::Black
	};

	QCustomPlot* plot;
	QLabel* label;
	QLabel* label2;

	QCPItemTracer* tracer;

	int updateTime;
	QTimer* timer;

	QCPGraph* getGraph(int graph);

	void setLabel2(QString text);
};
