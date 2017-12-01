//Sean Bamford
//COMP 322 Obj Oriented 'n' Adv Programming
//11/30/17
//implements the functions in the header
#include "BMPOtherEnd.h"
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

BMPOtherEnd::BMPOtherEnd(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
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
	//save bmp using previous dll
	BMP_Handler::saveBMP(filename.toStdString().c_str(), pixels, width, height);
}

//read data
void BMPOtherEnd::read() {
	//send image data signal
	emit sendImageData(pixels, &width, &height);
}

//write data
void BMPOtherEnd::write(char* text) {
	//if text is null, give up
	if (text == nullptr) return;
	//how many characters can be stored
	size_t arrSize = (height * (width * 3)) / 8;
	//loop over all possible areas
	for (size_t i = 0; i < arrSize; ++i) {
		//loop over bits in a character
		for (int j = 0; j < 8; ++j) {
			//grab jth bit (0x80 >> j) in ith (text[i]) character in array, move it down to the end >> (7 - j)
			//then do this: (pixels[pos] & 1111111(bit)) | 0000000(bit)
			//& sets 1 to 0 if needed
			//| sets 0 to 1 if needed
			//set the result
			pixels[(i * 8) + j] = (pixels[(i * 8) + j] & (((text[i] & (0x80 >> j)) >> (7 - j)) | 0xFE)) | (((text[i] & (0x80 >> j)) >> (7 - j)) & 0x01);
		}
		//stop at end of string
		if (text[i] == '\0') break;
	}
}