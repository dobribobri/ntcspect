#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new CustomScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QCursor cursor = QCursor(Qt::PointingHandCursor);
    ui->graphicsView->setCursor(cursor);

    core = new Core();
    scene->addItem(core);

    ui->graphicsView->setMouseTracking(true);

    connect(scene, &CustomScene::signalTargetCoordinate, core, &Core::slot);

    logform = new FormLog();
    logform->show();
    core->setLog(logform->textEdit);

    progressBar = ui->progressBar;
    core->setProgressBar(progressBar);
    ui->label->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOpenFolder_clicked()
{
    dir = QFileDialog::getExistingDirectory(this, tr("Выберите папку"),
                                                QDir::currentPath(),
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if (dir == "") return;
    dir += '/';
    QDir datdir(dir);
    datdir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    flist = datdir.entryList();
    ui->pushButtonOpenFolder->setDisabled(true);
    ui->pushButtonParseFolder->setEnabled(true);
}

void MainWindow::on_pushButtonParseFolder_clicked()
{
    QString f = flist.first();
    /*Для одного файла*/
    //core->drawGray16TIFFImage(dir+f);
    /*Для всей папки*/
    core->pre_draw(dir, flist);
    ui->pushButtonParseFolder->setDisabled(true);
    core->setArea(1);
    ui->horizontalSlider->setEnabled(true);
    ui->pushButton_setBr->setEnabled(true);

    core->setPaintEnabled(false);
    ui->graphicsView->setEnabled(true);
}

void MainWindow::on_pushButtonWriteToFile_clicked()
{
    ui->pushButtonWriteToFile->setDisabled(true);
    QString where_path = QFileDialog::getSaveFileName(this,
                                                      tr("Куда сохранить?"),
                                                      dir);
    if (where_path == "") return;
    this->show();
    core->draw_n_writeToFile(dir, flist, where_path);
    ui->label->setVisible(true);
}

void MainWindow::on_p1_clicked()
{
    core->setArea(2);
    core->clearSelection();
    ui->p2->setEnabled(true);
    ui->p1->setPalette(QPalette(QColor(Qt::green)));
    ui->p1->setDisabled(true);
    ui->p2->setPalette(QPalette(QColor(Qt::yellow)));
}

void MainWindow::on_p2_clicked()
{
    ui->p2->setPalette(QPalette(QColor(Qt::green)));
    ui->p2->setDisabled(true);
    core->clearSelection();
    ui->pushButtonWriteToFile->setEnabled(true);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    core->setBrightness(value);
    core->re_draw();
}

void MainWindow::on_pushButton_setBr_clicked()
{
    core->setPaintEnabled(true);
    ui->pushButton_setBr->setDisabled(true);
    ui->horizontalSlider->setDisabled(true);
    ui->p1->setEnabled(true);
    ui->p1->setPalette(QPalette(QColor(Qt::yellow)));
}
