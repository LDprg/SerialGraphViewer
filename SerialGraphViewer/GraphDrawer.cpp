#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(QWidget* parent /*= Q_NULLPTR*/)
	:plot(nullptr),
	label(nullptr),
	label2(nullptr),
	tracer(nullptr),
	updateTime(40),
	timer(nullptr),
	index(0)
{
}

void GraphDrawer::demo()
{
	for (int i = 0; i < 101; ++i)
	{
		double x = i / 50.0 - 1; // x goes from -1 to 1
		addData(0, x, x * x);
	}

	rescaleAxis();
	replot();
}

void GraphDrawer::setData(int graph, QVector<double> x, QVector<double> y)
{
	getGraph(graph)->setData(x, y);
}

void GraphDrawer::addData(int graph, double x, double y)
{
	getGraph(graph)->addData(x, y);
}

void GraphDrawer::addData(QVector<QPair<double, double>> data)
{
	int i = 0;
	for (QPair<double, double> item : data)
	{
		addData(i, item.first, item.second);
		++i;
	}
	resetView();
	replot();
}

void GraphDrawer::setPlot(QCustomPlot* plot)
{
	this->plot = plot;
	this->tracer = new QCPItemTracer(plot);
	this->label = new QLabel(plot);
	this->timer = new QTimer(this);

	connect(this->plot, &QCustomPlot::mouseMove, this, &GraphDrawer::showPointToolTip);

	connect(timer, &QTimer::timeout, this, QOverload<>::of(&GraphDrawer::redraw));
	timer->start(updateTime);

	plot->setInteraction(QCP::iRangeDrag, true);
	plot->setInteraction(QCP::iRangeZoom, true);
	plot->setInteraction(QCP::iSelectPlottables, true);

	showTracer(false);
	label->setVisible(false);

	setLabelX("x");
	setLabelY("y");
}

void GraphDrawer::setRangeX(double lower, double upper)
{
	plot->xAxis->setRange(lower, upper);
}

void GraphDrawer::setRangeY(double lower, double upper)
{
	plot->yAxis->setRange(lower, upper);
}

void GraphDrawer::setLabelX(QString label)
{
	plot->xAxis->setLabel(label);
}

void GraphDrawer::setLabelY(QString label)
{
	plot->yAxis->setLabel(label);
}

void GraphDrawer::rescaleAxis()
{
	plot->rescaleAxes();
}

double GraphDrawer::getYfromX(int graph, double x)
{
	tracer->setGraph(plot->graph(graph));
	tracer->setGraphKey(x);
	return tracer->position->value();
}

void GraphDrawer::setUpdateTime(int timems)
{
	updateTime = timems;
}

int GraphDrawer::getUpdateTime()
{
	return updateTime;
}

void GraphDrawer::showTracer(bool show)
{
	if (tracer->visible() != show)
	{
		tracer->setVisible(show);
		replot();
	}
}

void GraphDrawer::setTracerLabel2(QLabel* label)
{
	label2 = label;
}

void GraphDrawer::replot()
{
	plot->replot();
}

void GraphDrawer::showPointToolTip(QMouseEvent* event)
{
	int x = plot->xAxis->pixelToCoord(event->pos().x());
	int y = plot->yAxis->pixelToCoord(event->pos().y());

	if (plot->selectedGraphs().count() > 0)
	{
		QCPGraph* graph = plot->selectedGraphs().first();

		double dbottom = graph->valueAxis()->range().lower;        //Yaxis bottom value
		double dtop = graph->valueAxis()->range().upper;           //Yaxis top value
		long ptop = graph->valueAxis()->axisRect()->top();         //graph top margin
		long pbottom = graph->valueAxis()->axisRect()->bottom();   //graph bottom position

		//or shortly for X-axis
		double valueX = (event->pos().x() - (double)graph->keyAxis()->axisRect()->left());  //graph width in pixels
		double ratio = (double)(graph->keyAxis()->axisRect()->right() - (double)graph->keyAxis()->axisRect()->left()) / (double)(graph->keyAxis()->range().lower - graph->keyAxis()->range().upper);    //ratio px->graph width
		//and result for X-axis
		valueX = -valueX / ratio + graph->keyAxis()->range().lower;

		QVector<double> x(1), y(1);

		tracer->setGraph(graph);
		tracer->setGraphKey(valueX);

		x[0] = tracer->position->key();
		y[0] = tracer->position->value();

		QString message = QString("%1 , %2").arg(x[0]).arg(y[0]);

		QPoint point = graph->coordsToPixels(x[0], y[0]).toPoint();
		point += {10, -25};

		label->move(point);
		label->setText(message);
		label->adjustSize();

		setLabel2(message);

		showTracer(true);
		label->setVisible(true);

		plot->replot();
	}
	else
	{
		label->setVisible(false);
	}
}

void GraphDrawer::resetView()
{
	rescaleAxis();
	replot();
}

void GraphDrawer::removeTracer()
{
	showTracer(false);
}

QCPGraph* GraphDrawer::getGraph(int graph)
{
	for (; graph >= plot->graphCount();)
	{
		plot->addGraph();
	}

	return plot->graph(graph);
}

void GraphDrawer::setLabel2(QString text)
{
	if (label2) {
		label2->setText(text);
	}
}