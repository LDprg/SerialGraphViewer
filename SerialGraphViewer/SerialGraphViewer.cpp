#include "SerialGraphViewer.h"

SerialGraphViewer::SerialGraphViewer(QWidget* parent)
	: QMainWindow(parent)
{
	dataInterface = new DataAcceptor();
	graphInterface = new GraphDrawer();
	serialInterface = new SerialController();

	ui.setupUi(this);

	connect(ui.actionExit, &QAction::activate, this, &SerialGraphViewer::close);

	graphInterface->setPlot(ui.customPlot);
	graphInterface->setTracerLabel2(ui.lbCoords);

	connect(dataInterface, &DataAcceptor::newData, graphInterface, QOverload<QVector<QPair<double, double>>>::of(&GraphDrawer::addData));

	connect(ui.btResetView, &QPushButton::clicked, graphInterface, &GraphDrawer::resetView);

	connect(ui.btResetTracer, &QPushButton::clicked, graphInterface, &GraphDrawer::removeTracer);
	connect(ui.btResetTracer, &QPushButton::clicked, ui.lbCoords, &QLabel::clear);

	connect(serialInterface, &SerialController::newData, dataInterface, &DataAcceptor::addData);

	serialInterface->connectSerial("COM2");

	//graphInterface->demo();
	//dataInterface->addData("0,0,0,0");
	//dataInterface->addData("2,2,6,16");
	//dataInterface->addData("1,2,4,8");
	//dataInterface->addData("3,2,8,24");
}