#ifndef TOOL_H
#define TOOL_H

#include <QPointF>
#include "../control/snapmanager.h"

class Tool {
protected:
    bool m_currentlyWorking = false;
    SnapManager* m_snap = nullptr;
public:
    Tool(SnapManager* sm);
    bool currentlyWorking();
    virtual void resetTool() = 0;
    virtual void mousePress(const QPointF& pos) = 0;
    virtual void mouseMove(const QPointF& pos) {}
    virtual void mouseRelease(const QPointF& pos) {}
    virtual ~Tool() {}
};

#endif // TOOL_H
