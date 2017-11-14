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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BMPOtherEndClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *pictureLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BMPOtherEndClass)
    {
        if (BMPOtherEndClass->objectName().isEmpty())
            BMPOtherEndClass->setObjectName(QStringLiteral("BMPOtherEndClass"));
        BMPOtherEndClass->resize(593, 531);
        actionOpen = new QAction(BMPOtherEndClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(BMPOtherEndClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(BMPOtherEndClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pictureLabel = new QLabel(centralWidget);
        pictureLabel->setObjectName(QStringLiteral("pictureLabel"));
        pictureLabel->setGeometry(QRect(10, 10, 571, 321));
        pictureLabel->setFrameShape(QFrame::WinPanel);
        BMPOtherEndClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BMPOtherEndClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 593, 21));
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
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(BMPOtherEndClass);
        QObject::connect(actionExit, SIGNAL(triggered()), BMPOtherEndClass, SLOT(close()));
        QObject::connect(actionOpen, SIGNAL(triggered()), BMPOtherEndClass, SLOT(loadFile()));

        QMetaObject::connectSlotsByName(BMPOtherEndClass);
    } // setupUi

    void retranslateUi(QMainWindow *BMPOtherEndClass)
    {
        BMPOtherEndClass->setWindowTitle(QApplication::translate("BMPOtherEndClass", "BMPOtherEnd", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("BMPOtherEndClass", "Open...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("BMPOtherEndClass", "Exit", Q_NULLPTR));
        pictureLabel->setText(QString());
        menuFile->setTitle(QApplication::translate("BMPOtherEndClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BMPOtherEndClass: public Ui_BMPOtherEndClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BMPOTHEREND_H
