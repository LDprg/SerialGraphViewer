#include "SerialGraphViewer.h"

SerialGraphViewer::SerialGraphViewer(QWidget* parent)
	: QMainWindow(parent)
{
	dataInterface = new DataAcceptor(this);
	graphInterface = new GraphDrawer(this);
	serialInterface = new SerialController(this);

	ui.setupUi(this);

	ui.cbCOM->addItem("COM1");
	ui.cbCOM->addItem("COM2");
	ui.cbCOM->addItem("COM3");
	ui.cbCOM->addItem("COM4");
	ui.cbCOM->addItem("COM5");
	ui.cbCOM->addItem("COM6");
	ui.cbCOM->addItem("COM7");
	ui.cbCOM->addItem("COM8");
	ui.cbCOM->addItem("COM9");
	ui.cbCOM->addItem("COM10");
	ui.cbCOM->addItem("COM11");
	ui.cbCOM->addItem("COM12");
	ui.cbCOM->addItem("COM13");
	ui.cbCOM->addItem("COM14");

	connect(ui.actionExit, &QAction::activate, this, &SerialGraphViewer::close);

	graphInterface->setPlot(ui.customPlot);
	graphInterface->setTracerLabel2(ui.lbCoords);

	connect(dataInterface, &DataAcceptor::newData, graphInterface, QOverload<QVector<QPair<double, double>>>::of(&GraphDrawer::addData));

	connect(ui.btResetView, &QPushButton::clicked, graphInterface, &GraphDrawer::resetView);

	connect(ui.btResetTracer, &QPushButton::clicked, graphInterface, &GraphDrawer::removeTracer);
	connect(ui.btResetTracer, &QPushButton::clicked, ui.lbCoords, &QLabel::clear);

	connect(serialInterface, &SerialController::newData, dataInterface, &DataAcceptor::addData);


	connect(ui.cbCOM, QOverload<const QString&>::of(&QComboBox::activated), serialInterface, &SerialController::newPort);

	//serialInterface->connectSerial("COM2");

	//graphInterface->demo();
	//dataInterface->addData("0,0,0,0");
	//dataInterface->addData("2,2,6,16");
	//dataInterface->addData("1,2,4,8");
	//dataInterface->addData("3,2,8,24");
}