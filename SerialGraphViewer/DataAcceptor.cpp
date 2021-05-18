#include "DataAcceptor.h"

DataAcceptor::DataAcceptor(QWidget* parent /*= Q_NULLPTR*/)
{
}

void DataAcceptor::addData(QString data)
{
	QStringList list = data.split(',');

	double Timestamp = list.first().toDouble();
	list.removeAt(0);
	QPair<double, double> temp;
	QVector<QPair<double, double>> queue;

	for (QString datastring : list)
	{
		temp.first = Timestamp;
		temp.second = datastring.toDouble();
		queue.push_back(temp);
	}

	emit newData(queue);
}