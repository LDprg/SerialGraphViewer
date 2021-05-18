#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SerialGraphViewer.h"

#include <QPushButton>

#include "DataAcceptor.h"
#include "GraphDrawer.h"
#include "SerialController.h"

class SerialGraphViewer : public QMainWindow
{
	Q_OBJECT

public:
	SerialGraphViewer(QWidget* parent = Q_NULLPTR);

private:
	Ui::SerialGraphViewerClass ui;
	DataAcceptor* dataInterface;
	GraphDrawer* graphInterface;
	SerialController* serialInterface;
};
