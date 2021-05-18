#pragma once
#include <QtWidgets>

#include "SerialWorker.h"

class SerialController : public QObject
{
	Q_OBJECT
public:
	SerialController(QWidget* parent = Q_NULLPTR);
	~SerialController();

	void connectSerial(const QString& portName);
signals:
	void newData(QString data);

	void operate(QString portName);

private:

	QThread* workerThread;
	SerialWorker* worker;
};
