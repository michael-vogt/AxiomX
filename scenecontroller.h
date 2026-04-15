#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGraphicsScene>
#include <vector>
#include "core.h"
#include "view.h"

#include "graphicsobject.h"
#include "graphicspoint.h"
#include "graphicsline.h"

namespace View {
class SceneController;
}

class SceneController {
private:
    QGraphicsScene* m_scene;
    std::vector<GraphicsObject*> m_graphics;

public:
    SceneController(QGraphicsScene* s) : m_scene(s) {}

    Point* createPoint(double x, double y) {
        Point* p = new Point(x, y);
        auto gp = new GraphicsPoint(p);

        m_scene->addItem(gp);
        gp->attach();

        m_graphics.push_back(gp);
        return p;
    }

    Line* createLine(Point* a, Point* b) {
        Line* l = new Line(a, b);
        auto gl = new GraphicsLine(l);

        m_scene->addItem(gl);
        gl->attach();

        m_graphics.push_back(gl);
        return l;
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

    std::vector<GraphicsObject*> graphics() {
        return m_graphics;
    }

    QGraphicsScene* scene() {
        return m_scene;
    }

};

#endif // SCENECONTROLLER_H
