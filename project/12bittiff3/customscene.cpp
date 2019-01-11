#include "customscene.h"

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}

CustomScene::~CustomScene()
{

}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() && Qt::LeftButton)
        emit signalTargetCoordinate(event->scenePos());
}
