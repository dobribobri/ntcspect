/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *pushButtonOpenFolder;
    QPushButton *pushButtonParseFolder;
    QProgressBar *progressBar;
    QPushButton *pushButtonWriteToFile;
    QPushButton *p1;
    QPushButton *p2;
    QLabel *label;
    QSlider *horizontalSlider;
    QPushButton *pushButton_setBr;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1220, 655);
        MainWindow->setMinimumSize(QSize(1220, 655));
        MainWindow->setMaximumSize(QSize(1220, 655));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setGeometry(QRect(10, 1, 1024, 600));
        graphicsView->setMinimumSize(QSize(1024, 600));
        graphicsView->setMaximumSize(QSize(1920, 1080));
        pushButtonOpenFolder = new QPushButton(centralWidget);
        pushButtonOpenFolder->setObjectName(QStringLiteral("pushButtonOpenFolder"));
        pushButtonOpenFolder->setGeometry(QRect(1040, 10, 171, 25));
        pushButtonParseFolder = new QPushButton(centralWidget);
        pushButtonParseFolder->setObjectName(QStringLiteral("pushButtonParseFolder"));
        pushButtonParseFolder->setEnabled(false);
        pushButtonParseFolder->setGeometry(QRect(1040, 40, 171, 25));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(1040, 560, 171, 23));
        progressBar->setValue(0);
        pushButtonWriteToFile = new QPushButton(centralWidget);
        pushButtonWriteToFile->setObjectName(QStringLiteral("pushButtonWriteToFile"));
        pushButtonWriteToFile->setEnabled(false);
        pushButtonWriteToFile->setGeometry(QRect(1040, 190, 171, 25));
        p1 = new QPushButton(centralWidget);
        p1->setObjectName(QStringLiteral("p1"));
        p1->setEnabled(false);
        p1->setGeometry(QRect(1040, 160, 81, 25));
        p2 = new QPushButton(centralWidget);
        p2->setObjectName(QStringLiteral("p2"));
        p2->setEnabled(false);
        p2->setGeometry(QRect(1130, 160, 81, 25));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1100, 240, 67, 17));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setGeometry(QRect(1040, 80, 171, 16));
        horizontalSlider->setMaximum(8);
        horizontalSlider->setPageStep(2);
        horizontalSlider->setValue(3);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_setBr = new QPushButton(centralWidget);
        pushButton_setBr->setObjectName(QStringLiteral("pushButton_setBr"));
        pushButton_setBr->setEnabled(false);
        pushButton_setBr->setGeometry(QRect(1090, 100, 71, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1220, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\265 \320\276\320\272\320\275\320\276", Q_NULLPTR));
        pushButtonOpenFolder->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", Q_NULLPTR));
        pushButtonParseFolder->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214", Q_NULLPTR));
        pushButtonWriteToFile->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\262 \321\204\320\260\320\271\320\273", Q_NULLPTR));
        p1->setText(QApplication::translate("MainWindow", "\320\250\320\260\321\200\320\270\320\272", Q_NULLPTR));
        p2->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\260\320\262\320\260", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\276!", Q_NULLPTR));
        pushButton_setBr->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
