#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGraphicsScene>
#include <vector>
#include "../core/point.h"
#include "../view/graphicsobject.h"

class SceneController {
private:
    QGraphicsScene* m_scene = nullptr;
    std::vector<GraphicsObject*> m_graphics;

public:
    SceneController(QGraphicsScene* s);

    void remove(GraphicsObject* g);

    void deleteSelected();

    bool pointExists(Point* p);

    void resize(const QSize& size, const QSize& oldSize);

    GraphicsObject* findObjectAt(const QPointF& pos, double radius = 10.0);

    Point* findPointNear(const QPointF& pos, double radius = 10.0);

    std::vector<GraphicsObject*>& graphics();

    QGraphicsScene* scene();

};

#endif // SCENECONTROLLER_H
