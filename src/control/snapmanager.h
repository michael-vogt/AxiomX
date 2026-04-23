#ifndef SNAPMANAGER_H
#define SNAPMANAGER_H

#include <QPointF>
#include "scenecontroller.h"
#include "../core/structs.h"

class SnapManager {
public:
    SceneController* ctrl;

    bool snapToGrid = true;
    bool snapToPoints = true;
    bool snapToAxes = true;

    double gridSize = 50.0;
    double snapRadius = 10.0;

    SnapManager(SceneController* c);

    SnapResult snap(const QPointF& input);
};

#endif // SNAPMANAGER_H
