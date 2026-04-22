#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include <QGraphicsScene>
#include <vector>
//#include "../view/geoview.h"
#include "../view/graphicspoint.h"
#include "../view/graphicsline.h"
#include "../view/graphicscircle.h"

class SceneController {
private:
    QGraphicsScene* m_scene = nullptr;
    std::vector<GraphicsObject*> m_graphics;

public:
    SceneController(QGraphicsScene* s) : m_scene(s) {}

    void remove(GraphicsObject* g) {
        if (g->scene()) g->scene()->removeItem(dynamic_cast<QGraphicsItem*>(g));
        m_graphics.erase(std::remove(m_graphics.begin(), m_graphics.end(), g), m_graphics.end());
    }

    void deleteSelected() {
        std::vector<GraphicsPoint*> selectedPoints;
        std::vector<GraphicsLine*> selectedLines;
        std::vector<GraphicsCircle*> selectedCircles;
        for (auto g : m_graphics) {
            if (!g->selected()) continue;
            if (GraphicsPoint* gp = dynamic_cast<GraphicsPoint*>(g)) {
                selectedPoints.push_back(gp);
            } else if (GraphicsLine* gl = dynamic_cast<GraphicsLine*>(g)) {
                selectedLines.push_back(gl);
            } else if (GraphicsCircle* gc = dynamic_cast<GraphicsCircle*>(g)) {
                selectedCircles.push_back(gc);
            }
        }

        for (auto gc : selectedCircles) remove(gc);
        for (auto gl : selectedLines) remove(gl);
        for (auto gp : selectedPoints) remove(gp);
    }

    GraphicsPoint* createPoint(double x, double y, bool isTemporaryPoint = false) {
        GraphicsPoint* gp = dynamic_cast<GraphicsPoint*>(findObjectAt(QPointF(x, y)));
        if (!gp || isTemporaryPoint) {
            Point* p = new Point(x, y);
            auto gp = new GraphicsPoint(p, m_scene);


            m_scene->addItem(gp);
            gp->attach();

            m_graphics.push_back(gp);
        }
        return gp;
    }

    GraphicsPoint* graphicsPointAlreadyExists(GraphicsPoint* gpToCheck) {
        for (auto g : m_graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            if (gp != gpToCheck && gp->equals(gpToCheck)) return gp;
        }
        return nullptr;
    }

    bool pointExists(Point* p) {
        for (auto g : m_graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (!gp) continue;

            Point* q = gp->model();
            if (q->x() == p->x() && q->y() == p->y()) return true;
        }
        return false;
    }

    GraphicsLine* createLine(Point* a, Point* b) {
        Line* l = new Line(a, b);
        auto gl = new GraphicsLine(l, m_scene);

        m_scene->addItem(gl);
        gl->attach();

        m_graphics.push_back(gl);
        return gl;
    }

    GraphicsObject* findObjectAt(const QPointF& pos, double radius = 10.0) {
        // 1. Punkt
        for (auto g : m_graphics) {
            auto gp = dynamic_cast<GraphicsPoint*>(g);
            if (gp && QLineF(gp->pos(), pos).length() < radius) {
                return gp;
            }
        }

        // 2. Linien
        for (auto g : m_graphics) {
            auto gl = dynamic_cast<GraphicsLine*>(g);
            if (gl && gl->model()->distanceToPoint(pos, gl->lineType()) < radius) {
                return gl;
            }
        }

        // 3. Kreise
        for (auto g : m_graphics) {
            auto gc = dynamic_cast<GraphicsCircle*>(g);
            if (gc && gc->model()->pointOnCircle(pos, 6.0)) {
                return gc;
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
