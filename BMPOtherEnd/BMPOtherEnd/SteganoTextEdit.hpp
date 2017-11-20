#pragma once
#include <QPlainTextEdit>

class SteganoTextEdit : public QPlainTextEdit {
	Q_OBJECT

public:
	SteganoTextEdit(QWidget * parent = Q_NULLPTR);
	~SteganoTextEdit();
public slots:
	void read(uchar*, int*, int*);
	void write(void);
signals:
	void sendText(char*);
private:
	char* text;
	int width;
	int height;
};
