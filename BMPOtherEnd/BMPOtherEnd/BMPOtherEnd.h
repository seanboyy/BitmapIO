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
	//loading file
	void loadFile(void);
	//saving file
	void saveFile(void);
	//read hidden data
	void read(void);
	//write data to pixels
	void write(char*);
signals:
	//push pixmap
	void sendPixmap(QPixmap);
	//push image data
	void sendImageData(uchar*, int*, int*);
private:
	//the user interface object
	Ui::BMPOtherEndClass ui;
	//the pixel data
	uchar* pixels;
	//width of image
	int width;
	//height of image
	int height;
};
