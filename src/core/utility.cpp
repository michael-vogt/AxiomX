#include "utility.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"
#include "../view/graphicspoint.h"

template<typename Base, typename T>
inline bool instanceOf(T* ptr) {
    return (dynamic_cast<Base*>(ptr) != nullptr);
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

void printGraphicsObjectsToConsole(std::vector<GraphicsObject*> graphics) {
    qDebug() << "graphics contains " << QString::number(graphics.size()) + " elements:";
    for (auto go : graphics) {
        auto gp = dynamic_cast<GraphicsPoint*>(go);
        if (gp) qDebug() << gp;
        auto gl = dynamic_cast<GraphicsLine*>(go);
        if (gl) qDebug() << gl;
        auto gc = dynamic_cast<GraphicsCircle*>(go);
        if (gc) qDebug() << gc;
    }
}