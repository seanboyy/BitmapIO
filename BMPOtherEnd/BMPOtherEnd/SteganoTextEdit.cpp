#include "SteganoTextEdit.hpp"

SteganoTextEdit::SteganoTextEdit(QWidget * parent) : QPlainTextEdit(parent) {
	setPlainText("");
	text = "";
}

void SteganoTextEdit::read(uchar* pixels, int* width, int* height) {
	char temp = 0;
	size_t arrSize = (*height * (*width * 3)) / 8;
	text = new char[arrSize];
	for (int i = 0; i < *height * (*width * 3); ++i) {
		temp |= ((pixels[i] & 0x01) << (7 - (i % 8)));
		if (i != 0 && (i + 1) % 8 == 0) {
			QRegExp regex("[\x20-\x7E]", Qt::CaseSensitive, QRegExp::RegExp);
			if (regex.indexIn(QString(temp)) == 0) text[((i + 1) / 8) - 1] = temp;
			else {
				text[((i + 1) / 8) - 1] = '\0';
				break;
			}
			temp = 0;
		}
	}
	setPlainText(text);
}

void SteganoTextEdit::write() {
	std::string temp = toPlainText().toStdString();
	text = new char[temp.size() + 1];
	std::copy(temp.begin(), temp.end(), text);
	text[temp.size()] = '\0';
	emit sendText(text);
}
