#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "scenecontroller.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"
#include "../view/graphicspoint.h"

class InteractionManager {
public:
    SceneController* m_ctrl;

    GraphicsPoint* m_hoveredPoint = nullptr;
    GraphicsPoint* m_snappedPoint = nullptr;
    GraphicsLine* m_hoveredLine = nullptr;
    GraphicsCircle* m_hoveredCircle = nullptr;

    InteractionManager(SceneController* c);

    void clearHover();

    void updateHover(const QPointF& pos);

    GraphicsPoint* getSnappedPoint(const QPointF& pos);
};

#endif // INTERACTIONMANAGER_H
