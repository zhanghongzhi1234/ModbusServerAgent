#include "RTDUTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RTDUTest w;
	w.show();
	return a.exec();
}
