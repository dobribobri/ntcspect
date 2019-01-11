#include "core.h"
#include "mainwindow.h"
#include "formlog.h"

Core::Core(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    memset(S, 0, sizeof(S));
    memset(currS, 0, sizeof(currS));
    target = QPointF(0,0);
    pen.setColor(Qt::red);
}

Core::~Core() {

}

std::string Core::dtos(double i) {
    std::stringstream s;
    s << i;
    return s.str();
}

void Core::slot(QPointF point) {
    if (this->paintingEnabled == false) return;
    target = point;
    qDebug() << target.x() << " " << target.y();
    log->append("x = " + QString::number(target.x()) + "  y = " + QString::number(target.y()));
    this->setPos(target);
    QPolygon polygon;
    polygon << QPoint(target.x()-3,target.y()-3) << QPoint(target.x()-3,target.y()+6)
            << QPoint(target.x()+6,target.y()-3) << QPoint(target.x()+6,target.y()+6);
    QGraphicsScene* sc = this->scene();
    sc->addPolygon(polygon, pen);
    if (firstpoint) {
        target0 = target;
        firstpoint = false;
        log->append("====================");
    } else {
        QGraphicsLineItem* line = new QGraphicsLineItem(target0.x(), target0.y(), target.x(), target.y());
        line->setPen(pen);
        sc->addItem(line);
        target0 = target;
    }
    if (area == 1) this->points_a1.push_back(target);
    if (area == 2) this->points_a2.push_back(target);
    //this->points.push_back(target);
}

void Core::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    /*
    QPolygon polygon;
    polygon << QPoint(0,0) << QPoint(0,6) << QPoint(6,0) << QPoint(6,6);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    */
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Core::boundingRect() const {
    return QRectF(0,0,1024,1024);
}

/*
bool Core::belongsQ(QPointF point) {
    bool result = false;
    int size = this->points.size();
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        if ( (points[i].y() < point.y() && points[j].y() >= point.y() || points[j].y() < point.y() && points[i].y() >= point.y()) &&
             (points[i].x() + (point.y() - points[i].y()) / (points[j].y() - points[i].y()) * (points[j].x() - points[i].x()) < point.x()) )
            result = !result;
        j = i;
    }
    return result;
}
*/

void Core::setArea(int _zone) {
    this->area = _zone;
    return;
}

bool Core::belongsQ_a1(QPointF point) {
    QApplication::processEvents();
    bool result = false;
    int size = this->points_a1.size();
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        if ( (points_a1[i].y() < point.y() && points_a1[j].y() >= point.y() || points_a1[j].y() < point.y() && points_a1[i].y() >= point.y()) &&
             (points_a1[i].x() + (point.y() - points_a1[i].y()) / (points_a1[j].y() - points_a1[i].y()) * (points_a1[j].x() - points_a1[i].x()) < point.x()) )
            result = !result;
        j = i;
    }
    return result;
}

bool Core::belongsQ_a2(QPointF point) {
    QApplication::processEvents();
    bool result = false;
    int size = this->points_a2.size();
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        if ( (points_a2[i].y() < point.y() && points_a2[j].y() >= point.y() || points_a2[j].y() < point.y() && points_a2[i].y() >= point.y()) &&
             (points_a2[i].x() + (point.y() - points_a2[i].y()) / (points_a2[j].y() - points_a2[i].y()) * (points_a2[j].x() - points_a2[i].x()) < point.x()) )
            result = !result;
        j = i;
    }
    return result;
}

/*
bool Core::belongsQ(int x, int y) {
    QPointF* point = new QPointF(x, y);
    return this->belongsQ(*point);
}
*/

/*
void Core::drawPointsThatBelongs() {
    QGraphicsScene* sc = this->scene();
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            QPointF point(j, i);
            if (belongsQ(j, i)) {
                QPolygon polygon;
                polygon << QPoint(point.x()-3,point.y()-3) << QPoint(point.x()+6,point.y()-3)
                        << QPoint(point.x()-3,point.y()+6) << QPoint(point.x()+6,point.y()+6);
                sc->addPolygon(polygon, pen);
            }
        }
    }
}
*/

/*
void Core::avgIntesityOnSelectedArea() {
    if (this->points.size() == 0) {
        qDebug() << "Область не выбрана!";
        log->append("Область не выбрана!");
        return;
    }
    int pointCount = 0;
    avgI = 0.;
    maxI = 0., minI = pow(2,12);
    for (int h = 0; h < 1024; h++) {
        for (int w = 0; w < 1024; w++) {
            if (belongsQ(w, h)) {
                avgI += (double)S[h][w];
                if ((double)S[h][w] > maxI) maxI = (double)S[h][w];
                if ((double)S[h][w] < minI) minI = (double)S[h][w];
                pointCount++;
            }
        }
    }
    avgI /= pointCount;
    qDebug() << "[На выделенной области] Средняя интенсивность: " << avgI;
    log->append("[На выделенной области] Средняя интенсивность: " + QString::number(avgI));
    qDebug() << "[На выделенной области] Макс. интенсивность: " << maxI;
    log->append("[На выделенной области] Макс. интенсивность: " + QString::number(maxI));
    qDebug() << "[На выделенной области] Мин. интенсивность: " << minI;
    log->append("[На выделенной области] Мин. интенсивность: " + QString::number(minI));
    return;
}
*/

/*
void Core::drawGray16TIFFImage(QString _fullPathToTIFFImage) {
    std::string path = _fullPathToTIFFImage.toStdString();
    TIFF* tiff = TIFFOpen(path.c_str(), "r");
    QImage qimg = convertGray16TifToQImage(tiff);
    QPixmap pixmap;
    pixmap = pixmap.fromImage(qimg);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap);
    saved = qimg;
    return;
}
*/

/*
void Core::writeToFile(QString _fullPathToFile, QString _fullPathToFolder, QStringList _files) {
    std::string fname = _fullPathToFile.toStdString();
    std::ofstream fout;
    fout.open(fname);
    std::string folder = _fullPathToFolder.toStdString();
    int k = 0;
    for (QString file : _files) {
        qDebug() << "Обработка: " << file << "...";
        log->append("Обработка: " + file + "...");
        for (int i = 0; i < 1024; i++) {
            for (int j = 0; j < 1024; j++) {
                S[i][j] = 0;
            }
        }
        std::string s = file.toStdString();
        if (s.substr(s.length() - 4, 4) != "tiff") {
            qDebug() << "Не TIFF-файл!";
            log->append("Не TIFF-файл!");
            continue;
        }
        int lamda;
        try {
            lamda = std::stoi(s.substr(s.length() - 8, 3));
        } catch (...) {
            qDebug() << "Неправильное название файла!";
            log->append("Неправильное название файла!");
        }
        TIFF* tiff = TIFFOpen((folder+s).c_str(), "r");
        this->rememberImage(tiff);
        this->avgIntesityOnSelectedArea();
        fout << lamda << " " <<
        TIFFClose(tiff);
        qDebug() << "Done!";
        log->append("--------------------");
        progressBar->setValue(int(double(k)/_files.size()*100));
        k++;
    }
    progressBar->setValue(100);
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] /= _files.size();
        }
    }
    QImage qimg = convert_S_ToGrayScaleQImage();
    QPixmap pixmap;
    pixmap = pixmap.fromImage(qimg);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap);
    saved = qimg;
}
*/

void Core::draw(QString _fullPathToFolder, QStringList _files) {
    QApplication::processEvents();
    std::string folder = _fullPathToFolder.toStdString();
    /*
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] = 0;
        }
    }
    */
    int k = 0;
    for (QString file : _files) {
        QApplication::processEvents();
        qDebug() << "Обработка: " << file << "...";
        log->append("Обработка: " + file + "...");
        std::string s = file.toStdString();
        if (s.substr(s.length() - 4, 4) != "tiff") {
            qDebug() << "Не TIFF-файл!";
            log->append("Не TIFF-файл!");
            continue;
        }
        TIFF* tiff = TIFFOpen((folder+s).c_str(), "r");
        this->rememberImage(tiff);
        int lamda;
        try {
            lamda = std::stoi(s.substr(s.length() - 8, 3));
        } catch (...) {
            qDebug() << "Неправильное название файла!";
            log->append("Неправильное название файла!");
            continue;
        }
        int pointCount_a1 = 0, pointCount_a2 = 0;
        double avgI_a1 = 0., avgI_a2 = 0.;
        double maxI_a1 = 0., maxI_a2 = 0.;
        double minI_a1 = pow(2,12), minI_a2 = pow(2,12);
        for (int h = 0; h < 1024; h++) {
            QApplication::processEvents();
            for (int w = 0; w < 1024; w++) {
                if (belongsQ_a1(QPointF(w, h))) {
                    avgI_a1 += (double)currS[h][w];
                    //if ((double)currS[h][w] > maxI_a1) maxI_a1 = (double)currS[h][w];
                    //if ((double)currS[h][w] < minI_a1) minI_a1 = (double)currS[h][w];
                    pointCount_a1++;
                }
                if (belongsQ_a2(QPointF(w, h))) {
                    avgI_a2 += (double)currS[h][w];
                    //if ((double)currS[h][w] > maxI_a2) maxI_a2 = (double)currS[h][w];
                    //if ((double)currS[h][w] < minI_a2) minI_a2 = (double)currS[h][w];
                    pointCount_a2++;
                }
            }
        }
        avgI_a1 /= pointCount_a1;
        avgI_a2 /= pointCount_a2;
        double I1 = avgI_a2 / avgI_a1;
        double I2 = 1 - I1;
        //this->v_lamda.push_back(lamda);
        //this->v_maxI_a1.push_back(maxI_a1);
        //this->v_minI_a1.push_back(minI_a1);
        //this->v_maxI_a2.push_back(maxI_a2);
        //this->v_minI_a2.push_back(minI_a2);
        //this->v_avgI_a1.push_back(avgI_a1);
        //this->v_avgI_a2.push_back(avgI_a2);
        //this->v_I1.push_back(I1);
        //this->v_I2.push_back(I2);
        qDebug() << "[Зона 1 (ball)] Средняя интенсивность: " << avgI_a1;
        log->append("[Зона 1 (ball)] Средняя интенсивность: " + QString::number(avgI_a1));
        /*
        qDebug() << "[Зона 1 (ball)] Макс. интенсивность: " << maxI_a1;
        log->append("[Зона 1 (ball)] Макс. интенсивность: " + QString::number(maxI_a1));
        qDebug() << "[Зона 1 (ball)] Мин. интенсивность: " << minI_a1;
        log->append("[Зона 1 (ball)] Мин. интенсивность: " + QString::number(minI_a1));
        */
        qDebug() << "[Зона 2 (grass)] Средняя интенсивность: " << avgI_a2;
        log->append("[Зона 2 (grass)] Средняя интенсивность: " + QString::number(avgI_a2));
        /*
        qDebug() << "[Зона 2 (grass)] Макс. интенсивность: " << maxI_a2;
        log->append("[Зона 2 (grass)] Макс. интенсивность: " + QString::number(maxI_a2));
        qDebug() << "[Зона 2 (grass)] Мин. интенсивность: " << minI_a2;
        log->append("[Зона 2 (grass)] Мин. интенсивность: " + QString::number(minI_a2));
        */
        TIFFClose(tiff);
        qDebug() << "Done!";
        log->append("--------------------");
        progressBar->setValue(int(double(k)/_files.size()*100));
        k++;
    }
    progressBar->setValue(100);
    /*
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] /= _files.size();
        }
    }
    */
    //QImage qimg = convert_S_ToGrayScaleQImage();
    QPixmap pixmap;
    //pixmap = pixmap.fromImage(qimg);
    pixmap = pixmap.fromImage(saved);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap/*.scaled(500, 500)*/);
    //saved = qimg;
    return;
}

void Core::draw_n_writeToFile(QString _fullPathToFolder, QStringList _files, QString _fullPathToFile) {
    QApplication::processEvents();
    std::string path = _fullPathToFile.toStdString();
    std::ofstream fout;
    fout.open(path);
    fout << "lamda  S_отр_ср(lamda)   S_ист_ср(lamda)   I1(lamda)  I2(lamda)    S_отр_max   S_отр_min   S_ист_max   S_ист_min\n";
    std::string write;

    std::string folder = _fullPathToFolder.toStdString();
    /*
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] = 0;
        }
    }
    */
    int k = 0;
    for (QString file : _files) {
        QApplication::processEvents();
        qDebug() << "Обработка: " << file << "...";
        log->append("Обработка: " + file + "...");
        std::string s = file.toStdString();
        if (s.substr(s.length() - 4, 4) != "tiff") {
            qDebug() << "Не TIFF-файл!";
            log->append("Не TIFF-файл!");
            continue;
        }
        TIFF* tiff = TIFFOpen((folder+s).c_str(), "r");
        this->rememberImage(tiff);
        int lamda;
        try {
            lamda = std::stoi(s.substr(s.length() - 8, 3));
        } catch (...) {
            qDebug() << "Неправильное название файла!";
            log->append("Неправильное название файла!");
            continue;
        }
        int pointCount_a1 = 0, pointCount_a2 = 0;
        double avgI_a1 = 0., avgI_a2 = 0.;
        double maxI_a1 = 0., maxI_a2 = 0.;
        double minI_a1 = pow(2,12), minI_a2 = pow(2,12);
        for (int h = 0; h < 1024; h++) {
            QApplication::processEvents();
            for (int w = 0; w < 1024; w++) {
                if (belongsQ_a1(QPointF(w, h))) {
                    avgI_a1 += (double)currS[h][w];
                    if ((double)currS[h][w] > maxI_a1) maxI_a1 = (double)currS[h][w];
                    if ((double)currS[h][w] < minI_a1) minI_a1 = (double)currS[h][w];
                    pointCount_a1++;
                }
                if (belongsQ_a2(QPointF(w, h))) {
                    avgI_a2 += (double)currS[h][w];
                    if ((double)currS[h][w] > maxI_a2) maxI_a2 = (double)currS[h][w];
                    if ((double)currS[h][w] < minI_a2) minI_a2 = (double)currS[h][w];
                    pointCount_a2++;
                }
            }
        }
        avgI_a1 /= pointCount_a1;
        avgI_a2 /= pointCount_a2;
        double I1 = avgI_a2 / avgI_a1;
        double I2 = 1 - I1;
        //this->v_lamda.push_back(lamda);
        //this->v_maxI_a1.push_back(maxI_a1);
        //this->v_minI_a1.push_back(minI_a1);
        //this->v_maxI_a2.push_back(maxI_a2);
        //this->v_minI_a2.push_back(minI_a2);
        //this->v_avgI_a1.push_back(avgI_a1);
        //this->v_avgI_a2.push_back(avgI_a2);
        //this->v_I1.push_back(I1);
        //this->v_I2.push_back(I2);
        qDebug() << "[Зона 1 (ball)] Средняя интенсивность: " << avgI_a1;
        log->append("[Зона 1 (ball)] Средняя интенсивность: " + QString::number(avgI_a1));

        qDebug() << "[Зона 1 (ball)] Макс. интенсивность: " << maxI_a1;
        log->append("[Зона 1 (ball)] Макс. интенсивность: " + QString::number(maxI_a1));
        qDebug() << "[Зона 1 (ball)] Мин. интенсивность: " << minI_a1;
        log->append("[Зона 1 (ball)] Мин. интенсивность: " + QString::number(minI_a1));

        qDebug() << "[Зона 2 (grass)] Средняя интенсивность: " << avgI_a2;
        log->append("[Зона 2 (grass)] Средняя интенсивность: " + QString::number(avgI_a2));

        qDebug() << "[Зона 2 (grass)] Макс. интенсивность: " << maxI_a2;
        log->append("[Зона 2 (grass)] Макс. интенсивность: " + QString::number(maxI_a2));
        qDebug() << "[Зона 2 (grass)] Мин. интенсивность: " << minI_a2;
        log->append("[Зона 2 (grass)] Мин. интенсивность: " + QString::number(minI_a2));

        write = dtos(lamda) + " " + dtos(avgI_a2) + " " + dtos(avgI_a1)
             + " " + dtos(I1) + " " + dtos(I2) + " "
                + dtos(maxI_a2) + " " + dtos(minI_a2) + " "
                + dtos(maxI_a1) + " " + dtos(minI_a1) + "\n";
        fout << write;
        TIFFClose(tiff);
        qDebug() << "Done!";
        log->append("--------------------");
        progressBar->setValue(int(double(k)/_files.size()*100));
        k++;
    }
    fout.close();
    progressBar->setValue(100);
    /*
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] /= _files.size();
        }
    }
    */
    //QImage qimg = convert_S_ToGrayScaleQImage();
    QPixmap pixmap;
    //pixmap = pixmap.fromImage(qimg);
    pixmap = pixmap.fromImage(saved);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap/*.scaled(500, 500)*/);
    //saved = qimg;
    return;
}

void Core::pre_draw(QString _fullPathToFolder, QStringList _files) {
    QApplication::processEvents();
    std::string folder = _fullPathToFolder.toStdString();
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] = 0;
        }
    }
    int k = 0;
    for (QString file : _files) {
        QApplication::processEvents();
        qDebug() << "Обработка: " << file << "...";
        log->append("Обработка: " + file + "...");
        std::string s = file.toStdString();
        if (s.substr(s.length() - 4, 4) != "tiff") {
            qDebug() << "Не TIFF-файл!";
            log->append("Не TIFF-файл!");
            continue;
        }
        TIFF* tiff = TIFFOpen((folder+s).c_str(), "r");
        this->rememberImage(tiff);
        TIFFClose(tiff);
        qDebug() << "Done!";
        log->append("--------------------");
        progressBar->setValue(int(double(k)/_files.size()*100));
        k++;
    }
    progressBar->setValue(100);
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            S[i][j] /= _files.size();
        }
    }
    QImage qimg = convert_S_ToGrayScaleQImage();
    QPixmap pixmap;
    pixmap = pixmap.fromImage(qimg);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap/*.scaled(500, 500)*/);
    saved = qimg;
    return;
}

void Core::writeToFile(QString _fullPathToFile) {
    QApplication::processEvents();
    std::string path = _fullPathToFile.toStdString();
    int k = 0;
    std::ofstream fout;
    fout.open(path);
    fout << "lamda  S_отр(lamda)   S_ист(lamda)   I1(lamda)  I2(lamda)\n";
    std::string write;
    for (unsigned int i = 0; i < this->v_lamda.size(); i++) {
        write = dtos(v_lamda[i]) + " " + dtos(v_avgI_a2[i]) + " " + dtos(v_avgI_a1[i])
             + " " + dtos(v_I1[i]) + " " + dtos(v_I2[i]) + "\n";
        fout << write;
        k++;
        progressBar->setValue(int(double(k)/v_lamda.size()));
    }
    progressBar->setValue(100);
    fout.close();
    return;
}

void Core::rememberImage(TIFF *tiff) {
    QApplication::processEvents();
    // Temporary variables
    uint32 width, height;

    // Read dimensions of image
    if (TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width) != 1) {
        qDebug() << "Failed to read width of TIFF";
    }
    if (TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height) != 1) {
        qDebug() << "Failed to read height of TIFF";
    }
    qDebug() << "width =" << width << " height =" << height;
    log->append("width = " + QString::number(width) + "   height = " + QString::number(height));

    if (width > 1024) {
        qDebug() << "width > 1024 !";
        log->append("width > 1024 !");
        return;
    }
    if (height > 1024) {
        qDebug() << "height > 1024 !";
        log->append("height > 1024 !");
        return;
    }

    QVarLengthArray<quint16, 1024> src(width);
    int max = 0; int min = pow(2, 12);
    for (uint32 y = 0; y < height; ++y) {
         QApplication::processEvents();
         TIFFReadScanline(tiff, src.data(), y, 0);
         for (int i = 0; i < src.size(); i++) {
             currS[y][i] = src[i];
             S[y][i] += src[i];
             if (src[i] > max) max = src[i];
             if (src[i] < min) min = src[i];
         }
    }
    qDebug() << "Total MAX value: " << max;
    log->append("Total MAX value: " + QString::number(max));
    qDebug() << "Total MIN value: " << min;
    log->append("Total MIN value: " + QString::number(min));
    return;
}

QImage Core::convert_S_ToGrayScaleQImage() {
    QApplication::processEvents();
    QImage result(1024, 1024, QImage::Format_Grayscale8);
    for (uint32 y = 0; y < 1024; y++) {
        QApplication::processEvents();
        quint8* dst = (quint8*)result.scanLine(y);
        for (uint32 x = 0; x < 1024; x++) {
             dst[x] = quint16(S[y][x]) >> this->brightness; //!
        }
    }
    return result;
}

/*
QImage Core::convertGray16TifToQImage(TIFF *tiff) {
    // Temporary variables
    uint32 width, height;

    // Read dimensions of image
    if (TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width) != 1) {
        qDebug() << "Failed to read width of TIFF";
    }
    if (TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height) != 1) {
        qDebug() << "Failed to read height of TIFF";
    }
    qDebug() << "width =" << width << " height =" << height;
    log->append("width = " + QString::number(width) + "   height = " + QString::number(height));
    QImage result(width, height, QImage::Format_Grayscale8);

    QVarLengthArray<quint16, 1024> src(width);
    int max = 0; int min = pow(2, 12);
    for (uint32 y = 0; y < height; ++y) {
         TIFFReadScanline(tiff, src.data(), y, 0);
         for (int i = 0; i < src.size(); i++) {
             S[y][i] = src[i];
             if (src[i] > max) max = src[i];
             if (src[i] < min) min = src[i];
         }
         quint8* dst = (quint8*)result.scanLine(y);
         for (uint32 x = 0; x < width; ++x) {
              dst[x] = src[x] >> 2; //!
         }
    }
    qDebug() << "Total MAX value: " << max;
    log->append("Total MAX value: " + QString::number(max));
    qDebug() << "Total MIN value: " << min;
    log->append("Total MIN value: " + QString::number(min));
    return result;
}
*/

void Core::setLog(QTextEdit *_log) {
    this->log = _log;
    return;
}

void Core::setProgressBar(QProgressBar *_prgrsBar) {
    this->progressBar = _prgrsBar;
    return;
}

void Core::clearSelection() {
    QGraphicsScene* sc = this->scene();
    QPixmap pixmap;
    pixmap = pixmap.fromImage(saved);
    sc->addPixmap(pixmap);
    this->firstpoint = true;
    return;
}

void Core::setBrightness(int _br) {
    this->brightness = _br;
    return;
}

void Core::re_draw() {
    QApplication::processEvents();
    QImage qimg = convert_S_ToGrayScaleQImage();
    QPixmap pixmap;
    pixmap = pixmap.fromImage(qimg);
    QGraphicsScene* sc = this->scene();
    sc->addPixmap(pixmap/*.scaled(500, 500)*/);
    saved = qimg;
    this->clearSelection();
    return;
}

void Core::setPaintEnabled(bool _flag) {
    this->paintingEnabled = _flag;
}
