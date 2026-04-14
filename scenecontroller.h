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
    QGraphicsScene* scene;
    std::vector<GraphicsObject*> graphics;

public:
    SceneController(QGraphicsScene* s) : scene(s) {}

    Point* createPoint(double x, double y) {
        Point* p = new Point(x, y);
        auto gp = new GraphicsPoint(p);

        scene->addItem(gp);
        gp->attach();

        graphics.push_back(gp);
        return p;
    }

    Line* createLine(Point* a, Point* b) {
        Line* l = new Line(a, b);
        auto gl = new GraphicsLine(l);

        scene->addItem(gl);
        gl->attach();

        graphics.push_back(gl);
        return l;
    }

    Point* findPointNear(const QPointF& pos, double radius = 10.0) {
        for (auto g : graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            QPointF p = gp->pos();
            if (QLineF(p, pos).length() < radius)
                return gp->getModel();
        }
        return nullptr;
    }

    QGraphicsScene* getScene() {
        return scene;
    }

};

#endif // SCENECONTROLLER_H
