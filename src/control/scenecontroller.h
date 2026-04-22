#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGraphicsScene>
#include <vector>
#include "../view/graphicspoint.h"
#include "../view/graphicsline.h"
#include "../view/graphicscircle.h"

class SceneController {
private:
    QGraphicsScene* m_scene;
    std::vector<GraphicsObject*> m_graphics;

public:
    SceneController(QGraphicsScene* s);

    void remove(GraphicsObject* g);

    void deleteSelected();

    GraphicsPoint* createPoint(double x, double y, bool isTemporaryPoint = false);

    GraphicsPoint* graphicsPointAlreadyExists(GraphicsPoint* gpToCheck);

    bool pointExists(Point* p);

    GraphicsLine* createLine(Point* a, Point* b);

    GraphicsObject* findObjectAt(const QPointF& pos, double radius = 10.0);

    Point* findPointNear(const QPointF& pos, double radius = 10.0);

    std::vector<GraphicsObject*>& graphics();

    QGraphicsScene* scene();

};

#endif // SCENECONTROLLER_H
