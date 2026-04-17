#ifndef UTILITY_H
#define UTILITY_H

#include "infinitelineitem.h"

double distancePointToSegment(const QPointF& p, const QPointF& a, const QPointF& b) {
    double dx = b.x() - a.x();
    double dy = b.y() - a.y();

    if (dx == 0 && dy == 0) {
        return QLineF(p, a).length();
    }

    double t = ((p.x() - a.x()) * dx + (p.y() - a.y()) * dy) / (dx*dx + dy*dy);

    t = std::max(0.0, std::min(1.0, t));

    QPointF projection(a.x() + t * dx, a.y() + t * dy);

    return QLineF(p, projection).length();
}

QString lineTypeToString(LineType lineType) {
    switch (lineType) {
    case SEGMENT:
        return "Segment";
    case RAY:
        return "Ray";
    case LINE:
        return "Line";
    default:
        return "Unknown";
    }
}

#endif // UTILITY_H
