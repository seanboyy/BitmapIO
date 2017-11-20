#include "BMPOtherEnd.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

BMPOtherEnd::BMPOtherEnd(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void BMPOtherEnd::loadFile() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Images (*.bmp)"));
	if (filename.isEmpty()) return;
	emit sendPixmap(QPixmap(filename));
	pixels = BMP_Handler::loadBMP(filename.toStdString().c_str(), width, height);
}

void BMPOtherEnd::saveFile() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Images (*.bmp)"));
	if (filename.isEmpty()) return;
	BMP_Handler::saveBMP(filename.toStdString().c_str(), pixels, width, height);
}