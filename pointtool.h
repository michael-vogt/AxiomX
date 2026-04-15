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
    SceneController* m_ctrl;

public:
    PointTool(SceneController* c) : m_ctrl(c) {}

    void resetTool() override {}

    void mousePress(const QPointF &pos) override {
        m_ctrl->createPoint(pos.x(), pos.y());
    }
};

#endif // POINTTOOL_H
