#ifndef PHYSICS_C4_GRAPHICSSCENE_H
#define PHYSICS_C4_GRAPHICSSCENE_H

#include <QtWidgets/qgraphicsscene.h>

class GraphicsScene: public QGraphicsScene {
public:
    using QGraphicsScene::QGraphicsScene;
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};


#endif //PHYSICS_C4_GRAPHICSSCENE_H
