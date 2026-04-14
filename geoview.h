#ifndef GEOVIEW_H
#define GEOVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "tool.h"

namespace View {
class GeoView;
}

class GeoView : public QGraphicsView {
private:
    Tool* tool = nullptr;

public:
    GeoView(QGraphicsScene* s) : QGraphicsView(s) {}

    void setTool(Tool* t) {
        tool = t;
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (tool) {
            tool->mousePress(mapToScene(event->pos()));
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (tool) {
            tool->mouseMove(mapToScene(event->pos()));
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        if (tool) {
            tool->mouseRelease(mapToScene(event->pos()));
        }
    }
};

#endif // GEOVIEW_H
