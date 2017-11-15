#include "BMPOtherEnd.h"
#include <QFileDialog>
#include <QString>

BMPOtherEnd::BMPOtherEnd(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void BMPOtherEnd::loadFile() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Images (*.bmp)"));

	emit sendPixmap(QPixmap(filename));
}

void BMPOtherEnd::saveFile() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Images (*.bmp)"));
}