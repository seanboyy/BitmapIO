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

//load file
void BMPOtherEnd::loadFile() {
	//get the name of the file (absolute resource location) for loading
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Images (*.bmp)"));
	//if no filename was gotten, give up
	if (filename.isEmpty()) return;
	//push the pixmap to the label, so we can see it
	emit sendPixmap(QPixmap(filename));
	//load bmp data using previous dll
	pixels = BMP_Handler::loadBMP(filename.toStdString().c_str(), width, height);
}

//save file
void BMPOtherEnd::saveFile() {
	//get the name of the file (absolute resource location) for saving
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Images (*.bmp)"));
	//if no filename was gotten, give up
	if (filename.isEmpty()) return;
	//
	BMP_Handler::saveBMP(filename.toStdString().c_str(), pixels, width, height);
}

void BMPOtherEnd::read() {
	emit sendImageData(pixels, &width, &height);
}

void BMPOtherEnd::write(char* text) {
	if (text == nullptr) return;
	size_t arrSize = (height * (width * 3)) / 8;
	for (size_t i = 0; i < arrSize; ++i) {
		for (int j = 0; j < 8; ++j) {
			uchar temp = pixels[(i * 8) + j] & (((text[i] & (0x80 >> j)) >> (7 - j)) | 0xFE);
			temp = temp | (((text[i] & (0x80 >> j)) >> (7 - j)) & 0x01);
			pixels[(i * 8) + j] = temp;
		}
		if (text[i] == '\0') break;
	}
}