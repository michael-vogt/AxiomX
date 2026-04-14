#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "view.h"

namespace View {
namespace Tools {
class PointTool;
}
}

class PointTool : public Tool {
private:
    SceneController* ctrl;

public:
    PointTool(SceneController* c) : ctrl(c) {}

    void mousePress(const QPointF &pos) override {
        ctrl->createPoint(pos.x(), pos.y());
    }
};

#endif // POINTTOOL_H
