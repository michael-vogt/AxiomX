#ifndef SNAPMANAGER_H
#define SNAPMANAGER_H

#include <QPointF>
#include "scenecontroller.h"
#include "../core/structs.h"

class SnapManager {
public:
    SceneController* m_ctrl;

    bool m_snapToGrid = true;
    bool m_snapToPoints = true;
    bool m_snapToAxes = true;

    double m_gridSize = 50.0;
    double m_snapRadius = 10.0;

    SnapManager(SceneController* c);

    SnapResult snap(const QPointF& input);
};

#endif // SNAPMANAGER_H
