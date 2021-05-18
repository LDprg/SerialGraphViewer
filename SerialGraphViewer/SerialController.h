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

public slots:
	void newPort(const QString &portname);

private:

	QThread* workerThread;
	SerialWorker* worker;
};
