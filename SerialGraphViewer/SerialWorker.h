#pragma once
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialWorker : public QObject
{
	Q_OBJECT
public:
	SerialWorker(QObject* parent = Q_NULLPTR);

public slots:
	void getData(QString portName);

signals:
	void response(const QString& s);
	void error(const QString& s);
	void timeout(const QString& s);

	void resultReady(QString result);

private:
	QString m_portName;
	int m_waitTimeout = 0;

	QSerialPort *serial;
};
