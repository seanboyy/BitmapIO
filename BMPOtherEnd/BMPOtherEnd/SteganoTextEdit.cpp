#include "SteganoTextEdit.hpp"

SteganoTextEdit::SteganoTextEdit(QWidget * parent) : QPlainTextEdit(parent) {
	setPlainText("");
}

SteganoTextEdit::~SteganoTextEdit() {
	delete[] text;
}

void SteganoTextEdit::read(uchar* pixels, int* width, int* height) {
	char temp = 0;
	size_t arrSize = (*height * (*width * 3)) / 8;
	text = new char[arrSize];
	for (int i = 0; i < *height * (*width * 3); ++i) {
		temp |= ((pixels[i] & 0x01) << (7 - (i % 8)));
		if (i != 0 && i % 8 == 0) {
			QRegExp regex("[\x20-\x7E]", Qt::CaseSensitive, QRegExp::RegExp);
			if (regex.indexIn(QString(temp)) == 0) text[(i / 8) - 1] = temp;
			else text[(i / 8) - 1] = '\0';
		}
	}
	setPlainText(text);
}

void SteganoTextEdit::write() {
	emit sendText(text);
}
