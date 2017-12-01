//Sean Bamford
//COMP 322 Obj Oriented 'n' Adv Programming
//11/30/17
//implements the functions in the header
#include "SteganoTextEdit.hpp"

//constructor bruh
SteganoTextEdit::SteganoTextEdit(QWidget * parent) : QPlainTextEdit(parent) {
	//shouldn't need this, but it's good to be safe
	setPlainText("");
	//initialize text
	text = "";
}

//read encoded data
void SteganoTextEdit::read(uchar* pixels, int* width, int* height) {
	//make a temp char for filling
	char temp = 0;
	//find max size the text can be (how many bytes can be hidden)
	size_t arrSize = (*height * (*width * 3)) / 8;
	//create a new string of the correct size
	text = new char[arrSize];
	//loop over the pixels
	for (int i = 0; i < *height * (*width * 3); ++i) {
		//grab the last bit of each pixel, and shove it into the temp char
		temp |= ((pixels[i] & 0x01) << (7 - (i % 8)));
		//if at the end of a character
		if (i != 0 && (i + 1) % 8 == 0) {
			//make a regex pattern for all characters typeable on a standard english keyboard
			QRegExp regex("[\x20-\x7E\n]", Qt::CaseSensitive, QRegExp::RegExp);
			//check if the character we made is one of th
			if (regex.indexIn(QString(temp)) == 0) text[((i + 1) / 8) - 1] = temp;
			else {
				//set any other character to null and stop
				text[((i + 1) / 8) - 1] = '\0';
				break;
			}
			//reset the temp char
			temp = 0;
		}
	}
	//show the text
	setPlainText(text);
}

void SteganoTextEdit::write() {
	//convert the text in the box to a char*
	std::string temp = toPlainText().toStdString();
	text = new char[temp.size() + 1];
	std::copy(temp.begin(), temp.end(), text);
	text[temp.size()] = '\0';
	//send the text out
	emit sendText(text);
}
