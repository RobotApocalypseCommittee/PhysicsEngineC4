#include "GraphicsScene.h"
#include <QGraphicsSceneMouseEvent>
#include "mainwindow.h"

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    dynamic_cast<MainWindow *>(parent())->viewClicked(event->scenePos());
    QGraphicsScene::mouseReleaseEvent(event);
}
