#pragma once

#include <BMP_Handler.h>
#include <QPlainTextEdit>
#include <QtWidgets/QMainWindow>
#include "ui_BMPOtherEnd.h"

class BMPOtherEnd : public QMainWindow
{
	Q_OBJECT

public:
	BMPOtherEnd(QWidget *parent = Q_NULLPTR);
	~BMPOtherEnd();
public slots:
	void loadFile(void);
	void saveFile(void);
	void read(void);
	void write(char*);
signals:
	void sendPixmap(QPixmap);
	void sendImageData(uchar*, int*, int*);
private:
	QPlainTextEdit textBox;
	Ui::BMPOtherEndClass ui;
	uchar* pixels;
	int width;
	int height;
};
