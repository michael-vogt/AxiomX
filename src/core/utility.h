#ifndef UTILITY_H
#define UTILITY_H

#include "../control/scenecontroller.h"
#include "../view/graphicsobject.h"
#include "../core/enums.h"

template<typename Base, typename T>
inline bool instanceOf(T* ptr);

QString lineTypeToString(LineType lineType);

LineType lineTypeFromInt(int lt);

void printGraphicsObjectsToConsole(std::vector<GraphicsObject*> graphics);

void save(SceneController* ctrl, const QString& filename);

void load(SceneController* ctrl, const QString& filename);

#endif // UTILITY_H
