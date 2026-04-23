#ifndef STRUCTS_H
#define STRUCTS_H

#include <QPointF>

struct SnapResult {
    QPointF pos;
    bool snapped = false;
};

#endif // STRUCTS_H
