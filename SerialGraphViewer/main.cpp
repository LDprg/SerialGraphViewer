#include "SerialGraphViewer.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	SerialGraphViewer w;
	w.show();
	return a.exec();
}