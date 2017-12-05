#pragma once
#include <QPlainTextEdit>
#include <sstream>

class SteganoTextEdit : public QPlainTextEdit {
	Q_OBJECT

public:
	SteganoTextEdit(QWidget * parent = Q_NULLPTR);
public slots:
	void read(uchar*, int*, int*);
	void write(void);
	void doTheStuff();
signals:
	void sendText(char*);
	void sendCharCount(QString);
private:
	char* text = nullptr;
	uchar* pixels = nullptr;
	int charCount;
	int charUse;
	int height;
	int width;
};
