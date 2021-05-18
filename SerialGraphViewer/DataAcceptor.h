#pragma once
#include <QtWidgets>
#include <QVector>
#include <QPair>

class DataAcceptor : public QObject
{
	Q_OBJECT
public:
	DataAcceptor(QWidget* parent = Q_NULLPTR);

public slots:
	void addData(QString data);

signals:

	void newData(QVector<QPair<double, double>> data);
private:
};
