/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *plotWindow;
    QPushButton *threeYearsButton;
    QPushButton *twoYearsButton;
    QPushButton *sixMonthButton;
    QPushButton *threeMonthsButton;
    QPushButton *oneMonthButton;
    QPushButton *oneWeekButton;
    QPushButton *oneYearButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1023, 597);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        plotWindow = new QCustomPlot(centralWidget);
        plotWindow->setObjectName(QString::fromUtf8("plotWindow"));
        plotWindow->setGeometry(QRect(0, 0, 1021, 511));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotWindow->sizePolicy().hasHeightForWidth());
        plotWindow->setSizePolicy(sizePolicy);
        plotWindow->setMaximumSize(QSize(16777215, 16777215));
        plotWindow->setAutoFillBackground(false);
        threeYearsButton = new QPushButton(plotWindow);
        threeYearsButton->setObjectName(QString::fromUtf8("threeYearsButton"));
        threeYearsButton->setGeometry(QRect(20, 0, 41, 31));
        threeYearsButton->setAutoFillBackground(false);
        threeYearsButton->setCheckable(true);
        twoYearsButton = new QPushButton(plotWindow);
        twoYearsButton->setObjectName(QString::fromUtf8("twoYearsButton"));
        twoYearsButton->setGeometry(QRect(60, 0, 41, 31));
        twoYearsButton->setAutoFillBackground(false);
        twoYearsButton->setCheckable(true);
        sixMonthButton = new QPushButton(plotWindow);
        sixMonthButton->setObjectName(QString::fromUtf8("sixMonthButton"));
        sixMonthButton->setGeometry(QRect(140, 0, 41, 31));
        sixMonthButton->setAutoFillBackground(false);
        sixMonthButton->setCheckable(true);
        threeMonthsButton = new QPushButton(plotWindow);
        threeMonthsButton->setObjectName(QString::fromUtf8("threeMonthsButton"));
        threeMonthsButton->setGeometry(QRect(180, 0, 41, 31));
        threeMonthsButton->setAutoFillBackground(false);
        threeMonthsButton->setCheckable(true);
        oneMonthButton = new QPushButton(plotWindow);
        oneMonthButton->setObjectName(QString::fromUtf8("oneMonthButton"));
        oneMonthButton->setGeometry(QRect(220, 0, 41, 31));
        oneMonthButton->setAutoFillBackground(false);
        oneMonthButton->setCheckable(true);
        oneWeekButton = new QPushButton(plotWindow);
        oneWeekButton->setObjectName(QString::fromUtf8("oneWeekButton"));
        oneWeekButton->setGeometry(QRect(260, 0, 41, 31));
        oneWeekButton->setAutoFillBackground(false);
        oneWeekButton->setCheckable(true);
        oneYearButton = new QPushButton(plotWindow);
        oneYearButton->setObjectName(QString::fromUtf8("oneYearButton"));
        oneYearButton->setGeometry(QRect(100, 0, 41, 31));
        oneYearButton->setAutoFillBackground(false);
        oneYearButton->setCheckable(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1023, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(false);
        statusBar->setAutoFillBackground(false);
        statusBar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        threeYearsButton->setText(QApplication::translate("MainWindow", "3y", nullptr));
        twoYearsButton->setText(QApplication::translate("MainWindow", "2y", nullptr));
        sixMonthButton->setText(QApplication::translate("MainWindow", "6m", nullptr));
        threeMonthsButton->setText(QApplication::translate("MainWindow", "3m", nullptr));
        oneMonthButton->setText(QApplication::translate("MainWindow", "1m", nullptr));
        oneWeekButton->setText(QApplication::translate("MainWindow", "1w", nullptr));
        oneYearButton->setText(QApplication::translate("MainWindow", "1y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
