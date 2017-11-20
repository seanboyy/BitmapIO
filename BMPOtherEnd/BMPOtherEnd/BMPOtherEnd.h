#pragma once

#include <BMP_Handler.h>
#include <QtWidgets/QMainWindow>
#include "ui_BMPOtherEnd.h"

class BMPOtherEnd : public QMainWindow
{
	Q_OBJECT

public:
	BMPOtherEnd(QWidget *parent = Q_NULLPTR);
public slots:
	void loadFile(void);
	void saveFile(void);
	void read(void);
	void write(void);
signals:
	void sendPixmap(QPixmap);
private:
	Ui::BMPOtherEndClass ui;
	uchar* pixels;
	int width;
	int height;
};
