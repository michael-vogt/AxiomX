#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"
#include "view.h"

namespace View {
namespace Tools {
class LineTool;
}
}

class LineTool : public Tool {
private:
    SceneController* ctrl;
    Point* first = nullptr;

public:
    LineTool(SceneController* c) : ctrl(c) {}

    void mousePress(const QPointF &pos) override {
        Point* p = ctrl->findPointNear(pos);

        if (!p) {
            p = ctrl->createPoint(pos.x(), pos.y());
        }

        if (!first) {
            first = p;
        } else {
            ctrl->createLine(first, p);
            first = nullptr;
        }
    }
};

#endif // LINETOOL_H
