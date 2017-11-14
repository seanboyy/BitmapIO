#include "BMPOtherEnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BMPOtherEnd w;
	w.show();
	return a.exec();
}
