#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();

signals:
    // The signal of transmit the coordinates of the mouse position
    void signalTargetCoordinate(QPointF point);

public slots:

private:
    // The function, which made tracking the mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CUSTOMSCENE_H
