#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BMPOtherEnd.h"

class BMPOtherEnd : public QMainWindow
{
	Q_OBJECT

public:
	BMPOtherEnd(QWidget *parent = Q_NULLPTR);
public slots:
	void loadFile(void);
signals:
	void sendPixmap(QPixmap);
private:
	Ui::BMPOtherEndClass ui;
};
