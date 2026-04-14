#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tool.h"
//#include "view.h"
#include "scenecontroller.h"

namespace View {
namespace Tools {
class MoveTool;
}
}

class MoveTool : public Tool {
private:
    SceneController* ctrl;
    Point* selected = nullptr;

public:
    MoveTool(SceneController* c) : ctrl(c) {}

    void mousePress(const QPointF &pos) override {
        selected = ctrl->findPointNear(pos);
    }

    void mouseMove(const QPointF &pos) override {
        if (selected) {
            selected->set(pos.x(), pos.y());
        }
    }

    void mouseRelease(const QPointF &pos) override {
        selected = nullptr;
    }
};

#endif // MOVETOOL_H
