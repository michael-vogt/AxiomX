#ifndef STRUCTS_H
#define STRUCTS_H

#include <QPointF>
#include "../view/graphicspoint.h"

struct SnapResult {
    GraphicsPoint* gp;
    QPointF pos;
    bool snapped = false;
};

#endif // STRUCTS_H
