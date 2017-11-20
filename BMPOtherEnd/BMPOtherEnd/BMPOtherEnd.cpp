#include "BMPOtherEnd.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

BMPOtherEnd::BMPOtherEnd(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
}

BMPOtherEnd::~BMPOtherEnd() {
	delete[] pixels;
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

void BMPOtherEnd::read() {
	emit sendImageData(pixels, &width, &height);
}

void BMPOtherEnd::write(char* text) {
	size_t arrSize = (height * (width * 3)) / 8;
	for (size_t i = 0; i < arrSize; ++i) {
		for (int j = 0; j < 8; ++j) {
			pixels[i + j] &= ((text[i] & (0x80 >> j)) >> (7 - j));
		}
	}
}