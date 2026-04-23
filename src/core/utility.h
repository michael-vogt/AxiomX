#ifndef UTILITY_H
#define UTILITY_H

#include "../view/graphicsobject.h"
#include "../core/enums.h"

template<typename Base, typename T>
inline bool instanceOf(T* ptr);

QString lineTypeToString(LineType lineType);

void printGraphicsObjectsToConsole(std::vector<GraphicsObject*> graphics);

#endif // UTILITY_H
