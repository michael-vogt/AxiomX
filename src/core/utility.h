#ifndef UTILITY_H
#define UTILITY_H

#include "infinitelineitem.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"
#include "../view/graphicspoint.h"

double distancePointToSegment(const QPointF& p, const QPointF& a, const QPointF& b);

template<typename Base, typename T>
inline bool instanceOf(T* ptr);

QString lineTypeToString(LineType lineType);

void printGraphicsObjectsToConsole(std::vector<GraphicsObject*> graphics);

#endif // UTILITY_H
