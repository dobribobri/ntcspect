#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QProgressBar>
#include "customscene.h"
#include "core.h"
#include "formlog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonOpenFolder_clicked();

    void on_pushButtonParseFolder_clicked();

    void on_pushButtonWriteToFile_clicked();

    void on_p1_clicked();

    void on_p2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_setBr_clicked();

private:
    Ui::MainWindow *ui;
    CustomScene* scene;
    Core* core;
    QString dir;
    QStringList flist;

public:
    FormLog* logform;
    QProgressBar* progressBar;
};

#endif // MAINWINDOW_H
