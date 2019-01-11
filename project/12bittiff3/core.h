#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QTextEdit>
#include <QProgressBar>
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <tiffio.h>
#include <math.h>
#include <fstream>
#include <sstream>

class Core : public QObject, public QGraphicsItem {
    Q_OBJECT
    public:
        explicit Core(QObject* parent = 0);
        ~Core();

    signals:

    public slots:
        void slot(QPointF point);

    private:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    private slots:

    private:
        std::string dtos(double i);

        QTextEdit* log;
        QProgressBar* progressBar;
        QPointF target;
        bool firstpoint = true;
        int area = 1;
        QPointF target0;
        QPen pen;

        int S[1024][1024];
        int currS[1024][1024];
        void rememberImage(TIFF* tiff);

        //QImage convertGray16TifToQImage(TIFF* tiff);
        QImage convert_S_ToGrayScaleQImage();

        //std::vector<QPointF> points;
        std::vector<QPointF> points_a1, points_a2;
        //bool belongsQ(QPointF point);
        //bool belongsQ(int x, int y);
        bool belongsQ_a1(QPointF point);
        bool belongsQ_a2(QPointF point);

        QImage saved;
        int brightness = 3;

        std::vector<double> v_lamda, v_avgI_a1, v_maxI_a1, v_minI_a1, v_avgI_a2, v_maxI_a2, v_minI_a2, v_I1, v_I2;

        bool paintingEnabled = false;


    public:
        //double avgI; double maxI; double minI;
        //void avgIntesityOnSelectedArea();
        //void drawGray16TIFFImage(QString _fullPathToTIFFImage);
        void pre_draw(QString _fullPathToFolder, QStringList _files);
        void re_draw();
        void setArea(int _zone);
        void draw(QString _fullPathToFolder, QStringList _files);
        //void drawPointsThatBelongs();

        void setLog(QTextEdit* _log);
        void setProgressBar(QProgressBar* _prgrsBar);
        void clearSelection();

        //void writeToFile(QString _fullPathToFile, QString _fullPathToFolder, QStringList _files);
        void writeToFile(QString _fullPathToFile);

        void draw_n_writeToFile(QString _fullPathToFolder, QStringList _files, QString _fullPathToFile);

        void setBrightness(int _br);

        void setPaintEnabled(bool _flag);
};

#endif
