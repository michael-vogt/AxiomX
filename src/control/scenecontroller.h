#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGraphicsScene>
#include <vector>
#include "../core/core.h"
#include "../view/graphicsobject.h"
#include "../view/graphicspoint.h"
#include "../view/graphicsline.h"

class SceneController {
private:
    QGraphicsScene* m_scene;
    std::vector<GraphicsObject*> m_graphics;

public:
    SceneController(QGraphicsScene* s) : m_scene(s) {}

    void remove(GraphicsObject* g) {
        m_scene->removeItem(dynamic_cast<QGraphicsItem*>(g));
        m_graphics.erase(std::remove(m_graphics.begin(), m_graphics.end(), g), m_graphics.end());
    }

    GraphicsPoint* createPoint(double x, double y) {
        Point* p = new Point(x, y);
        auto gp = new GraphicsPoint(p);

        m_scene->addItem(gp);
        gp->attach();

        m_graphics.push_back(gp);
        return gp;
    }

    GraphicsLine* createLine(Point* a, Point* b) {
        Line* l = new Line(a, b);
        auto gl = new GraphicsLine(l);

        m_scene->addItem(gl);
        gl->attach();

        m_graphics.push_back(gl);
        return gl;
    }

    GraphicsObject* findObjectAt(const QPointF& pos, double radius = 10.0) {
        for (auto g : m_graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (gp && QLineF(gp->pos(), pos).length() < radius) {
                return gp;
            }
        }

        for (auto g : m_graphics) {
            auto gl = dynamic_cast<GraphicsLine*>(g);
            if (gl && gl->model()->distanceToPoint(pos) < radius) {
                return gl;
            }
        }

        return nullptr;
    }

    Point* findPointNear(const QPointF& pos, double radius = 10.0) {
        for (auto g : m_graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            QPointF p = gp->pos();
            if (QLineF(p, pos).length() < radius)
                return gp->model();
        }
        return nullptr;
    }

    std::vector<GraphicsObject*>& graphics() {
        return m_graphics;
    }

    QGraphicsScene* scene() {
        return m_scene;
    }

};

#endif // SCENECONTROLLER_H
