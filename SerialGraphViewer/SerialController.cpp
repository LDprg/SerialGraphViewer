#include "SerialController.h"

SerialController::SerialController(QWidget* parent /*= Q_NULLPTR*/)
{
	worker = new SerialWorker(this);
	workerThread = new QThread(this);

	worker->moveToThread(workerThread);

	connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &SerialController::operate, worker, &SerialWorker::getData);
	connect(worker, &SerialWorker::resultReady, this, &SerialController::newData);
	workerThread->start();
}

SerialController::~SerialController()
{
	workerThread->terminate();
	workerThread->wait();
}

void SerialController::connectSerial(const QString& portName)
{
	emit operate(portName);
}

void SerialController::newPort(const QString& portname)
{
	workerThread->terminate();
	workerThread->wait();
	workerThread->start();

	connectSerial(portname);
}
