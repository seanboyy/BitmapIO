/********************************************************************************
** Form generated from reading UI file 'BMPOtherEnd.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BMPOTHEREND_H
#define UI_BMPOTHEREND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "SteganoTextEdit.hpp"

QT_BEGIN_NAMESPACE

class Ui_BMPOtherEndClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionSave;
    QWidget *centralWidget;
    QLabel *pictureLabel;
    QPushButton *encode;
    QPushButton *decode;
    SteganoTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BMPOtherEndClass)
    {
        if (BMPOtherEndClass->objectName().isEmpty())
            BMPOtherEndClass->setObjectName(QStringLiteral("BMPOtherEndClass"));
        BMPOtherEndClass->resize(632, 587);
        actionOpen = new QAction(BMPOtherEndClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(BMPOtherEndClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(BMPOtherEndClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(BMPOtherEndClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pictureLabel = new QLabel(centralWidget);
        pictureLabel->setObjectName(QStringLiteral("pictureLabel"));
        pictureLabel->setGeometry(QRect(10, 10, 611, 371));
        pictureLabel->setFrameShape(QFrame::WinPanel);
        pictureLabel->setFrameShadow(QFrame::Sunken);
        pictureLabel->setScaledContents(true);
        encode = new QPushButton(centralWidget);
        encode->setObjectName(QStringLiteral("encode"));
        encode->setGeometry(QRect(510, 400, 111, 31));
        decode = new QPushButton(centralWidget);
        decode->setObjectName(QStringLiteral("decode"));
        decode->setGeometry(QRect(510, 490, 111, 31));
        plainTextEdit = new SteganoTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 390, 491, 141));
        plainTextEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        plainTextEdit->setFrameShadow(QFrame::Sunken);
        BMPOtherEndClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BMPOtherEndClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 632, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        BMPOtherEndClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BMPOtherEndClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BMPOtherEndClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BMPOtherEndClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BMPOtherEndClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(BMPOtherEndClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), BMPOtherEndClass, SLOT(loadFile()));
        QObject::connect(actionSave, SIGNAL(triggered()), BMPOtherEndClass, SLOT(saveFile()));
        QObject::connect(actionExit, SIGNAL(triggered()), BMPOtherEndClass, SLOT(close()));
        QObject::connect(BMPOtherEndClass, SIGNAL(sendPixmap(QPixmap)), pictureLabel, SLOT(setPixmap(QPixmap)));
        QObject::connect(BMPOtherEndClass, SIGNAL(sendImageData(uchar*,int*,int*)), plainTextEdit, SLOT(read(uchar*,int*,int*)));
        QObject::connect(decode, SIGNAL(clicked()), BMPOtherEndClass, SLOT(read()));
        QObject::connect(plainTextEdit, SIGNAL(sendText(char*)), BMPOtherEndClass, SLOT(write(char*)));
        QObject::connect(encode, SIGNAL(clicked()), plainTextEdit, SLOT(write()));

        QMetaObject::connectSlotsByName(BMPOtherEndClass);
    } // setupUi

    void retranslateUi(QMainWindow *BMPOtherEndClass)
    {
        BMPOtherEndClass->setWindowTitle(QApplication::translate("BMPOtherEndClass", "BMPOtherEnd", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("BMPOtherEndClass", "Open...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("BMPOtherEndClass", "Exit", Q_NULLPTR));
        actionSave->setText(QApplication::translate("BMPOtherEndClass", "Save...", Q_NULLPTR));
        pictureLabel->setText(QString());
        encode->setText(QApplication::translate("BMPOtherEndClass", "Encode", Q_NULLPTR));
        decode->setText(QApplication::translate("BMPOtherEndClass", "Decode", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("BMPOtherEndClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BMPOtherEndClass: public Ui_BMPOtherEndClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BMPOTHEREND_H
