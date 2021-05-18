#include "SerialWorker.h"

SerialWorker::SerialWorker(QObject* parent /*= Q_NULLPTR*/)
{
}

void SerialWorker::getData(QString portName)
{
	QString result;

	m_portName = portName;

	serial = new QSerialPort(this);

	/*QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

	for (QSerialPortInfo element : ports) {
		//qDebug() << element.portName();
		if (element.portName() == m_portName) {
			serial->setPort(element);
			break;
		}
	}*/

	serial->setPortName(portName);

	if (!serial->open(QIODevice::ReadWrite)) {
		qDebug() << "Can't open " << serial->portName() << ", error code " << serial->error() << ", error string code " << serial->errorString();
		return;
	}

	while (true) {
		if (serial->waitForReadyRead(m_waitTimeout)) {
			QByteArray responseData = serial->readAll();
			while (serial->waitForReadyRead(10))
				responseData += serial->readAll();

			const QString response = QString::fromUtf8(responseData);
			if (response == "\r" || response == "\n")
			{
				emit resultReady(result);
				result = "";
			}
			else {
				result += response;
			}
			qDebug() << result;
		}
	}
}
